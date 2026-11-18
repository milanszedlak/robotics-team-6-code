"""Helpers shared by the launch files (camera pose from config/camera_pose.yaml)."""
import math

import yaml
from launch_ros.actions import Node


def load_camera_pose(path):
    """Returns (cfg dict, (x, y, z, roll, pitch, yaw) with angles in radians)."""
    with open(path) as f:
        cfg = yaml.safe_load(f)
    cp = cfg['camera_pose']
    rad = math.radians
    return cfg, (float(cp['x']), float(cp['y']), float(cp['z']),
                 rad(float(cp['roll'])), rad(float(cp['pitch'])), rad(float(cp['yaw'])))


def camera_pose_tf_node(cfg, pose, use_sim_time=False):
    """Static TF base_link → camera_link (the fixed camera's measured pose)."""
    cp = cfg['camera_pose']
    x, y, z, r, p, yw = pose
    return Node(package='tf2_ros', executable='static_transform_publisher', name='camera_pose_tf',
                arguments=['--x', str(x), '--y', str(y), '--z', str(z),
                           '--roll', str(r), '--pitch', str(p), '--yaw', str(yw),
                           '--frame-id', cp.get('parent_frame', 'base_link'),
                           '--child-frame-id', cp.get('child_frame', 'camera_link')],
                parameters=[{'use_sim_time': use_sim_time}])
