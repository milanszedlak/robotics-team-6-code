"""View the arm in RViz — run on the LAPTOP / NUC.

  ros2 launch mycobot_description view.launch.py                 # live: TF comes from the Pi
  ros2 launch mycobot_description view.launch.py gui:=true       # offline: sliders, no arm needed

Live mode only starts RViz: the Pi's robot_state_publisher already publishes /robot_description
and TF. Offline mode also starts robot_state_publisher + joint_state_publisher_gui locally.
Do NOT use gui:=true while the Pi driver is running (two sources of /joint_states).
"""
import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.conditions import IfCondition
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    share = get_package_share_directory('mycobot_description')
    with open(os.path.join(share, 'urdf', 'mycobot_280_pi.urdf')) as f:
        urdf = f.read()
    gui = LaunchConfiguration('gui')
    return LaunchDescription([
        DeclareLaunchArgument('gui', default_value='false',
                              description='true = offline, move the joints with sliders'),
        Node(package='robot_state_publisher', executable='robot_state_publisher',
             parameters=[{'robot_description': urdf}], condition=IfCondition(gui)),
        Node(package='joint_state_publisher_gui', executable='joint_state_publisher_gui',
             condition=IfCondition(gui)),
        Node(package='rviz2', executable='rviz2', output='log',
             arguments=['-d', os.path.join(share, 'rviz', 'view.rviz')]),
    ])
