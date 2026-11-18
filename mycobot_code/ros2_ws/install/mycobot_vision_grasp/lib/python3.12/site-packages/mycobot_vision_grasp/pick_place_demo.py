"""Example client for the arm command API: locate → pick → place.

  ros2 run mycobot_vision_grasp pick_place_demo                         # any colour, place pose
  ros2 run mycobot_vision_grasp pick_place_demo --color red
  ros2 run mycobot_vision_grasp pick_place_demo --color blue --drop 0.15 -0.15 0.05
  ros2 run mycobot_vision_grasp pick_place_demo --locate-only

Copy this into your own node to drive the arm from another program (vehicle, mission planner...).
"""
import argparse
import math

import rclpy
from cobot_interfaces.action import PickBlock, PlaceBlock
from cobot_interfaces.srv import LocateBlocks
from geometry_msgs.msg import Point
from rclpy.action import ActionClient
from rclpy.node import Node


class ArmCommander(Node):
    """Small blocking wrapper around /arm/locate_blocks, /arm/pick_block and /arm/place_block."""

    def __init__(self):
        super().__init__('arm_commander')
        self.locate_cli = self.create_client(LocateBlocks, '/arm/locate_blocks')
        self.pick_cli = ActionClient(self, PickBlock, '/arm/pick_block')
        self.place_cli = ActionClient(self, PlaceBlock, '/arm/place_block')

    def _wait_servers(self, timeout=10.0):
        ok = (self.locate_cli.wait_for_service(timeout_sec=timeout)
              and self.pick_cli.wait_for_server(timeout_sec=timeout)
              and self.place_cli.wait_for_server(timeout_sec=timeout))
        if not ok:
            raise RuntimeError('arm_task_node is not running (or a different ROS_DOMAIN_ID)')

    def locate(self, color='', go_home=True):
        self._wait_servers()
        fut = self.locate_cli.call_async(LocateBlocks.Request(color=color, go_home=go_home))
        rclpy.spin_until_future_complete(self, fut)
        return fut.result()

    def _run_action(self, client, goal):
        def on_feedback(fb):
            self.get_logger().info(f'  ... {fb.feedback.stage}')
        send = client.send_goal_async(goal, feedback_callback=on_feedback)
        rclpy.spin_until_future_complete(self, send)
        handle = send.result()
        if not handle.accepted:
            raise RuntimeError('goal rejected (arm busy, not ready, or in autorun mode)')
        res = handle.get_result_async()
        rclpy.spin_until_future_complete(self, res)
        return res.result().result

    def pick(self, color=''):
        self._wait_servers()
        return self._run_action(self.pick_cli, PickBlock.Goal(color=color))

    def place(self, location='place'):
        self._wait_servers()
        return self._run_action(self.place_cli, PlaceBlock.Goal(location=location))

    def drop_at(self, x, y, z):
        self._wait_servers()
        return self._run_action(self.place_cli, PlaceBlock.Goal(
            use_position=True, position=Point(x=float(x), y=float(y), z=float(z))))


def main():
    ap = argparse.ArgumentParser(description=__doc__.split('\n')[0])
    ap.add_argument('--color', default='', help='colour to pick (default: any)')
    ap.add_argument('--location', default='place', help='named place pose: place / carry / home')
    ap.add_argument('--drop', nargs=3, type=float, metavar=('X', 'Y', 'Z'),
                    help='drop the block with the gripper centre at this point (base_link, metres)')
    ap.add_argument('--locate-only', action='store_true')
    args, ros_args = ap.parse_known_args()

    rclpy.init(args=ros_args)
    arm = ArmCommander()
    log = arm.get_logger()
    try:
        res = arm.locate(args.color)
        log.info(f'locate: {res.message}')
        for b in res.blocks:
            p = b.position
            log.info(f'  {b.color:6s} at ({p.x:.3f}, {p.y:.3f}, {p.z:.3f}) m  '
                     f'yaw {math.degrees(b.grasp_yaw):4.0f}°  width {b.width * 100:.1f} cm  '
                     f'{"graspable" if b.graspable else "NOT graspable"}')
        if args.locate_only or not res.success:
            return

        r = arm.pick(args.color)
        log.info(f'pick: {"OK" if r.success else "FAILED"} - {r.message}')
        if not r.success:
            return

        r = arm.drop_at(*args.drop) if args.drop else arm.place(args.location)
        log.info(f'place: {"OK" if r.success else "FAILED"} - {r.message}')
    except RuntimeError as e:
        log.error(str(e))
    finally:
        arm.destroy_node()
        rclpy.try_shutdown()


if __name__ == '__main__':
    main()
