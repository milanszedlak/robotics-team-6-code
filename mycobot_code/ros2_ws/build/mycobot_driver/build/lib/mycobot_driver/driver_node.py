"""ROS 2 driver for the myCobot 280 Pi. Runs ON THE ARM'S PI and owns the serial port.

Other machines (laptop / NUC) use it over DDS on the Ethernet cable; they only need the
same ROS_DOMAIN_ID.

Provides
  /joint_states                                (sensor_msgs/JointState, radians)
  TF base_link → link6_flange                  (from the arm's forward kinematics)
  /arm/flange_pose                             (geometry_msgs/PoseStamped, base_link)
  /arm_controller/follow_joint_trajectory      (control_msgs/FollowJointTrajectory)  -- what MoveIt /
  /gripper_action_controller/gripper_cmd       (control_msgs/GripperCommand)            mycobot_vision_grasp use
  /arm/joint_command                           (std_msgs/Float64MultiArray, 6 angles in DEGREES)
  /arm/go_home, /arm/stop, /arm/power_on, /arm/release_servos,
  /arm/open_gripper, /arm/close_gripper        (std_srvs/Trigger)

Backends (parameter `backend`): serial = the real arm (default), fake = simulated arm for testing.
"""
import threading
import time

import rclpy
from geometry_msgs.msg import PoseStamped, TransformStamped
from rclpy.action import ActionServer, CancelResponse, GoalResponse
from rclpy.callback_groups import MutuallyExclusiveCallbackGroup, ReentrantCallbackGroup
from rclpy.executors import MultiThreadedExecutor
from rclpy.node import Node
from sensor_msgs.msg import JointState
from std_msgs.msg import Float64MultiArray
from std_srvs.srv import Trigger
from tf2_ros import TransformBroadcaster

from .conversions import (clamp_angles, deg_to_rad, gripper_position_to_value,
                          gripper_value_to_position, rad_to_deg, reached, speed_percent)
from .hardware import ArmError, open_backend
from .kinematics import fk, matrix_to_quat

try:
    from control_msgs.action import FollowJointTrajectory, GripperCommand
    HAVE_CONTROL_MSGS = True
except ImportError:                    # sudo apt install ros-jazzy-control-msgs
    HAVE_CONTROL_MSGS = False

DEFAULT_JOINTS = ['link1_to_link2', 'link2_to_link3', 'link3_to_link4',
                  'link4_to_link5', 'link5_to_link6', 'link6_to_link6_flange']

ARM_ERRORS = (OSError, ArmError, ValueError)      # serial.SerialException is an OSError


class MyCobotDriver(Node):
    def __init__(self):
        super().__init__('mycobot_driver')
        P = self.declare_parameter
        backend = P('backend', 'serial').value
        serial_port = P('serial_port', '/dev/ttyAMA0').value
        baud = P('baud', 1000000).value
        self.joint_names = list(P('joint_names', DEFAULT_JOINTS).value)
        self.rate = P('publish_rate', 10.0).value
        self.default_speed = P('default_speed', 40).value
        self.max_deg_per_s = P('max_deg_per_s_at_speed_100', 160.0).value
        self.home_deg = list(P('home_angles_deg', [0.0] * 6).value)
        self.goal_tol = P('goal_tolerance_deg', 2.0).value
        self.waypoint_tol = P('waypoint_tolerance_deg', 6.0).value
        self.min_point_interval = P('min_point_interval', 0.3).value
        self.extra_time = P('extra_time', 3.0).value
        self.publish_gripper = P('publish_gripper_joint', True).value
        self.gripper_joint = P('gripper_joint', 'gripper_controller').value
        self.gripper_open = P('gripper_open_position', 0.0).value
        self.gripper_closed = P('gripper_closed_position', -0.7).value
        self.gripper_speed = P('gripper_speed', 50).value
        self.gripper_time = P('gripper_move_time', 1.5).value
        self.publish_tf = P('publish_tf', True).value
        self.base_frame = P('base_frame', 'base_link').value
        self.flange_frame = P('flange_frame', 'link6_flange').value

        self.get_logger().info(f'Opening arm backend "{backend}"'
                               + (f' on {serial_port} @ {baud}' if backend == 'serial' else ''))
        self.arm = open_backend(backend, serial_port, baud)
        self.angles_deg = None          # latest reading, degrees
        self.gripper_value = 100
        self.state_lock = threading.Lock()
        self.motion_lock = threading.Lock()   # one motion command source at a time

        poll_cb = MutuallyExclusiveCallbackGroup()
        cb = ReentrantCallbackGroup()
        self.js_pub = self.create_publisher(JointState, '/joint_states', 10)
        self.flange_pub = self.create_publisher(PoseStamped, '/arm/flange_pose', 10)
        self.tf_pub = TransformBroadcaster(self) if self.publish_tf else None
        self.create_timer(1.0 / self.rate, self._poll, callback_group=poll_cb)
        self.create_subscription(Float64MultiArray, '/arm/joint_command', self._on_joint_command, 10,
                                 callback_group=cb)
        for name, fn in [('go_home', self._srv_home), ('stop', self._srv_stop),
                         ('power_on', self._srv_power_on), ('release_servos', self._srv_release),
                         ('open_gripper', self._srv_open), ('close_gripper', self._srv_close)]:
            self.create_service(Trigger, f'/arm/{name}', fn, callback_group=cb)

        if HAVE_CONTROL_MSGS:
            ActionServer(self, FollowJointTrajectory,
                         P('arm_action', '/arm_controller/follow_joint_trajectory').value,
                         execute_callback=self._exec_trajectory, goal_callback=self._check_trajectory,
                         cancel_callback=lambda _: CancelResponse.ACCEPT, callback_group=cb)
            ActionServer(self, GripperCommand,
                         P('gripper_action', '/gripper_action_controller/gripper_cmd').value,
                         execute_callback=self._exec_gripper,
                         cancel_callback=lambda _: CancelResponse.ACCEPT, callback_group=cb)
        else:
            self.get_logger().warn('control_msgs not installed: trajectory and gripper actions are '
                                   'DISABLED (sudo apt install ros-jazzy-control-msgs). '
                                   'Topics and services still work.')

    # ------------------------------------------------------------------ state
    def _poll(self):
        try:
            deg = self.arm.get_angles()
        except ARM_ERRORS as e:
            self.get_logger().warn(f'Cannot read arm: {e}', throttle_duration_sec=5.0)
            return
        if self.publish_gripper:
            try:                            # no gripper fitted -> keep the last value
                g = self.arm.call('get_gripper_value')
                if isinstance(g, (int, float)) and g >= 0:
                    self.gripper_value = g
            except ARM_ERRORS:
                pass
        first = self.angles_deg is None
        with self.state_lock:
            self.angles_deg = deg
        if first:
            self.get_logger().info(f'Arm connected. Joint angles (deg): {[round(a, 1) for a in deg]}')
        stamp = self.get_clock().now().to_msg()
        msg = JointState()
        msg.header.stamp = stamp
        msg.name = list(self.joint_names)
        msg.position = deg_to_rad(deg)
        if self.publish_gripper:
            msg.name.append(self.gripper_joint)
            msg.position.append(gripper_value_to_position(
                self.gripper_value, self.gripper_open, self.gripper_closed))
        self.js_pub.publish(msg)
        self._publish_flange(deg_to_rad(deg), stamp)

    def _publish_flange(self, q, stamp):
        T = fk(q)
        x, y, z = (float(v) for v in T[:3, 3])
        qx, qy, qz, qw = (float(v) for v in matrix_to_quat(T[:3, :3]))
        pose = PoseStamped()
        pose.header.stamp, pose.header.frame_id = stamp, self.base_frame
        pose.pose.position.x, pose.pose.position.y, pose.pose.position.z = x, y, z
        o = pose.pose.orientation
        o.x, o.y, o.z, o.w = qx, qy, qz, qw
        self.flange_pub.publish(pose)
        if self.tf_pub is not None:
            t = TransformStamped()
            t.header.stamp, t.header.frame_id = stamp, self.base_frame
            t.child_frame_id = self.flange_frame
            t.transform.translation.x, t.transform.translation.y, t.transform.translation.z = x, y, z
            r = t.transform.rotation
            r.x, r.y, r.z, r.w = qx, qy, qz, qw
            self.tf_pub.sendTransform(t)

    def current_deg(self):
        with self.state_lock:
            return list(self.angles_deg) if self.angles_deg else None

    def move_and_wait(self, goal_deg, speed, timeout, tol, should_stop=lambda: False):
        """Send a joint goal (degrees) and block until reached / timeout / cancelled."""
        goal_deg = clamp_angles(goal_deg)
        self.arm.send_angles(goal_deg, speed)
        end = time.monotonic() + timeout
        while time.monotonic() < end:
            if should_stop():
                self.arm.call('stop')
                return 'cancelled'
            cur = self.current_deg()
            if cur and reached(cur, goal_deg, tol):
                return 'ok'
            time.sleep(0.05)
        return 'timeout'

    # ------------------------------------------------------------------ simple interfaces
    def _on_joint_command(self, msg):
        if len(msg.data) != 6:
            self.get_logger().error('/arm/joint_command needs exactly 6 angles in degrees')
            return
        try:
            self.arm.send_angles(clamp_angles(msg.data), self.default_speed)
        except ARM_ERRORS as e:
            self.get_logger().error(f'joint_command failed: {e}')

    def _trigger(self, res, fn, ok_msg):
        try:
            fn()
            res.success, res.message = True, ok_msg
        except ARM_ERRORS as e:
            res.success, res.message = False, str(e)
        return res

    def _srv_home(self, _, res):
        def go():
            with self.motion_lock:
                r = self.move_and_wait(self.home_deg, self.default_speed, 15.0, self.goal_tol)
            if r != 'ok':
                raise ArmError(f'go_home: {r}')
        return self._trigger(res, go, 'at home')

    def _srv_stop(self, _, res):
        return self._trigger(res, lambda: self.arm.call('stop'), 'stopped')

    def _srv_power_on(self, _, res):
        return self._trigger(res, lambda: self.arm.call('power_on'), 'servos powered')

    def _srv_release(self, _, res):
        self.get_logger().warn('Releasing all servos: the arm will go limp, support it!')
        return self._trigger(res, lambda: self.arm.call('release_all_servos'), 'servos released')

    def _set_gripper_and_wait(self, value):
        self.arm.call('set_gripper_value', int(value), int(self.gripper_speed))
        time.sleep(self.gripper_time)

    def _srv_open(self, _, res):
        return self._trigger(res, lambda: self._set_gripper_and_wait(100), 'gripper open')

    def _srv_close(self, _, res):
        return self._trigger(res, lambda: self._set_gripper_and_wait(0), 'gripper closed')

    # ------------------------------------------------------------------ FollowJointTrajectory
    def _check_trajectory(self, goal):
        names = list(goal.trajectory.joint_names)
        if sorted(names) != sorted(self.joint_names):
            self.get_logger().error(f'Rejecting trajectory: joints {names} != {self.joint_names}')
            return GoalResponse.REJECT
        if not goal.trajectory.points:
            return GoalResponse.REJECT
        return GoalResponse.ACCEPT

    def _exec_trajectory(self, gh):
        traj = gh.request.trajectory
        order = [list(traj.joint_names).index(n) for n in self.joint_names]
        result = FollowJointTrajectory.Result()

        # MoveIt sends dense trajectories; the arm only takes position goals, so thin them out.
        pts, last_t = [], -1e9
        for i, p in enumerate(traj.points):
            t = p.time_from_start.sec + p.time_from_start.nanosec * 1e-9
            if t - last_t >= self.min_point_interval or i == len(traj.points) - 1:
                pts.append((t, rad_to_deg([p.positions[k] for k in order])))
                last_t = t

        with self.motion_lock:
            prev_t, prev_deg = 0.0, self.current_deg()
            if prev_deg is None:
                gh.abort()
                result.error_code = FollowJointTrajectory.Result.INVALID_GOAL
                result.error_string = 'no joint state from the arm yet'
                return result
            for i, (t, deg) in enumerate(pts):
                final = i == len(pts) - 1
                dt = max(t - prev_t, 0.05)
                speed = speed_percent(prev_deg, deg, dt, self.max_deg_per_s)
                try:
                    status = self.move_and_wait(
                        deg, speed, dt + (self.extra_time if final else 1.0),
                        self.goal_tol if final else self.waypoint_tol,
                        should_stop=lambda: gh.is_cancel_requested)
                except ARM_ERRORS as e:
                    gh.abort()
                    result.error_code = FollowJointTrajectory.Result.INVALID_GOAL
                    result.error_string = str(e)
                    return result
                fb = FollowJointTrajectory.Feedback()
                fb.joint_names = list(self.joint_names)
                fb.desired.positions = deg_to_rad(deg)
                fb.actual.positions = deg_to_rad(self.current_deg() or deg)
                gh.publish_feedback(fb)
                if status == 'cancelled':
                    gh.canceled()
                    result.error_string = 'cancelled'
                    return result
                if status == 'timeout' and final:
                    gh.abort()
                    result.error_code = FollowJointTrajectory.Result.GOAL_TOLERANCE_VIOLATED
                    result.error_string = f'did not reach the final point within {self.goal_tol} deg'
                    return result
                prev_t, prev_deg = t, deg
        gh.succeed()
        result.error_code = FollowJointTrajectory.Result.SUCCESSFUL
        return result

    # ------------------------------------------------------------------ GripperCommand
    def _exec_gripper(self, gh):
        pos = gh.request.command.position
        value = gripper_position_to_value(pos, self.gripper_open, self.gripper_closed)
        result = GripperCommand.Result()
        try:
            self.arm.call('set_gripper_value', value, int(self.gripper_speed))
        except ARM_ERRORS as e:
            self.get_logger().error(f'gripper failed: {e}')
            gh.abort()
            return result
        end = time.monotonic() + self.gripper_time
        while time.monotonic() < end:
            if gh.is_cancel_requested:
                gh.canceled()
                return result
            time.sleep(0.05)
        actual = gripper_value_to_position(self.gripper_value, self.gripper_open, self.gripper_closed)
        result.position = actual
        result.reached_goal = abs(self.gripper_value - value) <= 5
        result.stalled = not result.reached_goal       # usually: closed on an object
        gh.succeed()
        return result


def main():
    rclpy.init()
    node = MyCobotDriver()
    ex = MultiThreadedExecutor(num_threads=4)
    ex.add_node(node)
    try:
        ex.spin()
    except KeyboardInterrupt:
        pass
    finally:
        node.arm.close()
        node.destroy_node()
        rclpy.try_shutdown()


if __name__ == '__main__':
    main()
