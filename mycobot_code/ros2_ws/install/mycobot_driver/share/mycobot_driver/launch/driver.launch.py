"""Start the myCobot driver ON THE ARM'S PI.

  ros2 launch mycobot_driver driver.launch.py                  # real arm on /dev/ttyAMA0
  ros2 launch mycobot_driver driver.launch.py backend:=fake    # simulated arm (any machine, no hardware)
"""
import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    cfg = os.path.join(get_package_share_directory('mycobot_driver'), 'config', 'driver.yaml')
    return LaunchDescription([
        DeclareLaunchArgument('backend', default_value='serial',
                              description='serial = real arm, fake = simulated arm'),
        DeclareLaunchArgument('serial_port', default_value='/dev/ttyAMA0'),
        Node(package='mycobot_driver', executable='mycobot_driver_node', name='mycobot_driver',
             output='screen', emulate_tty=True,
             parameters=[cfg, {'backend': LaunchConfiguration('backend'),
                               'serial_port': LaunchConfiguration('serial_port')}]),
    ])
