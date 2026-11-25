"""Start the arm driver ON THE ARM'S PI.

  ros2 launch mycobot_driver driver.launch.py                  # real arm on /dev/ttyAMA0
  ros2 launch mycobot_driver driver.launch.py backend:=fake    # simulated arm (any machine)
  ros2 launch mycobot_driver driver.launch.py publish_tf:=false

Starts mycobot_driver (serial port, /joint_states, trajectory + gripper actions) and
robot_state_publisher (/robot_description + TF from /joint_states).
"""
import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.conditions import IfCondition
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    cfg = os.path.join(get_package_share_directory('mycobot_driver'), 'config', 'driver.yaml')
    urdf_path = os.path.join(get_package_share_directory('mycobot_description'),
                             'urdf', 'mycobot_280_pi.urdf')
    with open(urdf_path) as f:
        urdf = f.read()
    return LaunchDescription([
        DeclareLaunchArgument('backend', default_value='serial',
                              description='serial = real arm, fake = simulated arm'),
        DeclareLaunchArgument('publish_tf', default_value='true',
                              description='also run robot_state_publisher (TF + /robot_description)'),
        Node(package='mycobot_driver', executable='driver_node', name='mycobot_driver',
             output='screen', emulate_tty=True,
             parameters=[cfg, {'backend': LaunchConfiguration('backend')}]),
        Node(package='robot_state_publisher', executable='robot_state_publisher',
             output='log', parameters=[{'robot_description': urdf}],
             condition=IfCondition(LaunchConfiguration('publish_tf'))),
    ])
