"""Fake vehicle: tests the arm flow when no vehicle program is available.

After receiving /arm/holding = "red", waits travel_time seconds and publishes /vehicle/arrived = "red".
"""
import rclpy
from rclpy.node import Node
from rclpy.qos import DurabilityPolicy, QoSProfile, ReliabilityPolicy
from std_msgs.msg import String

LATCHED_QOS = QoSProfile(depth=1, reliability=ReliabilityPolicy.RELIABLE,
                         durability=DurabilityPolicy.TRANSIENT_LOCAL)


class FakeVehicle(Node):

    def __init__(self):
        super().__init__('fake_vehicle')
        self.travel_time = self.declare_parameter('travel_time', 3.0).value
        self.pub = self.create_publisher(String, '/vehicle/arrived', 10)
        self.create_subscription(String, '/arm/holding', self._on_holding, LATCHED_QOS)
        self.create_subscription(String, '/arm/state', self._on_state, LATCHED_QOS)
        self.timer = None

    def _on_holding(self, msg):
        color = msg.data.strip()
        if not color:
            return
        self.get_logger().info(f'Arm is holding {color}; driving to the {color} basket '
                               f'({self.travel_time:.0f} s)')
        if self.timer:
            self.timer.cancel()

        def arrive():
            self.timer.cancel()
            self.get_logger().info(f'Arrived at the {color} basket')
            self.pub.publish(String(data=color))

        self.timer = self.create_timer(self.travel_time, arrive)

    def _on_state(self, msg):
        if msg.data == 'DONE':
            self.get_logger().info('Arm finished placing; vehicle leaving')


def main():
    rclpy.init()
    node = FakeVehicle()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.try_shutdown()


if __name__ == '__main__':
    main()
