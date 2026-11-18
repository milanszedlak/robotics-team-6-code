"""Tests for arm-side transforms, gripper offset, joint-6 limit and target selection (no ROS needed)."""
import math
import os
import sys

import numpy as np
import pytest

sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..'))
from mycobot_vision_grasp.geometry import (  # noqa: E402
    apply_transform, axis_vector, build_grasp_rotation, effective_closing_vector,
    fit_joint_limit, matrix_from_rpy, rpy_from_matrix, tcp_frame_rotation)
from mycobot_vision_grasp.targeting import Candidate, choose_block, corners_valid  # noqa: E402

OPTICAL = matrix_from_rpy(-math.pi / 2, 0, -math.pi / 2)   # camera_link → optical frame


def T(xyz, R):
    M = np.eye(4)
    M[:3, :3] = R
    M[:3, 3] = xyz
    return M


# ---------------------------------------------------------------- fixed camera
def camera_T(x, y, z, roll, pitch, yaw):
    """Same as the launch file: camera_pose.yaml (degrees) → T(base ← optical frame)"""
    r = math.radians
    return T([x, y, z], matrix_from_rpy(r(roll), r(pitch), r(yaw))) @ T([0, 0, 0], OPTICAL)


def test_camera_looking_down_pitch_90():
    T_bc = camera_T(0.25, 0.0, 0.60, 0, 90, 0)
    # optical z (lens forward) points down
    assert np.allclose(T_bc[:3, 2], [0, 0, -1], atol=1e-9)
    # the point 0.6 m straight below the camera (depth 0.6) = base (0.25, 0, 0)
    p = apply_transform(T_bc, [[0, 0, 0.60]])[0]
    assert np.allclose(p, [0.25, 0.0, 0.0], atol=1e-9)


def test_camera_tilted_45_facing_arm():
    # camera 0.5 m in front of the arm, 0.4 m high, looking back at the arm 45° down
    T_bc = camera_T(0.5, 0.0, 0.4, 0, 45, 180)
    fwd = T_bc[:3, 2]
    assert np.allclose(fwd, [-math.sqrt(0.5), 0, -math.sqrt(0.5)], atol=1e-9)
    # 0.4*√2 m along the line of sight = base (0.1, 0, 0)
    p = apply_transform(T_bc, [[0, 0, 0.4 * math.sqrt(2)]])[0]
    assert np.allclose(p, [0.1, 0.0, 0.0], atol=1e-9)


@pytest.mark.parametrize('rpy', [(0, 90, 0), (10, 45, 180), (0, -90, 30), (5, 20, -60), (0, 0, 0)])
def test_rpy_roundtrip(rpy):
    R = matrix_from_rpy(*map(math.radians, rpy))
    assert np.allclose(matrix_from_rpy(*rpy_from_matrix(R)), R, atol=1e-9)


# ---------------------------------------------------------------- 45° gripper offset
def test_roll_offset_rotates_closing_axis():
    c = effective_closing_vector('+z', '+y', math.radians(45))
    # +y rotated 45° counter-clockwise about +z → (-sin45, cos45, 0)
    assert np.allclose(c, [-math.sqrt(0.5), math.sqrt(0.5), 0], atol=1e-9)


@pytest.mark.parametrize('offset_deg', [0, 45, -45])
@pytest.mark.parametrize('yaw_deg', [0, 30, 120, -75])
def test_grasp_rotation_with_offset_aligns_real_jaws(offset_deg, yaw_deg):
    off, yaw = math.radians(offset_deg), math.radians(yaw_deg)
    R = build_grasp_rotation('+z', '+y', yaw, off)
    assert np.allclose(R.T @ R, np.eye(3), atol=1e-9) and abs(np.linalg.det(R) - 1) < 1e-9
    assert np.allclose(R @ axis_vector('+z'), [0, 0, -1], atol=1e-9)           # gripper points down
    jaw = R @ effective_closing_vector('+z', '+y', off)                       # actual finger direction
    assert np.allclose(jaw, [math.cos(yaw), math.sin(yaw), 0], atol=1e-9)


def test_offset_changes_flange_angle_by_offset():
    # same grasp direction: with a 45° offset the flange must turn an extra 45° (compensating the other way)
    R0 = build_grasp_rotation('+z', '+y', 0.3, 0.0)
    R45 = build_grasp_rotation('+z', '+y', 0.3, math.radians(45))
    rel = R0.T @ R45                       # relative rotation in the flange frame should be -45° about z
    assert np.allclose(rel, matrix_from_rpy(0, 0, math.radians(-45)), atol=1e-9)


def test_tcp_frame_axes():
    R = tcp_frame_rotation('+z', '+y', math.radians(45))
    assert np.allclose(R[:, 2], [0, 0, 1])                                     # z = gripper forward
    assert np.allclose(R[:, 0], effective_closing_vector('+z', '+y', math.radians(45)))
    assert abs(np.linalg.det(R) - 1) < 1e-9


# ---------------------------------------------------------------- joint 6 ±180°
def test_fit_joint_limit():
    lo, hi = -math.pi, math.pi
    assert fit_joint_limit(0.5, lo, hi) == 0.5
    assert math.isclose(fit_joint_limit(math.radians(200), lo, hi), math.radians(-160))
    assert math.isclose(fit_joint_limit(math.radians(-270), lo, hi), math.radians(90))
    # with a narrower range (e.g. ±90°), returns None when it cannot fit
    assert fit_joint_limit(math.radians(150), -math.pi / 2, math.pi / 2) is None


def test_any_jaw_direction_reachable_within_180():
    """Parallel gripper 180° symmetry + joint 6 ±180° → every grasp direction has at least one solution."""
    for yaw_deg in range(-180, 180, 5):
        for k in (0, 1):
            j6 = math.radians(yaw_deg + 180 * k - 45)        # joint-6 angle needed after removing the 45° offset
            if fit_joint_limit(j6, -math.pi, math.pi) is not None:
                break
        else:
            pytest.fail(f'{yaw_deg}° has no solution')


# ---------------------------------------------------------------- target selection
def cand(color, conf, grasp, xy, tcp_dist=0.2):
    return Candidate(color, conf, grasp, np.array([xy[0], xy[1], 0.02]), None,
                     np.array([0, 0, tcp_dist]))


def test_choose_skips_not_graspable_and_low_confidence():
    cs = [cand('red', 0.9, False, (0.2, 0)), cand('blue', 0.3, True, (0.2, 0.05)),
          cand('green', 0.8, True, (0.25, 0))]
    assert choose_block(cs, 0.5).color == 'green'


def test_choose_prefers_confidence_then_nearest():
    cs = [cand('red', 0.9, True, (0.2, 0), 0.30), cand('blue', 0.9, True, (0.2, 0.1), 0.20),
          cand('green', 0.7, True, (0.2, 0.2), 0.10)]
    assert choose_block(cs).color == 'blue'


def test_choose_tracks_same_block():
    cs = [cand('red', 0.9, True, (0.20, 0.00)), cand('red', 0.9, True, (0.20, 0.10))]
    assert np.allclose(choose_block(cs, color='red', ref_point=(0.21, 0.095)).center_base[:2],
                       (0.20, 0.10))
    assert choose_block(cs, color='red', ref_point=(0.40, 0.40)) is None
    assert choose_block(cs, color='blue') is None


def test_corners_valid():
    assert not corners_valid(np.zeros((4, 3)))
    sq = np.array([[0, 0, .3], [.02, 0, .3], [.02, .03, .3], [0, .03, .3]])
    assert corners_valid(sq)
