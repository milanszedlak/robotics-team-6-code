"""Kinematics tests (no ROS, no arm needed).

FIRMWARE_SAMPLES were read from the real arm on 2026-11-18 with pymycobot
`MyCobot280.angles_to_coords(angles)`: the firmware's own forward kinematics, computed
without moving the arm. coords = [x, y, z (mm), rx, ry, rz (deg, R = Rz·Ry·Rx)].
"""
import math
import os
import sys

import numpy as np
import pytest

sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..'))

from mycobot_driver.kinematics import LIMITS, fk, ik, matrix_to_quat, within_limits  # noqa: E402

FIRMWARE_SAMPLES = [
    ([0, 0, 0, 0, 0, 0], [45.6, -63.4, 420.8, -90.0, 0.0, -90.0]),
    ([90, 0, 0, 0, 0, 0], [63.4, 45.5, 420.8, -90.0, 0.0, 0.0]),
    ([0, 45, 0, 0, 0, 0], [-166.7, -63.4, 370.6, -45.0, 0.0, -90.0]),
    ([0, 0, 45, 0, 0, 0], [-88.7, -63.4, 403.0, -45.0, 0.0, -90.0]),
    ([0, 0, 0, 45, 0, 0], [-20.8, -63.4, 431.1, -45.0, 0.0, -90.0]),
    ([0, 0, 0, 0, 45, 0], [32.2, -31.1, 420.8, -90.0, 0.0, -45.0]),
    ([0, 0, 0, 0, 0, 45], [45.6, -63.4, 420.8, -90.0, 45.0, -90.0]),
    ([0, 30, -100, -20, 0, 0], [110.0, -63.4, 222.2, 180.0, 0.0, -90.0]),
    ([-87.8, 69.5, 63.3, -58.8, -1.1, -15.2], [-73.1, 230.7, 177.3, -15.73, -3.12, 167.27]),
    ([36.4, 57.7, -97.5, -113.2, 80.6, -20.2], [7.3, -17.4, 201.9, 96.21, 46.71, -130.66]),
    ([62.9, -99.6, -13.1, 53.2, -65.1, 133.6], [217.0, 194.2, 105.5, -149.24, 65.02, -160.55]),
    ([96.3, -93.9, -113.9, 9.9, 105.4, -35.6], [13.4, 55.6, -28.1, 94.93, 18.24, -96.84]),
    ([-68.0, -15.6, -113.0, -66.8, -14.9, -1.3], [-53.8, -67.3, 125.2, 75.06, 5.17, -143.94]),
    ([-64.1, -53.8, -67.5, -9.7, -50.5, -143.6], [2.5, -230.8, 83.6, -159.2, 59.09, 21.38]),
    ([81.0, 11.3, 34.2, -75.4, 118.2, 108.0], [11.7, -74.1, 390.7, 71.04, 43.52, -87.38]),
    ([-91.0, -33.5, 53.2, 50.7, 104.7, -23.4], [-18.4, 46.3, 336.1, 167.26, -75.81, 17.15]),
    ([79.2, 34.1, -47.2, 21.0, 91.8, 103.9], [7.7, -54.2, 398.4, 92.36, 83.99, -96.66]),
    ([1.3, 17.8, -111.7, -61.7, 71.4, -25.7], [80.2, -18.3, 163.6, 101.44, 48.39, -153.05]),
    ([-78.5, 9.8, 48.7, 41.9, -30.1, -18.3], [-120.7, 160.7, 323.6, 1.11, 31.66, 176.31]),
    ([2.0, 55.7, 5.0, -25.6, -2.5, -141.1], [-178.4, -71.6, 336.2, 47.22, -32.22, 115.2]),
]


def rot_xyz(rx, ry, rz):
    """Firmware angle convention: R = Rz(rz) · Ry(ry) · Rx(rx), degrees."""
    rx, ry, rz = map(math.radians, (rx, ry, rz))
    cx, sx, cy, sy, cz, sz = (math.cos(rx), math.sin(rx), math.cos(ry), math.sin(ry),
                              math.cos(rz), math.sin(rz))
    Rx = np.array([[1, 0, 0], [0, cx, -sx], [0, sx, cx]])
    Ry = np.array([[cy, 0, sy], [0, 1, 0], [-sy, 0, cy]])
    Rz = np.array([[cz, -sz, 0], [sz, cz, 0], [0, 0, 1]])
    return Rz @ Ry @ Rx


@pytest.mark.parametrize('angles,coords', FIRMWARE_SAMPLES)
def test_fk_matches_firmware(angles, coords):
    T = fk([math.radians(a) for a in angles])
    assert np.linalg.norm(T[:3, 3] * 1000.0 - np.array(coords[:3])) < 0.5      # mm
    R_err = T[:3, :3].T @ rot_xyz(*coords[3:])
    angle = math.degrees(math.acos(max(-1.0, min(1.0, (np.trace(R_err) - 1) / 2))))
    assert angle < 0.5                                                          # deg


@pytest.mark.parametrize('angles,_', FIRMWARE_SAMPLES)
def test_ik_recovers_reachable_pose(angles, _):
    q_true = [math.radians(a) for a in angles]
    if not within_limits(q_true):
        pytest.skip('sample outside driver limits')
    T = fk(q_true)
    seed = [v + 0.15 for v in q_true]           # nearby seed, like consecutive motion steps
    q = ik(T, seed)
    assert q is not None
    assert within_limits(q)
    T2 = fk(q)
    assert np.linalg.norm(T2[:3, 3] - T[:3, 3]) < 1e-3
    assert np.allclose(T2[:3, :3], T[:3, :3], atol=1e-2)


def gripper_down(x, y, z, yaw=0.0):
    """Flange pose with +z (gripper forward) pointing straight down."""
    c, s = math.cos(yaw), math.sin(yaw)
    R = np.array([[c, s, 0.0], [s, -c, 0.0], [0.0, 0.0, -1.0]])     # columns: x, y, z=(0,0,-1)
    T = np.eye(4)
    T[:3, :3] = R
    T[:3, 3] = (x, y, z)
    return T


HOME = [0.0, 0.5, -1.8, 0.0, 0.0, 0.0]       # arm_task.yaml home_joints


@pytest.mark.parametrize('x,y', [(0.15, 0.0), (0.20, 0.0), (0.18, 0.08), (0.18, -0.08),
                                 (0.12, 0.12), (0.0, 0.18), (0.0, -0.18), (-0.12, 0.12)])
def test_ik_gripper_down_over_table(x, y):
    """Flange 0.11 m above the base plane, gripper pointing down (≈ grasping a 2.5 cm block
    with a 10 cm gripper), from the home pose as seed."""
    T = gripper_down(x, y, 0.11, yaw=math.atan2(y, x))
    q = ik(T, HOME)
    assert q is not None, f'unreachable: ({x}, {y})'
    assert within_limits(q)
    assert np.linalg.norm(fk(q)[:3, 3] - T[:3, 3]) < 1e-3


def test_unreachable_returns_none():
    assert ik(gripper_down(0.6, 0.0, 0.1), HOME, restarts=3) is None


def test_limits_match_driver_clamp():
    assert math.degrees(LIMITS[5][1]) == pytest.approx(175.0)


def test_matrix_to_quat_identity():
    assert np.allclose(matrix_to_quat(np.eye(3)), (0, 0, 0, 1))
