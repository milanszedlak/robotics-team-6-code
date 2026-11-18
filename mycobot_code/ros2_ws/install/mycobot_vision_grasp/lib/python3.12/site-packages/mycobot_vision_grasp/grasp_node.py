"""myCobot arm task node (fixed camera, eye-to-hand). Runs on the laptop / NUC.

The arm itself is driven by mycobot_driver on the arm's Pi; this node only sends it
FollowJointTrajectory / GripperCommand goals over the network.

Command API (callable from any machine on the same ROS_DOMAIN_ID):
  /arm/locate_blocks  (cobot_interfaces/srv/LocateBlocks)      every block the camera sees, in base_link
  /arm/pick_block     (cobot_interfaces/action/PickBlock)      locate → approach → descend → grasp → lift
  /arm/place_block    (cobot_interfaces/action/PlaceBlock)     named pose or XYZ point → release
Only one command runs at a time; goals sent while busy are rejected.

Autonomous mode (parameter autorun:=true) runs the vehicle hand-off loop instead:

  camera ──/vision/blocks──▶ arm: get block pose while at the home pose (not blocking the camera)
                             arm: move above block → descend vertically → grasp → lift to carry pose
                             arm ──/arm/holding = "red"──▶ vehicle
                                                          vehicle: drive to the red basket
                             arm ◀──/vehicle/arrived = "red"── vehicle
                             arm: check the colour matches → move to place pose → release
                             arm ──/arm/state = "DONE"──▶ vehicle may leave

Coordinate transforms (the camera is fixed and does not move with the arm):

  camera optical frame camera_color_optical_frame (3D points from the vision node)
      │  T(base ← camera): constant, from config/camera_pose.yaml (published as a static TF by the launch file)
      ▼
  arm base frame base_link → used to plan the grasp
      │  T(gripper centre ← base): current arm pose (TF base_link → link6_flange from the driver)
      ▼
  gripper centre frame gripper_tcp

Inverse kinematics: ik_solver = internal (default; mycobot_driver.kinematics, validated against
the arm firmware) or moveit (MoveIt /compute_ik, used in the Gazebo simulation).
"""
import math
import threading
import time

import numpy as np
import rclpy
from action_msgs.msg import GoalStatus
from cobot_interfaces.action import PickBlock, PlaceBlock
from cobot_interfaces.msg import BlockInfo, BlockTargetArray
from cobot_interfaces.srv import LocateBlocks
from control_msgs.action import FollowJointTrajectory, GripperCommand
from geometry_msgs.msg import Point, PointStamped, PoseStamped, TransformStamped
from rclpy.action import ActionClient, ActionServer, CancelResponse, GoalResponse
from rclpy.callback_groups import ReentrantCallbackGroup
from rclpy.duration import Duration
from rclpy.executors import MultiThreadedExecutor
from rclpy.node import Node
from rclpy.qos import DurabilityPolicy, QoSProfile, ReliabilityPolicy
from rclpy.time import Time
from sensor_msgs.msg import JointState
from std_msgs.msg import String
import tf2_ros
from trajectory_msgs.msg import JointTrajectoryPoint

from mycobot_driver.kinematics import ik as internal_ik

from .geometry import (apply_transform, axis_vector, build_grasp_rotation,
                       effective_closing_vector, fit_joint_limit, make_transform,
                       matrix_to_quat, select_grasp, tcp_frame_rotation,
                       yaw_candidates)
from .targeting import Candidate, choose_block, corners_valid

# Values published on /arm/state
IDLE, PICKING, HOLDING, PLACING, DONE, ERROR = 'IDLE', 'PICKING', 'HOLDING', 'PLACING', 'DONE', 'ERROR'

LATCHED_QOS = QoSProfile(depth=1, reliability=ReliabilityPolicy.RELIABLE,
                         durability=DurabilityPolicy.TRANSIENT_LOCAL)


class GraspError(Exception):
    pass


class Cancelled(Exception):
    pass


class ArmTaskNode(Node):

    def __init__(self):
        super().__init__('arm_task')
        P = self.declare_parameter

        # --- Robot / gripper ---
        self.base_frame = P('base_frame', 'base_link').value
        self.ik_link = P('ik_link', 'link6_flange').value
        self.tcp_frame = P('tcp_frame', 'gripper_tcp').value
        self.tcp_offset = P('tcp_offset', 0.10).value
        self.planning_group = P('planning_group', 'arm').value
        self.arm_joints = list(P('arm_joints', [
            'link1_to_link2', 'link2_to_link3', 'link3_to_link4',
            'link4_to_link5', 'link5_to_link6', 'link6_to_link6_flange']).value)
        self.approach_axis = P('approach_axis', '+z').value
        self.closing_axis = P('closing_axis', '+y').value
        self.roll_offset = math.radians(P('gripper_roll_offset_deg', 45.0).value)
        wrist = P('wrist_joint', '').value or self.arm_joints[-1]
        self.wrist_idx = self.arm_joints.index(wrist)
        lo, hi = P('wrist_limits_deg', [-175.0, 175.0]).value
        self.wrist_lo, self.wrist_hi = math.radians(lo), math.radians(hi)
        self.home_joints = list(P('home_joints', [0.0, 0.5, -1.8, 0.0, 0.0, 0.0]).value)
        self.carry_joints = list(P('carry_joints', [0.0, 0.0, -1.0, -0.5, 0.0, 0.0]).value)
        self.place_joints = list(P('place_joints', [1.2, -0.3, -1.2, -0.05, 0.0, 0.0]).value)

        # --- Controllers / IK ---
        arm_action = P('arm_action', '/arm_controller/follow_joint_trajectory').value
        self.ik_solver = P('ik_solver', 'internal').value
        ik_service = P('ik_service', '/compute_ik').value
        self.ik_timeout = P('ik_timeout', 0.2).value
        self.ik_avoid_collisions = P('ik_avoid_collisions', False).value
        self.max_joint_speed = P('max_joint_speed', 0.6).value
        self.min_segment_time = P('min_segment_time', 0.4).value

        # --- Gripper ---
        self.gripper_mode = P('gripper_mode', 'action').value
        gripper_action = P('gripper_action', '/gripper_action_controller/gripper_cmd').value
        gripper_traj_action = P('gripper_trajectory_action',
                                '/gripper_controller/follow_joint_trajectory').value
        self.gripper_joint = P('gripper_joint', 'gripper_controller').value
        self.gripper_open = P('gripper_open_position', 0.0).value
        self.gripper_closed = P('gripper_closed_position', -0.7).value
        self.gripper_effort = P('gripper_max_effort', 10.0).value
        self.gripper_max_opening = P('gripper_max_opening', 0.045).value
        self.grasp_check_tolerance = P('grasp_check_tolerance', 0.03).value

        # --- Vision interface ---
        vision_topic = P('vision_topic', '/vision/blocks').value
        self.camera_frame = P('camera_frame', 'camera_color_optical_frame').value
        self.min_confidence = P('min_confidence', 0.5).value
        self.settle_time = P('settle_time', 0.6).value
        self.vision_timeout = P('vision_timeout', 5.0).value
        self.track_max_jump = P('track_max_jump', 0.03).value
        self.accept_unstamped = P('accept_unstamped', False).value

        # --- Grasp strategy ---
        self.approach_height = P('approach_height', 0.08).value
        self.grasp_depth = P('grasp_depth', 0.012).value
        self.lift_height = P('lift_height', 0.08).value
        self.min_grasp_z = P('min_grasp_z', 0.005).value
        self.descend_step = P('descend_step', 0.02).value
        self.detect_samples = P('detect_samples', 3).value
        self.detect_retries = P('detect_retries', 5).value

        # --- Mode / vehicle hand-off ---
        self.autorun = P('autorun', False).value
        self.wait_for_vehicle = P('wait_for_vehicle', True).value
        self.vehicle_timeout = P('vehicle_timeout', 300.0).value
        self.loop = P('loop', True).value

        # --- Communication ---
        cb = ReentrantCallbackGroup()
        self.tf_buffer = tf2_ros.Buffer()
        self.tf_listener = tf2_ros.TransformListener(self.tf_buffer, self)
        self.tf_static = tf2_ros.StaticTransformBroadcaster(self)
        self._publish_tcp_frame()
        self._lock = threading.Lock()
        self._blocks_msg = None
        self._joint_pos = {}
        self._arrived = None
        self.busy = threading.Lock()        # one command (or autorun cycle) at a time
        self.ready = False
        self._stage_cb = None               # set while an action goal runs: feedback + cancel check

        self.create_subscription(BlockTargetArray, vision_topic, self._on_blocks, 10,
                                 callback_group=cb)
        self.create_subscription(JointState, '/joint_states', self._on_joints, 10,
                                 callback_group=cb)
        self.create_subscription(String, '/vehicle/arrived', self._on_arrived, 10,
                                 callback_group=cb)
        self.state_pub = self.create_publisher(String, '/arm/state', LATCHED_QOS)
        self.holding_pub = self.create_publisher(String, '/arm/holding', LATCHED_QOS)
        self.target_tcp_pub = self.create_publisher(PointStamped, '/arm/target_in_gripper', 10)
        self.target_base_pub = self.create_publisher(PointStamped, '/arm/target_in_base', 10)

        self.arm_client = ActionClient(self, FollowJointTrajectory, arm_action, callback_group=cb)
        if self.gripper_mode == 'trajectory':
            self.gripper_client = ActionClient(self, FollowJointTrajectory,
                                               gripper_traj_action, callback_group=cb)
        else:
            self.gripper_client = ActionClient(self, GripperCommand, gripper_action,
                                               callback_group=cb)
        self.ik_client = None
        if self.ik_solver == 'moveit':
            from moveit_msgs.srv import GetPositionIK      # only needed with MoveIt (simulation)
            self._GetPositionIK = GetPositionIK
            self.ik_client = self.create_client(GetPositionIK, ik_service, callback_group=cb)
        elif self.ik_solver != 'internal':
            raise ValueError(f"ik_solver must be 'internal' or 'moveit', not {self.ik_solver!r}")

        # --- Command API ---
        self.create_service(LocateBlocks, '/arm/locate_blocks', self._srv_locate, callback_group=cb)
        ActionServer(self, PickBlock, '/arm/pick_block', execute_callback=self._exec_pick,
                     goal_callback=self._accept_goal,
                     cancel_callback=lambda _: CancelResponse.ACCEPT, callback_group=cb)
        ActionServer(self, PlaceBlock, '/arm/place_block', execute_callback=self._exec_place,
                     goal_callback=self._accept_goal,
                     cancel_callback=lambda _: CancelResponse.ACCEPT, callback_group=cb)

        self.state = None
        self.holding = ''
        self.set_state(IDLE)
        self.set_holding('')

    def _publish_tcp_frame(self):
        """Publish ik_link → gripper_tcp (enable TF in RViz to see the gripper centre and real closing direction)."""
        t = TransformStamped()
        t.header.stamp = self.get_clock().now().to_msg()
        t.header.frame_id = self.ik_link
        t.child_frame_id = self.tcp_frame
        p = axis_vector(self.approach_axis) * self.tcp_offset
        t.transform.translation.x, t.transform.translation.y, t.transform.translation.z = map(float, p)
        q = matrix_to_quat(tcp_frame_rotation(self.approach_axis, self.closing_axis,
                                              self.roll_offset))
        (t.transform.rotation.x, t.transform.rotation.y,
         t.transform.rotation.z, t.transform.rotation.w) = map(float, q)
        self.tf_static.sendTransform(t)

    # ================================================================ callbacks
    def _on_blocks(self, msg):
        with self._lock:
            self._blocks_msg = msg

    def _on_joints(self, msg):
        with self._lock:
            for n, p in zip(msg.name, msg.position):
                self._joint_pos[n] = p

    def _on_arrived(self, msg):
        with self._lock:
            self._arrived = (msg.data.strip().lower(), time.monotonic())

    # ================================================================ status reporting
    def set_state(self, s):
        if s != self.state:
            self.get_logger().info(f'/arm/state → {s}')
        self.state = s
        self.state_pub.publish(String(data=s))

    def set_holding(self, color):
        self.holding = color
        self.holding_pub.publish(String(data=color))

    def stage(self, name, log_msg=None):
        """Log a step; when running an action goal also send feedback and honour cancel requests."""
        if log_msg:
            self.get_logger().info(log_msg)
        if self._stage_cb is not None:
            self._stage_cb(name)

    # ================================================================ helpers
    @staticmethod
    def _wait(future, timeout, what):
        end = time.monotonic() + timeout
        while not future.done():
            if time.monotonic() > end:
                raise GraspError(f'{what} timed out')
            time.sleep(0.005)
        return future.result()

    def current_arm_joints(self):
        with self._lock:
            missing = [j for j in self.arm_joints if j not in self._joint_pos]
            if missing:
                raise GraspError(f'joints {missing} not found in /joint_states; '
                                 f'check the arm_joints parameter')
            return [self._joint_pos[j] for j in self.arm_joints]

    def wait_for_ready(self):
        self.get_logger().info('Waiting for the arm driver, joint states and TF...')
        checks = [
            ('arm_controller action (is mycobot_driver running on the Pi? same ROS_DOMAIN_ID?)',
             lambda: self.arm_client.wait_for_server(timeout_sec=1.0)),
            ('gripper action', lambda: self.gripper_client.wait_for_server(timeout_sec=1.0)),
            ('/joint_states', lambda: bool(self._joint_pos) or time.sleep(1.0)),
            (f'TF {self.base_frame} ← {self.ik_link} (published by mycobot_driver)',
             lambda: self.tf_buffer.can_transform(self.base_frame, self.ik_link, Time(),
                                                  timeout=Duration(seconds=1.0))),
            (f'TF {self.base_frame} ← {self.camera_frame} (camera_pose.yaml + camera driver)',
             lambda: self.tf_buffer.can_transform(self.base_frame, self.camera_frame, Time(),
                                                  timeout=Duration(seconds=1.0))),
        ]
        if self.ik_client is not None:
            checks.insert(2, ('MoveIt /compute_ik',
                              lambda: self.ik_client.wait_for_service(timeout_sec=1.0)))
        for name, ok in checks:
            n = 0
            while rclpy.ok() and not ok():
                n += 1
                if n % 5 == 0:
                    self.get_logger().warn(f'Still waiting for {name} ...')
        if not rclpy.ok():
            return
        self.current_arm_joints()
        T = self.lookup_T(self.base_frame, self.camera_frame)
        self.get_logger().info(f'Camera (optical frame origin) in base frame: {np.round(T[:3, 3], 3)} m')
        if self._blocks_msg is None:
            self.get_logger().warn('No /vision/blocks received yet; is the vision node running?')
        self.ready = True
        if self.autorun:
            self.get_logger().info('Arm ready (autorun: vehicle hand-off loop)')
        else:
            self.get_logger().info('Arm ready. Commands: /arm/locate_blocks, /arm/pick_block, '
                                   '/arm/place_block')

    def lookup_T(self, target, source, stamp=None):
        """Return the 4x4 transform T(target ← source)."""
        t = Time() if stamp is None else Time.from_msg(stamp)
        try:
            tf = self.tf_buffer.lookup_transform(target, source, t, timeout=Duration(seconds=1.0))
        except tf2_ros.TransformException as e:
            if stamp is None:
                raise GraspError(f'TF {target} ← {source} failed: {e}')
            return self.lookup_T(target, source)
        tr, q = tf.transform.translation, tf.transform.rotation
        return make_transform((tr.x, tr.y, tr.z), (q.x, q.y, q.z, q.w))

    def current_closing_yaw(self):
        T = self.lookup_T(self.base_frame, self.ik_link)
        v = T[:3, :3] @ effective_closing_vector(self.approach_axis, self.closing_axis,
                                                 self.roll_offset)
        return math.atan2(v[1], v[0])

    # ================================================================ transforms (camera → base)
    def blocks_to_candidates(self, msg):
        T_tcp_base = self.lookup_T(self.tcp_frame, self.base_frame)    # current gripper pose
        cands = []
        for b in msg.blocks:
            header = b.header if b.header.frame_id else msg.header
            cam_frame = header.frame_id or self.camera_frame

            pts_cam = np.array([[b.center.x, b.center.y, b.center.z]] +
                               [[p.x, p.y, p.z] for p in b.corners], np.float64)
            if not np.all(np.isfinite(pts_cam[0])) or pts_cam[0, 2] <= 0.0:
                continue

            # Fixed camera: T(base ← camera) is constant
            T_base_cam = self.lookup_T(self.base_frame, cam_frame)
            pts_base = apply_transform(T_base_cam, pts_cam)
            center_tcp = apply_transform(T_tcp_base, pts_base[:1])[0]

            corners_ok = corners_valid(pts_cam[1:])
            cands.append(Candidate(
                color=b.color.strip().lower(),
                confidence=float(b.confidence),
                should_grasp=bool(b.should_grasp),
                center_base=pts_base[0],
                corners_base=pts_base[1:] if corners_ok else None,
                center_tcp=center_tcp,
            ))
        return cands

    def fresh_blocks(self):
        """Wait for a detection captured after the arm has stopped (so the arm is not moving in the image)."""
        t_min = self.get_clock().now() + Duration(seconds=self.settle_time)
        end = time.monotonic() + self.vision_timeout + 3 * self.settle_time
        while time.monotonic() < end:
            with self._lock:
                m = self._blocks_msg
            if m is not None:
                st = m.header.stamp
                if Time.from_msg(st) >= t_min:
                    return m
                if self.accept_unstamped and st.sec == 0 and st.nanosec == 0:
                    return m
            time.sleep(0.02)
        self.get_logger().warn('No new /vision/blocks received '
                               '(is the vision node running? are the timestamps correct?)')
        return None

    def locate_once(self, color=None, ref_point=None):
        msg = self.fresh_blocks()
        if msg is None:
            return None
        cands = []
        for c in self.blocks_to_candidates(msg):
            if c.corners_base is not None:
                c.grasp = select_grasp(c.corners_base, self.gripper_max_opening)
                if c.grasp is None:
                    self.get_logger().warn(f'{c.color} block is wider than the gripper opening; skipped')
                    continue
            cands.append(c)
        return choose_block(cands, self.min_confidence, color, ref_point, self.track_max_jump)

    def locate(self, color=None):
        """Take detect_samples frames and average the position and angle of the same block.
        Returns (Candidate, yaw)."""
        first = self.locate_once(color)
        if first is None:
            return None
        samples = [first]
        for _ in range(self.detect_samples - 1):
            c = self.locate_once(first.color, first.center_base)
            if c is not None:
                samples.append(c)
        best = samples[0]
        best.center_base = np.mean([c.center_base for c in samples], axis=0)
        best.center_tcp = np.mean([c.center_tcp for c in samples], axis=0)

        with_grasp = [c.grasp for c in samples if c.grasp is not None]
        if with_grasp:
            # A parallel gripper is 180° symmetric → circular mean of 2*yaw
            s2 = sum(math.sin(2 * g['yaw']) for g in with_grasp)
            c2 = sum(math.cos(2 * g['yaw']) for g in with_grasp)
            yaw = 0.5 * math.atan2(s2, c2)
            width = float(np.mean([g['width'] for g in with_grasp]))
            info = f'grasp width {width*1000:.0f} mm, closing direction {math.degrees(yaw):.0f}°'
        else:
            yaw = self.current_closing_yaw()
            info = 'no corners; keeping current gripper angle'
        t, b = best.center_tcp, best.center_base
        self.get_logger().info(
            f'[{best.color}] base frame ({b[0]:.3f}, {b[1]:.3f}, {b[2]:.3f}) m │ '
            f'relative to gripper centre ({t[0]:+.3f}, {t[1]:+.3f}, {t[2]:+.3f}) m │ {info} '
            f'(average of {len(samples)} frames)')
        now = self.get_clock().now().to_msg()
        self.target_base_pub.publish(self._point(self.base_frame, now, b))
        self.target_tcp_pub.publish(self._point(self.tcp_frame, now, t))
        return best, yaw

    @staticmethod
    def _point(frame, stamp, p):
        m = PointStamped()
        m.header.frame_id = frame
        m.header.stamp = stamp
        m.point.x, m.point.y, m.point.z = map(float, p)
        return m

    # ================================================================ motion
    def compute_ik(self, position, rotation, seed):
        """Joint solution for ik_link at (position, rotation) in base_link, or None."""
        if self.ik_client is None:
            T = np.eye(4)
            T[:3, :3] = rotation
            T[:3, 3] = position
            q = internal_ik(T, seed)
            if q is None:
                return None
        else:
            q = self._moveit_ik(position, rotation, seed)
            if q is None:
                return None
        # Joint 6 range is limited: shift the angle into range (same pose); if impossible, no solution
        w = fit_joint_limit(q[self.wrist_idx], self.wrist_lo, self.wrist_hi)
        if w is None:
            return None
        q[self.wrist_idx] = w
        return q

    def _moveit_ik(self, position, rotation, seed):
        req = self._GetPositionIK.Request()
        req.ik_request.group_name = self.planning_group
        req.ik_request.avoid_collisions = self.ik_avoid_collisions
        req.ik_request.ik_link_name = self.ik_link
        js = JointState()
        js.name = list(self.arm_joints)
        js.position = [float(x) for x in seed]
        req.ik_request.robot_state.joint_state = js
        ps = PoseStamped()
        ps.header.frame_id = self.base_frame
        ps.pose.position.x, ps.pose.position.y, ps.pose.position.z = map(float, position)
        qx, qy, qz, qw = matrix_to_quat(rotation)
        ps.pose.orientation.x, ps.pose.orientation.y = qx, qy
        ps.pose.orientation.z, ps.pose.orientation.w = qz, qw
        req.ik_request.pose_stamped = ps
        req.ik_request.timeout = Duration(seconds=self.ik_timeout).to_msg()
        res = self._wait(self.ik_client.call_async(req), 5.0, 'IK service')
        if res.error_code.val != 1:
            return None
        sol = dict(zip(res.solution.joint_state.name, res.solution.joint_state.position))
        return [sol[j] for j in self.arm_joints]

    def tcp_to_link(self, tcp_position):
        """With the gripper pointing down, ik_link is tcp_offset directly above the gripper centre (TCP)."""
        return np.asarray(tcp_position, np.float64) + np.array([0.0, 0.0, self.tcp_offset])

    def grasp_rotation(self, yaw):
        return build_grasp_rotation(self.approach_axis, self.closing_axis, yaw, self.roll_offset)

    def _segment_time(self, q0, q1):
        dq = max(abs(a - b) for a, b in zip(q0, q1))
        return max(self.min_segment_time, dq / self.max_joint_speed)

    def _run_trajectory(self, client, joint_names, waypoints, times, what):
        goal = FollowJointTrajectory.Goal()
        goal.trajectory.joint_names = list(joint_names)
        for q, t in zip(waypoints, times):
            pt = JointTrajectoryPoint()
            pt.positions = [float(x) for x in q]
            pt.time_from_start = Duration(seconds=float(t)).to_msg()
            goal.trajectory.points.append(pt)
        handle = self._wait(client.send_goal_async(goal), 5.0, f'{what} (send)')
        if not handle.accepted:
            raise GraspError(f'{what} rejected by the controller')
        res = self._wait(handle.get_result_async(), times[-1] + 10.0, what)
        if res.status != GoalStatus.STATUS_SUCCEEDED or res.result.error_code != 0:
            raise GraspError(f'{what} failed (status={res.status}, '
                             f'error={res.result.error_code} {res.result.error_string})')

    def move_through(self, waypoints, what='arm motion'):
        for q in waypoints:
            w = q[self.wrist_idx]
            if not (self.wrist_lo - 1e-6 <= w <= self.wrist_hi + 1e-6):
                raise GraspError(f'{what}: joint 6 at {math.degrees(w):.0f}° is out of range')
        q_prev = self.current_arm_joints()
        times, t = [], 0.0
        for q in waypoints:
            t += self._segment_time(q_prev, q)
            times.append(t)
            q_prev = q
        self._run_trajectory(self.arm_client, self.arm_joints, waypoints, times, what)

    def move_to_joints(self, q, what='arm motion'):
        self.move_through([q], what)

    def gripper(self, position, what):
        if self.gripper_mode == 'trajectory':
            self._run_trajectory(self.gripper_client, [self.gripper_joint],
                                 [[position]], [1.0], what)
            return
        goal = GripperCommand.Goal()
        goal.command.position = float(position)
        goal.command.max_effort = float(self.gripper_effort)
        handle = self._wait(self.gripper_client.send_goal_async(goal), 5.0, what)
        if not handle.accepted:
            raise GraspError(f'{what} rejected')
        self._wait(handle.get_result_async(), 10.0, what)   # "stalled" is normal when holding an object

    # ================================================================ grasp planning
    def grasp_point(self, cand):
        p = cand.center_base.copy()
        p[2] = max(p[2] - self.grasp_depth, self.min_grasp_z)
        return p

    def plan_above(self, p, yaw, height):
        """Plan the gripper centre `height` above point p (base_link), gripper pointing down.
        A parallel gripper at 0° and 180° is equivalent, so try both and pick the one with
        joint 6 in range and the smallest joint-6 rotation. Returns (joints, yaw)."""
        p = np.asarray(p, np.float64) + np.array([0.0, 0.0, height])
        seed = self.current_arm_joints()
        best = None
        for y in yaw_candidates(yaw, self.current_closing_yaw()):
            q = self.compute_ik(self.tcp_to_link(p), self.grasp_rotation(y), seed)
            if q is None:
                continue
            cost = abs(q[self.wrist_idx] - seed[self.wrist_idx])
            if best is None or cost < best[2]:
                best = (q, y, cost)
        if best is None:
            raise GraspError(f'No IK solution: {np.round(p, 3)} is out of reach '
                             f'(the gripper can point down about 12-25 cm from the base axis) '
                             f'or joint 6 cannot reach the angle')
        return best[0], best[1]

    def straight_line(self, p_from, p_to, yaw):
        """Move along a straight line with the gripper pointing down, solving IK every descend_step;
        joint 6 must not jump."""
        R = self.grasp_rotation(yaw)
        dist = float(np.linalg.norm(np.asarray(p_to) - np.asarray(p_from)))
        steps = max(2, int(math.ceil(dist / self.descend_step)))
        qs, q = [], self.current_arm_joints()
        for s in np.linspace(0.0, 1.0, steps + 1)[1:]:
            p = (1 - s) * np.asarray(p_from) + s * np.asarray(p_to)
            q_new = self.compute_ik(self.tcp_to_link(p), R, q)
            if q_new is None:
                raise GraspError(f'No IK solution on the straight path at {np.round(p, 3)}')
            if abs(q_new[self.wrist_idx] - q[self.wrist_idx]) > 0.5:
                raise GraspError('Joint 6 would hit its limit on the straight path')
            if max(abs(a - b) for a, b in zip(q_new, q)) > 0.8:
                raise GraspError('Arm configuration would flip on the straight path')
            qs.append(q_new)
            q = q_new
        return qs

    # ================================================================ pick / place
    def pick(self, color=None):
        """Open → home → locate → above → descend → grasp → lift → carry pose.
        Returns (colour, top-face centre in base_link) or None if no graspable block was found."""
        self.stage('preparing', '[1] Open gripper and go home (out of the camera view)')
        self.gripper(self.gripper_open, 'open gripper')
        self.move_to_joints(self.home_joints, 'go home')

        self.stage('locating', f'[2] Get {color or "any"} block position')
        found = None
        for i in range(self.detect_retries):
            found = self.locate(color)
            if found:
                break
            self.stage('locating', f'    No graspable block, retry {i + 1}/{self.detect_retries}')
        if not found:
            return None
        cand, yaw = found
        color = cand.color

        self.set_state(PICKING)
        self.stage('approaching', f'[3] Move {self.approach_height*100:.0f} cm above the {color} block')
        p_grasp = self.grasp_point(cand)
        q, yaw = self.plan_above(p_grasp, yaw, self.approach_height)
        self.get_logger().info(f'    joint 6 = {math.degrees(q[self.wrist_idx]):.0f}°')
        self.move_to_joints(q, 'move above block')

        self.stage('descending', '[4] Descend vertically')
        p_top = p_grasp + np.array([0.0, 0.0, self.approach_height])
        self.move_through(self.straight_line(p_top, p_grasp, yaw), 'descend')

        self.stage('grasping', '[5] Grasp')
        self.gripper(self.gripper_closed, 'close gripper')
        time.sleep(0.5)

        self.stage('lifting', '[6] Lift and move to carry pose')
        self.move_through(self.straight_line(
            p_grasp, p_grasp + np.array([0.0, 0.0, self.lift_height]), yaw), 'lift')
        with self._lock:
            g = self._joint_pos.get(self.gripper_joint)
        if g is not None and abs(g - self.gripper_closed) < self.grasp_check_tolerance:
            raise GraspError('Gripper fully closed; the block was probably missed')
        self.move_to_joints(self.carry_joints, 'move to carry pose')
        return color, cand.center_base

    def place(self, location='place'):
        """Move to a named pose (place / carry / home), release, then go home."""
        poses = {'place': self.place_joints, 'carry': self.carry_joints, 'home': self.home_joints}
        if location not in poses:
            raise GraspError(f'unknown location {location!r}; use one of {sorted(poses)} '
                             f'or use_position:=true with a point')
        self.set_state(PLACING)
        self.stage('moving', f'[8] Move to the {location} pose')
        self.move_to_joints(poses[location], f'move to {location} pose')
        self.stage('releasing', '    Release')
        self.gripper(self.gripper_open, 'release')
        self.set_holding('')
        self.set_state(DONE)
        if location != 'home':
            self.stage('retreating', '    Go home')
            self.move_to_joints(self.home_joints, 'go home')

    def place_at(self, p):
        """Bring the gripper centre to point p (base_link) from above, release, and lift back up."""
        p = np.array(p, np.float64)
        if p[2] < self.min_grasp_z:
            raise GraspError(f'drop point z={p[2]:.3f} m is below min_grasp_z={self.min_grasp_z} m')
        self.set_state(PLACING)
        self.stage('moving', f'[8] Move above the drop point {np.round(p, 3)} m')
        q, yaw = self.plan_above(p, self.current_closing_yaw(), self.approach_height)
        self.move_to_joints(q, 'move above drop point')
        p_top = p + np.array([0.0, 0.0, self.approach_height])
        self.stage('descending', '    Descend vertically')
        self.move_through(self.straight_line(p_top, p, yaw), 'descend to drop point')
        self.stage('releasing', '    Release')
        self.gripper(self.gripper_open, 'release')
        self.set_holding('')
        self.stage('retreating', '    Lift back up')
        self.move_through(self.straight_line(p, p_top, yaw), 'retreat')
        self.set_state(DONE)

    # ================================================================ command API
    def _accept_goal(self, _goal):
        if not self.ready:
            self.get_logger().warn('Goal rejected: arm not ready yet')
            return GoalResponse.REJECT
        if self.autorun:
            self.get_logger().warn('Goal rejected: autorun mode is on')
            return GoalResponse.REJECT
        if self.busy.locked():
            self.get_logger().warn('Goal rejected: arm busy with another command')
            return GoalResponse.REJECT
        return GoalResponse.ACCEPT

    def _run_goal(self, gh, feedback_type, result, body):
        """Common wrapper for action goals: busy lock, feedback/cancel, error → result."""
        if not self.busy.acquire(blocking=False):
            result.message = 'arm busy'
            gh.abort()
            return result

        def on_stage(name):
            fb = feedback_type()
            fb.stage = name
            gh.publish_feedback(fb)
            if gh.is_cancel_requested:
                raise Cancelled()

        self._stage_cb = on_stage
        try:
            body(result)
            if result.success:
                gh.succeed()
            else:
                gh.abort()
        except Cancelled:
            result.success, result.message = False, 'cancelled'
            self.get_logger().info('Goal cancelled')
            gh.canceled()
        except GraspError as e:
            result.success, result.message = False, str(e)
            self.get_logger().error(f'Command failed: {e}')
            self.set_state(ERROR)
            gh.abort()
        finally:
            self._stage_cb = None
            self.busy.release()
        return result

    def _exec_pick(self, gh):
        def body(res):
            color = gh.request.color.strip().lower() or None
            found = self.pick(color)
            if found is None:
                res.success, res.message = False, f'no graspable {color or ""} block found'.replace('  ', ' ')
                self.set_state(IDLE)
                return
            res.color, pos = found
            res.position = Point(x=float(pos[0]), y=float(pos[1]), z=float(pos[2]))
            self.set_holding(res.color)
            self.set_state(HOLDING)
            res.success, res.message = True, f'holding the {res.color} block'
        return self._run_goal(gh, PickBlock.Feedback, PickBlock.Result(), body)

    def _exec_place(self, gh):
        def body(res):
            req = gh.request
            if req.use_position:
                self.place_at([req.position.x, req.position.y, req.position.z])
                where = f'({req.position.x:.3f}, {req.position.y:.3f}, {req.position.z:.3f})'
            else:
                where = req.location.strip().lower() or 'place'
                self.place(where)
            res.success, res.message = True, f'released at {where}'
            self.set_state(IDLE)
        return self._run_goal(gh, PlaceBlock.Feedback, PlaceBlock.Result(), body)

    def _srv_locate(self, req, res):
        if not self.ready:
            res.success, res.message = False, 'arm not ready yet'
            return res
        if not self.busy.acquire(blocking=False):
            res.success, res.message = False, 'arm busy'
            return res
        try:
            if req.go_home:
                self.move_to_joints(self.home_joints, 'go home')
            msg = self.fresh_blocks()
            if msg is None:
                res.success, res.message = False, 'no fresh /vision/blocks (is the vision node running?)'
                return res
            want = req.color.strip().lower()
            infos = []
            for c in self.blocks_to_candidates(msg):
                if want and c.color != want:
                    continue
                info = BlockInfo()
                info.color, info.confidence = c.color, c.confidence
                info.position = Point(x=float(c.center_base[0]), y=float(c.center_base[1]),
                                      z=float(c.center_base[2]))
                fits = True
                if c.corners_base is not None:
                    g = select_grasp(c.corners_base, self.gripper_max_opening)
                    fits = g is not None
                    if g is not None:
                        info.grasp_yaw, info.width = float(g['yaw']), float(g['width'])
                info.graspable = bool(c.should_grasp and fits and c.confidence >= self.min_confidence)
                infos.append(info)
            infos.sort(key=lambda b: (not b.graspable, -b.confidence))
            res.blocks = infos
            res.success = True
            res.message = f'{len(infos)} block(s), {sum(b.graspable for b in infos)} graspable'
        except GraspError as e:
            res.success, res.message = False, str(e)
        finally:
            self.busy.release()
        return res

    # ================================================================ autonomous mode
    def wait_vehicle(self, color):
        if not self.wait_for_vehicle:
            return
        log = self.get_logger()
        with self._lock:
            self._arrived = None
        t0 = time.monotonic()
        self.set_holding(color)
        self.set_state(HOLDING)
        log.info(f'[7] Holding {color}; waiting for the vehicle to reach the {color} basket '
                 f'(/vehicle/arrived)')
        while rclpy.ok():
            if self.vehicle_timeout > 0 and time.monotonic() - t0 > self.vehicle_timeout:
                raise GraspError(f'Timed out waiting for the vehicle ({self.vehicle_timeout:.0f} s); '
                                 f'block is still in the gripper')
            with self._lock:
                a, self._arrived = self._arrived, None
            if a is not None:
                if a[0] == color:
                    log.info(f'    Vehicle reached the {color} basket')
                    return
                log.error(f'    Vehicle reports {a[0]} but the arm holds {color}; '
                          f'not releasing, still waiting')
                self.set_state(ERROR)
                self.set_state(HOLDING)
            time.sleep(0.05)

    def run_task(self):
        while rclpy.ok():
            with self.busy:
                try:
                    found = self.pick()
                    if found is None:
                        self.get_logger().info('No block to pick right now')
                    else:
                        color = found[0]
                        self.wait_vehicle(color)
                        self.place()
                        self.get_logger().info(f'{color} block done ✔')
                    self.set_state(IDLE)
                except GraspError as e:
                    self.get_logger().error(f'Task failed: {e}')
                    self.set_state(ERROR)
            if not self.loop:
                break
            time.sleep(1.0)


def main():
    rclpy.init()
    node = ArmTaskNode()
    executor = MultiThreadedExecutor(num_threads=8)
    executor.add_node(node)
    threading.Thread(target=executor.spin, daemon=True).start()
    try:
        node.wait_for_ready()
        if node.autorun:
            node.run_task()
        else:
            while rclpy.ok():
                time.sleep(0.5)
    except KeyboardInterrupt:
        pass
    finally:
        executor.shutdown()
        node.destroy_node()
        rclpy.try_shutdown()


if __name__ == '__main__':
    main()
