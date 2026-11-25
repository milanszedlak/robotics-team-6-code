"""ROS-free test: render a synthetic depth-camera image and check detection → 3D → base frame → grasp direction.

Run:  cd ~/ros2_ws/src/mycobot_vision_grasp && python3 -m pytest test -v
"""
import math
import os
import sys

import cv2
import numpy as np
import pytest

sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..'))
from mycobot_vision_grasp.block_detector import detect_blocks, detection_points_3d  # noqa: E402
from mycobot_vision_grasp.geometry import (  # noqa: E402
    build_grasp_rotation, matrix_to_quat, quat_to_matrix, select_grasp,
    transform_points, wrap_to_pi, yaw_candidates)

W, H = 640, 480
K = np.array([[554.0, 0, 320.0], [0, 554.0, 240.0], [0, 0, 1]])
RED = [((0, 120, 70), (10, 255, 255)), ((170, 120, 70), (180, 255, 255))]


def rot_x(a):
    c, s = math.cos(a), math.sin(a)
    return np.array([[1, 0, 0], [0, c, -s], [0, s, c]])


def camera_pose(pos, tilt_deg):
    # optical frame looking straight down: z_cam=(0,0,-1), x_cam=(0,-1,0), y_cam=(-1,0,0)
    R = np.column_stack([[0, -1, 0], [-1, 0, 0], [0, 0, -1]]).astype(float)
    return rot_x(math.radians(tilt_deg)) @ R, np.asarray(pos, float)


def render(R_bc, t_bc, center, size, yaw, height):
    """Render colour and depth images of the table (z=0) and the block top face (z=height)."""
    u, v = np.meshgrid(np.arange(W), np.arange(H))
    rays_c = np.stack([(u - K[0, 2]) / K[0, 0], (v - K[1, 2]) / K[1, 1], np.ones_like(u, float)], -1)
    rays_b = rays_c @ R_bc.T

    def plane_depth(z):
        # camera origin + s*ray_b intersects plane z; optical depth = s (because ray_c has z=1)
        return (z - t_bc[2]) / rays_b[..., 2]

    depth = plane_depth(0.0).astype(np.float32)
    color = np.full((H, W, 3), 160, np.uint8)

    l, w = size
    c, s = math.cos(yaw), math.sin(yaw)
    local = np.array([[l / 2, w / 2], [-l / 2, w / 2], [-l / 2, -w / 2], [l / 2, -w / 2]])
    top = np.array([[center[0] + c * x - s * y, center[1] + s * x + c * y, height] for x, y in local])
    pc = (top - t_bc) @ R_bc  # base → camera
    px = (pc[:, :2] / pc[:, 2:3]) * [K[0, 0], K[1, 1]] + [K[0, 2], K[1, 2]]
    mask = np.zeros((H, W), np.uint8)
    cv2.fillPoly(mask, [np.round(px).astype(np.int32)], 255)
    color[mask > 0] = (0, 0, 220)
    depth[mask > 0] = plane_depth(height)[mask > 0]
    return color, depth


@pytest.mark.parametrize('tilt,yaw_deg,center', [
    (0, 30, (0.20, 0.03)),
    (12, -55, (0.18, -0.04)),
    (20, 80, (0.24, 0.02)),
])
def test_full_pipeline(tilt, yaw_deg, center):
    size = (0.06, 0.025)     # 6 cm long, 2.5 cm wide
    height = 0.025
    R_bc, t_bc = camera_pose((0.20, 0.0, 0.30), tilt)
    color, depth = render(R_bc, t_bc, center, size, math.radians(yaw_deg), height)

    dets, _ = detect_blocks(color, depth, RED)
    assert len(dets) == 1
    c_cam, corners_cam = detection_points_3d(dets[0], K)
    q = matrix_to_quat(R_bc)
    c_b = transform_points(c_cam[None], t_bc, q)[0]
    corners_b = transform_points(corners_cam, t_bc, q)

    assert np.allclose(c_b[:2], center, atol=0.004), c_b
    assert abs(c_b[2] - height) < 0.003

    g = select_grasp(corners_b, max_opening=0.045)
    assert g is not None
    assert abs(g['width'] - size[1]) < 0.004
    assert abs(g['length'] - size[0]) < 0.006
    # closing direction must be perpendicular to the long edge (= long-edge angle + 90°); 180° counts as equal
    expected = math.radians(yaw_deg) + math.pi / 2
    err = abs(wrap_to_pi(2 * (g['yaw'] - expected))) / 2
    assert math.degrees(err) < 3.0


def test_too_wide_block_rejected():
    corners = np.array([[0, 0], [0.06, 0], [0.06, 0.05], [0, 0.05]])
    assert select_grasp(corners, max_opening=0.045) is None


def test_long_side_used_when_short_side_not_fit():
    corners = np.array([[0, 0], [0.04, 0], [0.04, 0.03], [0, 0.03]])
    g = select_grasp(corners, max_opening=0.045)
    assert abs(g['width'] - 0.03) < 1e-9


@pytest.mark.parametrize('approach,closing', [('+z', '+y'), ('+z', '+x'), ('-x', '+y'), ('+x', '-z')])
@pytest.mark.parametrize('yaw', [0.0, 0.7, -2.5])
def test_grasp_rotation(approach, closing, yaw):
    from mycobot_vision_grasp.geometry import axis_vector
    R = build_grasp_rotation(approach, closing, yaw)
    assert np.allclose(R.T @ R, np.eye(3), atol=1e-9)
    assert abs(np.linalg.det(R) - 1) < 1e-9
    assert np.allclose(R @ axis_vector(approach), [0, 0, -1])
    assert np.allclose(R @ axis_vector(closing), [math.cos(yaw), math.sin(yaw), 0])
    assert np.allclose(quat_to_matrix(matrix_to_quat(R)), R, atol=1e-9)


def test_yaw_candidates_prefers_small_wrist_rotation():
    a, b = yaw_candidates(math.radians(170), math.radians(-10))
    assert abs(wrap_to_pi(a - math.radians(-10))) < math.radians(1)
    assert abs(wrap_to_pi(b - math.radians(170))) < math.radians(1)
