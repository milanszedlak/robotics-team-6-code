"""mycobot_driver: the myCobot 280 Pi's ROS 2 driver ("mycobot_ros2 — Drivers & Gripper Control").

Runs ON THE ARM'S PI and is the only program that talks to the arm's serial port. It has no
planning or task logic: MoveIt 2 and the task coordinator on the NUC (for now the laptop) send it
trajectories and gripper goals; it executes them and reports the arm's state.

Publishes
  /joint_states                      sensor_msgs/JointState   joint1..6 [rad] + gripper_joint [m], 20 Hz
  /arm/status                        std_msgs/String          IDLE | MOVING | ERROR | RELEASED
  (/robot_description + TF come from robot_state_publisher, started by the same launch file)

Actions (what MoveIt 2's simple controller manager talks to)
  /arm_controller/follow_joint_trajectory   control_msgs/FollowJointTrajectory
  /gripper_controller/gripper_cmd           control_msgs/GripperCommand   position = finger gap [m]

Topics for quick manual control (CLI / simple scripts)
  /arm_controller/joint_trajectory   trajectory_msgs/JointTrajectory   same as the action, no feedback
  /arm/joint_command                 std_msgs/Float64MultiArray        6 joint angles in DEGREES
  /arm/gripper_command               std_msgs/Int32                    0 = closed .. 100 = open

Services (std_srvs/Trigger)
  /arm/stop  /arm/home  /arm/power_on  /arm/release_servos  /arm/open_gripper  /arm/close_gripper

One arm motion runs at a time: a new trajectory / joint command while the arm is moving is
rejected. /arm/stop cancels whatever is running.
"""
import math
import threading
import time

import rclpy
from control_msgs.action import FollowJointTrajectory, GripperCommand
from rclpy.action import ActionServer, CancelResponse, GoalResponse
from rclpy.callback_groups import MutuallyExclusiveCallbackGroup, ReentrantCallbackGroup
from rclpy.executors import ExternalShutdownException, MultiThreadedExecutor
from rclpy.node import Node
from sensor_msgs.msg import JointState
from std_msgs.msg import Float64MultiArray, Int32, String
from std_srvs.srv import Trigger
from trajectory_msgs.msg import JointTrajectory, JointTrajectoryPoint

from .hardware import ArmError, open_backend
from .trajectory import TrajectoryError, check_limits, estimate_duration, plan_commands

ARM_ERRORS = (OSError, ArmError, ValueError)        # serial.SerialException is an OSError
FJT = FollowJointTrajectory.Result


class Cancelled(Exception):
    pass


class MotionFailed(Exception):
    def __init__(self, code, msg):
        super().__init__(msg)
        self.code = code


def duration_to_s(d):
    return d.sec + d.nanosec * 1e-9


class MyCobotDriver(Node):

    def __init__(self):
        super().__init__('mycobot_driver')
        P = self.declare_parameter
        backend = P('backend', 'serial').value
        port = P('serial_port', '/dev/ttyAMA0').value
        baud = P('baud', 1000000).value
        self.rate = P('publish_rate', 20.0).value
        self.gripper_every = max(1, P('gripper_poll_divider', 5).value)
        self.joint_names = list(P('joint_names', [f'joint{i}' for i in range(1, 7)]).value)
        self.gripper_joint = P('gripper_joint_name', 'gripper_joint').value
        self.gripper_max_gap = P('gripper_max_gap', 0.04).value
        self.home_deg = list(P('home_deg', [0.0] * 6).value)
        self.default_speed = P('default_speed', 40).value
        self.min_speed = P('min_speed', 5).value
        self.max_deg_per_s = P('max_deg_per_s_at_speed_100', 160.0).value
        self.min_period = P('min_command_period', 0.1).value
        self.goal_tol = P('goal_tolerance_deg', 2.0).value
        self.settle_time = P('goal_settle_timeout', 3.0).value
        self.gripper_speed = P('gripper_speed', 50).value
        self.gripper_time = P('gripper_move_time', 1.5).value
        self.gripper_tol = P('gripper_tolerance', 5).value

        self.get_logger().info(f'Opening arm backend "{backend}"'
                               + (f' on {port} @ {baud}' if backend == 'serial' else ''))
        self.arm = open_backend(backend, port, baud)

        self._lock = threading.Lock()           # protects the state fields below
        self.angles_deg = None                  # last joint angles read [deg]
        self.gripper_value = None               # last gripper value read, 0..100
        self.status = 'IDLE'
        self.released = False
        self._motion = threading.Lock()         # held while an arm motion runs
        self._gripper = threading.Lock()        # held while a gripper motion runs
        self._stop = threading.Event()
        self._polls = 0

        poll_cb, cb = MutuallyExclusiveCallbackGroup(), ReentrantCallbackGroup()
        self.js_pub = self.create_publisher(JointState, '/joint_states', 10)
        self.status_pub = self.create_publisher(String, '/arm/status', 10)

        ActionServer(self, FollowJointTrajectory, '/arm_controller/follow_joint_trajectory',
                     execute_callback=self._execute_trajectory_goal,
                     goal_callback=self._on_trajectory_goal,
                     cancel_callback=lambda _: CancelResponse.ACCEPT, callback_group=cb)
        ActionServer(self, GripperCommand, '/gripper_controller/gripper_cmd',
                     execute_callback=self._execute_gripper_goal,
                     goal_callback=self._on_gripper_goal,
                     cancel_callback=lambda _: CancelResponse.ACCEPT, callback_group=cb)

        self.create_subscription(JointTrajectory, '/arm_controller/joint_trajectory',
                                 self._on_trajectory_topic, 10, callback_group=cb)
        self.create_subscription(Float64MultiArray, '/arm/joint_command',
                                 self._on_joint_command, 10, callback_group=cb)
        self.create_subscription(Int32, '/arm/gripper_command',
                                 self._on_gripper_command, 10, callback_group=cb)

        for name, fn in [('stop', self._srv_stop), ('home', self._srv_home),
                         ('power_on', self._srv_power_on), ('release_servos', self._srv_release),
                         ('open_gripper', self._srv_open), ('close_gripper', self._srv_close)]:
            self.create_service(Trigger, f'/arm/{name}', fn, callback_group=cb)

        self.create_timer(1.0 / self.rate, self._poll, callback_group=poll_cb)
        self.get_logger().info('mycobot_driver ready: /joint_states, '
                               '/arm_controller/follow_joint_trajectory, /gripper_controller/gripper_cmd')

    # ================================================================ state (20 Hz)
    def _poll(self):
        try:
            deg = self.arm.get_angles()
        except ARM_ERRORS as e:
            self.get_logger().warn(f'Cannot read arm: {e}', throttle_duration_sec=5.0)
            self._publish_status('ERROR')
            return
        grip = None
        if self._polls % self.gripper_every == 0:
            try:
                g = self.arm.call('get_gripper_value')
                grip = int(g) if isinstance(g, (int, float)) and 0 <= g <= 100 else None
            except ARM_ERRORS:
                grip = None
        self._polls += 1
        with self._lock:
            self.angles_deg = deg
            if grip is not None:
                self.gripper_value = grip
            gval = self.gripper_value

        js = JointState()
        js.header.stamp = self.get_clock().now().to_msg()
        js.name = list(self.joint_names)
        js.position = [math.radians(a) for a in deg]
        if gval is not None:
            js.name.append(self.gripper_joint)
            js.position.append(self._value_to_gap(gval))
        self.js_pub.publish(js)

        if self.released:
            status = 'RELEASED'
        elif self._motion.locked() or self._gripper.locked():
            status = 'MOVING'
        else:
            status = 'IDLE'
        self._publish_status(status)

    def _publish_status(self, status):
        self.status = status
        self.status_pub.publish(String(data=status))

    def _current_deg(self):
        with self._lock:
            if self.angles_deg is not None:
                return list(self.angles_deg)
        return self.arm.get_angles()

    def _value_to_gap(self, v):
        return self.gripper_max_gap * max(0, min(100, v)) / 100.0

    def _gap_to_value(self, gap):
        return int(round(100.0 * max(0.0, min(self.gripper_max_gap, gap)) / self.gripper_max_gap))

    # ================================================================ arm motion
    def _points_from_msg(self, traj):
        """JointTrajectory → [(t, 6 angles deg)], filling joints it leaves out with current angles."""
        names = list(traj.joint_names)
        unknown = [n for n in names if n not in self.joint_names]
        if unknown:
            raise MotionFailed(FJT.INVALID_JOINTS, f'unknown joints {unknown}; expected {self.joint_names}')
        if len(set(names)) != len(names):
            raise MotionFailed(FJT.INVALID_JOINTS, 'duplicate joint names')
        current = self._current_deg()
        points = []
        for p in traj.points:
            if len(p.positions) != len(names):
                raise MotionFailed(FJT.INVALID_GOAL, 'point has a different number of positions than joint_names')
            deg = list(current)
            for n, v in zip(names, p.positions):
                deg[self.joint_names.index(n)] = math.degrees(v)
            points.append((duration_to_s(p.time_from_start), deg))
        return current, points

    def _run_trajectory(self, traj, goal_time_tolerance=0.0, feedback=None):
        """Play back a trajectory. Caller holds self._motion. Raises Cancelled / MotionFailed."""
        try:
            current, points = self._points_from_msg(traj)
            commands, duration = plan_commands(current, points, self.max_deg_per_s, self.min_period,
                                               self.default_speed, self.min_speed)
        except TrajectoryError as e:
            raise MotionFailed(FJT.INVALID_GOAL, str(e))
        if duration <= 1e-6:     # untimed single target: allow for the move itself
            duration = estimate_duration(current, commands[-1][1], commands[-1][2], self.max_deg_per_s)
        self.released = False
        final = commands[-1][1]
        self.get_logger().info(f'Trajectory: {len(points)} points ({len(commands)} sent), {duration:.2f} s')

        start = time.monotonic()
        for send_at, target, speed in commands:
            self._sleep_until(start + send_at)
            try:
                self.arm.send_angles(target, speed)
            except ARM_ERRORS as e:
                raise MotionFailed(FJT.PATH_TOLERANCE_VIOLATED, f'serial error: {e}')
            if feedback:
                feedback(target)

        # wait for the arm to reach the last point
        tol = goal_time_tolerance if goal_time_tolerance > 0 else self.settle_time
        self._sleep_until(start + duration)
        deadline = start + duration + tol
        while True:
            err = max(abs(a - b) for a, b in zip(self._current_deg(), final))
            if err <= self.goal_tol:
                return
            if time.monotonic() > deadline:
                raise MotionFailed(FJT.GOAL_TOLERANCE_VIOLATED,
                                   f'arm is still {err:.1f} deg from the goal after {tol:.1f} s extra')
            self._sleep_until(time.monotonic() + 0.05)

    def _sleep_until(self, t):
        while True:
            if self._stop.is_set():
                raise Cancelled()
            left = t - time.monotonic()
            if left <= 0:
                return
            time.sleep(min(left, 0.02))

    def _halt(self):
        try:
            self.arm.call('stop')
        except ARM_ERRORS as e:
            self.get_logger().error(f'stop failed: {e}')

    def _begin_motion(self):
        """Take the motion lock without waiting. False = arm busy."""
        if not self._motion.acquire(blocking=False):
            return False
        self._stop.clear()
        return True

    # ---- FollowJointTrajectory action
    def _on_trajectory_goal(self, goal):
        if not self._begin_motion():
            self.get_logger().warn('Trajectory rejected: arm is busy')
            return GoalResponse.REJECT
        return GoalResponse.ACCEPT

    def _execute_trajectory_goal(self, gh):
        result = FollowJointTrajectory.Result()
        traj = gh.request.trajectory
        fb = FollowJointTrajectory.Feedback()
        fb.joint_names = list(self.joint_names)

        def feedback(target_deg):
            fb.header.stamp = self.get_clock().now().to_msg()
            fb.desired = JointTrajectoryPoint(positions=[math.radians(a) for a in target_deg])
            actual = self._current_deg()
            fb.actual = JointTrajectoryPoint(positions=[math.radians(a) for a in actual])
            fb.error = JointTrajectoryPoint(positions=[math.radians(d - a) for d, a in zip(target_deg, actual)])
            gh.publish_feedback(fb)
            if gh.is_cancel_requested:
                self._stop.set()

        # cancel requests arrive between feedback calls too: watch for them
        watcher_done = threading.Event()

        def watch_cancel():
            while not watcher_done.wait(0.05):
                if gh.is_cancel_requested:
                    self._stop.set()
                    return
        threading.Thread(target=watch_cancel, daemon=True).start()
        try:
            self._run_trajectory(traj, duration_to_s(gh.request.goal_time_tolerance), feedback)
            result.error_code = FJT.SUCCESSFUL
            gh.succeed()
            self.get_logger().info('Trajectory done')
        except Cancelled:
            self._halt()
            result.error_string = 'cancelled / stopped'
            if gh.is_cancel_requested:
                gh.canceled()
            else:
                result.error_code = FJT.PATH_TOLERANCE_VIOLATED
                gh.abort()
            self.get_logger().warn('Trajectory stopped')
        except MotionFailed as e:
            self._halt()
            result.error_code, result.error_string = e.code, str(e)
            gh.abort()
            self.get_logger().error(f'Trajectory failed: {e}')
        finally:
            watcher_done.set()
            self._motion.release()
        return result

    # ---- topic versions (fire and forget)
    def _on_trajectory_topic(self, msg):
        self._run_unattended('trajectory', lambda: self._run_trajectory(msg))

    def _on_joint_command(self, msg):
        if len(msg.data) != 6:
            self.get_logger().error(f'/arm/joint_command needs 6 angles in degrees, got {len(msg.data)}')
            return
        self._run_unattended('joint command', lambda: self._move_to_deg(list(msg.data)))

    def _move_to_deg(self, deg, speed=None):
        try:
            check_limits(deg)
        except TrajectoryError as e:
            raise MotionFailed(FJT.INVALID_GOAL, str(e))
        traj = JointTrajectory(joint_names=list(self.joint_names))
        traj.points = [JointTrajectoryPoint(positions=[math.radians(a) for a in deg])]
        self._run_trajectory(traj)

    def _run_unattended(self, what, fn):
        if not self._begin_motion():
            self.get_logger().warn(f'{what} rejected: arm is busy')
            return False, 'arm is busy'
        try:
            fn()
            self.get_logger().info(f'{what} done')
            return True, f'{what} done'
        except Cancelled:
            self._halt()
            self.get_logger().warn(f'{what} stopped')
            return False, f'{what} stopped'
        except MotionFailed as e:
            self._halt()
            self.get_logger().error(f'{what} failed: {e}')
            return False, f'{what} failed: {e}'
        finally:
            self._motion.release()

    # ================================================================ gripper
    def _on_gripper_goal(self, goal):
        if self._gripper.locked():
            self.get_logger().warn('Gripper goal rejected: gripper is busy')
            return GoalResponse.REJECT
        return GoalResponse.ACCEPT

    def _move_gripper(self, value):
        """Move the gripper to value 0..100 and wait. Returns the value it ended at."""
        with self._gripper:
            self.arm.call('set_gripper_value', int(max(0, min(100, value))), int(self.gripper_speed))
            time.sleep(self.gripper_time)
            got = self.arm.call('get_gripper_value')
            got = int(got) if isinstance(got, (int, float)) and 0 <= got <= 100 else None
            if got is not None:
                with self._lock:
                    self.gripper_value = got
            return got

    def _execute_gripper_goal(self, gh):
        result = GripperCommand.Result()
        target = self._gap_to_value(gh.request.command.position)
        try:
            got = self._move_gripper(target)
        except ARM_ERRORS as e:
            self.get_logger().error(f'Gripper failed: {e}')
            gh.abort()
            return result
        if got is None:
            got = target
        result.position = self._value_to_gap(got)
        result.reached_goal = abs(got - target) <= self.gripper_tol
        # closing on an object stops the fingers early: that is a successful grasp
        result.stalled = not result.reached_goal
        gh.succeed()
        self.get_logger().info(f'Gripper: target {target}, now {got}'
                               + (' (stalled — holding something?)' if result.stalled else ''))
        return result

    def _on_gripper_command(self, msg):
        try:
            self._move_gripper(msg.data)
        except ARM_ERRORS as e:
            self.get_logger().error(f'Gripper failed: {e}')

    # ================================================================ services
    def _trigger(self, res, ok, msg):
        res.success, res.message = ok, msg
        return res

    def _srv_stop(self, req, res):
        self._stop.set()
        self._halt()
        return self._trigger(res, True, 'stopped')

    def _srv_home(self, req, res):
        ok, msg = self._run_unattended('home', lambda: self._move_to_deg(self.home_deg))
        return self._trigger(res, ok, msg)

    def _srv_power_on(self, req, res):
        try:
            self.arm.call('power_on')
            self.released = False
            return self._trigger(res, True, 'servos powered')
        except ARM_ERRORS as e:
            return self._trigger(res, False, str(e))

    def _srv_release(self, req, res):
        if self._motion.locked():
            return self._trigger(res, False, 'arm is moving; call /arm/stop first')
        try:
            self.arm.call('release_all_servos')
            self.released = True
            return self._trigger(res, True, 'servos released: the arm is limp')
        except ARM_ERRORS as e:
            return self._trigger(res, False, str(e))

    def _srv_open(self, req, res):
        try:
            got = self._move_gripper(100)
            return self._trigger(res, True, f'gripper open ({got})')
        except ARM_ERRORS as e:
            return self._trigger(res, False, str(e))

    def _srv_close(self, req, res):
        try:
            got = self._move_gripper(0)
            return self._trigger(res, True, f'gripper closed ({got})')
        except ARM_ERRORS as e:
            return self._trigger(res, False, str(e))

    def destroy_node(self):
        self._stop.set()
        try:
            self.arm.close()
        finally:
            super().destroy_node()


def main(args=None):
    rclpy.init(args=args)
    node = MyCobotDriver()
    executor = MultiThreadedExecutor(num_threads=6)
    executor.add_node(node)
    try:
        executor.spin()
    except (KeyboardInterrupt, ExternalShutdownException):
        pass
    finally:
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == '__main__':
    main()
