"""Launch the arm task in its AUTONOMOUS mode (pick → vehicle → place loop, autorun:=true).
For the real robot with the command API (locate / pick / place), use real_robot.launch.py.

Simulation (default): camera pose TF + fixed Gazebo camera + bridge + simulated vision + fake vehicle + arm
  ros2 launch mycobot_vision_grasp arm_task.launch.py

Simulation, but with the real vision program:
  ros2 launch mycobot_vision_grasp arm_task.launch.py sim_vision:=false

Real robot, autonomous loop (driver on the Pi, camera + vision already running on this machine):
  ros2 launch mycobot_vision_grasp arm_task.launch.py sim:=false

The camera pose is in config/camera_pose.yaml; another file can be given with:
  ros2 launch mycobot_vision_grasp arm_task.launch.py camera_pose_file:=/path/to/my_camera_pose.yaml
"""
import math
import os

import numpy as np
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, OpaqueFunction
from launch_ros.actions import Node

from mycobot_vision_grasp.geometry import matrix_from_rpy, rpy_from_matrix
from mycobot_vision_grasp.launch_utils import camera_pose_tf_node, load_camera_pose

PKG = 'mycobot_vision_grasp'


def _T(x, y, z, roll, pitch, yaw):
    T = np.eye(4)
    T[:3, :3] = matrix_from_rpy(roll, pitch, yaw)
    T[:3, 3] = (x, y, z)
    return T


def _setup(context):
    arg = lambda n: context.launch_configurations[n]
    is_true = lambda n: arg(n).strip().lower() == 'true'
    sim = is_true('sim')
    share = get_package_share_directory(PKG)
    params = arg('params_file')
    common = {'use_sim_time': sim}

    cfg, pose = load_camera_pose(arg('camera_pose_file'))
    cp = cfg['camera_pose']
    rad = math.radians
    x, y, z, r, p, yw = pose

    # Simulation: MoveIt IK (the Gazebo robot model differs from the real arm's kinematics)
    task_overrides = {'autorun': True, 'ik_solver': 'moveit' if sim else 'internal'}
    nodes = [
        camera_pose_tf_node(cfg, pose, sim),          # base_link → camera_link (fixed camera pose)
        Node(package=PKG, executable='arm_task_node', name='arm_task',
             parameters=[params, common, task_overrides], output='screen', emulate_tty=True),
    ]

    if sim:
        # On the real robot camera_link → camera_color_optical_frame is published by realsense2_camera;
        # in simulation it is published here
        nodes.append(Node(
            package='tf2_ros', executable='static_transform_publisher', name='camera_optical_tf',
            arguments=['--roll', str(-math.pi / 2), '--yaw', str(-math.pi / 2),
                       '--frame-id', cp.get('child_frame', 'camera_link'),
                       '--child-frame-id', 'camera_color_optical_frame'],
            parameters=[common]))

        # Place the Gazebo camera at world ← base ← camera
        rw = cfg.get('robot_in_world', {}) or {}
        T_world_base = _T(float(rw.get('x', 0)), float(rw.get('y', 0)), float(rw.get('z', 0)),
                          0.0, 0.0, rad(float(rw.get('yaw', 0))))
        T_wc = T_world_base @ _T(x, y, z, r, p, yw)
        R_, P_, Y_ = rpy_from_matrix(T_wc[:3, :3])
        nodes.append(Node(
            package='ros_gz_sim', executable='create', name='spawn_fixed_camera',
            arguments=['-file', os.path.join(share, 'models', 'd435i_fixed.sdf'),
                       '-name', 'd435i_fixed',
                       '-x', str(T_wc[0, 3]), '-y', str(T_wc[1, 3]), '-z', str(T_wc[2, 3]),
                       '-R', str(R_), '-P', str(P_), '-Y', str(Y_)],
            output='screen'))

        nodes.append(Node(
            package='ros_gz_bridge', executable='parameter_bridge', name='d435i_bridge',
            parameters=[{'config_file': os.path.join(share, 'config', 'camera_bridge.yaml'),
                         'use_sim_time': True}],
            output='screen'))
        if is_true('sim_vision'):
            nodes.append(Node(package=PKG, executable='sim_vision_node', name='sim_vision',
                              parameters=[params, common], output='screen'))
        if is_true('fake_vehicle'):
            nodes.append(Node(package=PKG, executable='fake_vehicle_node', name='fake_vehicle',
                              parameters=[params, common], output='screen'))
    return nodes


def generate_launch_description():
    share = get_package_share_directory(PKG)
    return LaunchDescription([
        DeclareLaunchArgument('params_file',
                              default_value=os.path.join(share, 'config', 'arm_task.yaml')),
        DeclareLaunchArgument('camera_pose_file',
                              default_value=os.path.join(share, 'config', 'camera_pose.yaml'),
                              description='Pose of the fixed camera relative to the arm base'),
        DeclareLaunchArgument('sim', default_value='true', description='Gazebo simulation'),
        DeclareLaunchArgument('sim_vision', default_value='true',
                              description='In simulation, use the built-in vision node instead of the real vision program'),
        DeclareLaunchArgument('fake_vehicle', default_value='true', description='In simulation, use the fake vehicle'),
        OpaqueFunction(function=_setup),
    ])
