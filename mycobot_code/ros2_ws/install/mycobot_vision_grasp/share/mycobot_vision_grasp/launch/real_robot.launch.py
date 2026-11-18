"""Real robot, LAPTOP / NUC side: D435 camera + block vision + arm task node (command API).

The arm driver is NOT started here; it runs on the arm's Pi:
  (on the Pi)      ros2 launch mycobot_driver driver.launch.py
  (laptop / NUC)   ros2 launch mycobot_vision_grasp real_robot.launch.py

Both machines need the same ROS_DOMAIN_ID. Options:
  camera:=false          the RealSense driver is started separately
  autorun:=true          run the autonomous pick → vehicle → place loop instead of waiting for commands
  camera_pose_file:=...  another camera pose file (default config/camera_pose.yaml)
"""
import os

from ament_index_python.packages import PackageNotFoundError, get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription, LogInfo, OpaqueFunction
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.actions import Node

from mycobot_vision_grasp.launch_utils import camera_pose_tf_node, load_camera_pose

PKG = 'mycobot_vision_grasp'

# realsense2_camera settings: aligned depth is required; IR / IMU / point cloud are not used
REALSENSE_ARGS = {
    'align_depth.enable': 'true',
    'rgb_camera.color_profile': '640,480,15',
    'depth_module.depth_profile': '640,480,15',
    'enable_infra1': 'false',
    'enable_infra2': 'false',
    'enable_gyro': 'false',
    'enable_accel': 'false',
    'pointcloud.enable': 'false',
    'publish_tf': 'true',          # camera_link → camera_color_optical_frame
}


def _setup(context):
    arg = lambda n: context.launch_configurations[n]
    is_true = lambda n: arg(n).strip().lower() == 'true'
    params = arg('params_file')
    cfg, pose = load_camera_pose(arg('camera_pose_file'))

    actions = [
        camera_pose_tf_node(cfg, pose),
        Node(package=PKG, executable='block_vision_node', name='block_vision',
             parameters=[params], output='screen', emulate_tty=True),
        Node(package=PKG, executable='arm_task_node', name='arm_task',
             parameters=[params, {'ik_solver': 'internal', 'autorun': is_true('autorun')}],
             output='screen', emulate_tty=True),
    ]
    if is_true('camera'):
        try:
            rs = get_package_share_directory('realsense2_camera')
        except PackageNotFoundError:
            return [LogInfo(msg='ERROR: realsense2_camera is not installed '
                                '(sudo apt install ros-jazzy-realsense2-camera), '
                                'or start the camera yourself and use camera:=false')] + actions
        actions.insert(0, IncludeLaunchDescription(
            PythonLaunchDescriptionSource(os.path.join(rs, 'launch', 'rs_launch.py')),
            launch_arguments=REALSENSE_ARGS.items()))
    return actions


def generate_launch_description():
    share = get_package_share_directory(PKG)
    return LaunchDescription([
        DeclareLaunchArgument('params_file',
                              default_value=os.path.join(share, 'config', 'arm_task.yaml')),
        DeclareLaunchArgument('camera_pose_file',
                              default_value=os.path.join(share, 'config', 'camera_pose.yaml'),
                              description='Pose of the fixed camera relative to the arm base'),
        DeclareLaunchArgument('camera', default_value='true',
                              description='Start the RealSense driver (realsense2_camera)'),
        DeclareLaunchArgument('autorun', default_value='false',
                              description='Autonomous pick → vehicle → place loop instead of commands'),
        OpaqueFunction(function=_setup),
    ])
