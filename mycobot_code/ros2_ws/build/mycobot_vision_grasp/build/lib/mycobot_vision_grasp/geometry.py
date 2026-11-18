"""Coordinate transforms and grasp pose computation (pure numpy, no ROS dependency)."""
import math

import numpy as np


def quat_to_matrix(q):
    """q = (x, y, z, w) → 3x3 rotation matrix"""
    x, y, z, w = q
    n = math.sqrt(x * x + y * y + z * z + w * w)
    x, y, z, w = x / n, y / n, z / n, w / n
    return np.array([
        [1 - 2 * (y * y + z * z), 2 * (x * y - z * w), 2 * (x * z + y * w)],
        [2 * (x * y + z * w), 1 - 2 * (x * x + z * z), 2 * (y * z - x * w)],
        [2 * (x * z - y * w), 2 * (y * z + x * w), 1 - 2 * (x * x + y * y)],
    ])


def matrix_to_quat(R):
    """3x3 rotation matrix → (x, y, z, w)"""
    R = np.asarray(R, np.float64)
    tr = R[0, 0] + R[1, 1] + R[2, 2]
    if tr > 0:
        s = math.sqrt(tr + 1.0) * 2
        w = 0.25 * s
        x = (R[2, 1] - R[1, 2]) / s
        y = (R[0, 2] - R[2, 0]) / s
        z = (R[1, 0] - R[0, 1]) / s
    elif R[0, 0] > R[1, 1] and R[0, 0] > R[2, 2]:
        s = math.sqrt(1.0 + R[0, 0] - R[1, 1] - R[2, 2]) * 2
        w = (R[2, 1] - R[1, 2]) / s
        x = 0.25 * s
        y = (R[0, 1] + R[1, 0]) / s
        z = (R[0, 2] + R[2, 0]) / s
    elif R[1, 1] > R[2, 2]:
        s = math.sqrt(1.0 + R[1, 1] - R[0, 0] - R[2, 2]) * 2
        w = (R[0, 2] - R[2, 0]) / s
        x = (R[0, 1] + R[1, 0]) / s
        y = 0.25 * s
        z = (R[1, 2] + R[2, 1]) / s
    else:
        s = math.sqrt(1.0 + R[2, 2] - R[0, 0] - R[1, 1]) * 2
        w = (R[1, 0] - R[0, 1]) / s
        x = (R[0, 2] + R[2, 0]) / s
        y = (R[1, 2] + R[2, 1]) / s
        z = 0.25 * s
    return (x, y, z, w)


def transform_points(points, translation, quat):
    """Transform Nx3 points from the source frame to the target frame
    (translation/quat come from TF lookup_transform(target, source))."""
    R = quat_to_matrix(quat)
    return np.asarray(points, np.float64) @ R.T + np.asarray(translation, np.float64)


def wrap_to_pi(a):
    return (a + math.pi) % (2 * math.pi) - math.pi


def parse_axis(s):
    """'+z' / '-y' / 'x' → (index, sign)"""
    s = s.strip().lower()
    sign = -1.0 if s.startswith('-') else 1.0
    idx = 'xyz'.index(s[-1])
    return idx, sign


def axis_vector(s):
    idx, sign = parse_axis(s)
    v = np.zeros(3)
    v[idx] = sign
    return v


def rotate_about(v, axis, angle):
    """Rotate vector v about the unit axis `axis` by `angle` (right-hand rule)."""
    v, k = np.asarray(v, np.float64), np.asarray(axis, np.float64)
    return (v * math.cos(angle) + np.cross(k, v) * math.sin(angle)
            + k * np.dot(k, v) * (1 - math.cos(angle)))


def effective_closing_vector(approach_axis, closing_axis, roll_offset=0.0):
    """Actual finger closing direction of the gripper (in the ik_link frame).

    roll_offset: mounting rotation of the gripper about the approach axis [rad].
      Example: if the gripper is tilted 45° (seen from the front) when joint 6 is at zero, use ±45°.
      Positive = counter-clockwise when looking at the gripper from the front.
    """
    return rotate_about(axis_vector(closing_axis), axis_vector(approach_axis), roll_offset)


def build_grasp_rotation(approach_axis, closing_axis, closing_yaw, roll_offset=0.0):
    """Orientation of ik_link (relative to base) for "gripper pointing straight down,
    finger closing direction at closing_yaw".

    approach_axis: axis of ik_link pointing out of the gripper, e.g. '+z'
    closing_axis:  axis of ik_link along the finger closing direction (before the offset), e.g. '+y'
    closing_yaw:   desired closing direction in the base XY plane [rad]
    roll_offset:   gripper mounting rotation about the approach axis [rad]
    """
    a = axis_vector(approach_axis)
    if abs(np.dot(a, axis_vector(closing_axis))) > 1e-9:
        raise ValueError('approach_axis and closing_axis must be different axes')
    c = effective_closing_vector(approach_axis, closing_axis, roll_offset)
    A = np.array([0.0, 0.0, -1.0])
    C = np.array([math.cos(closing_yaw), math.sin(closing_yaw), 0.0])
    src = np.column_stack([a, c, np.cross(a, c)])
    dst = np.column_stack([A, C, np.cross(A, C)])
    return dst @ src.T


def tcp_frame_rotation(approach_axis, closing_axis, roll_offset=0.0):
    """Rotation of the gripper_tcp frame relative to ik_link: x = closing direction,
    z = gripper forward, y = z × x."""
    a = axis_vector(approach_axis)
    c = effective_closing_vector(approach_axis, closing_axis, roll_offset)
    return np.column_stack([c, np.cross(a, c), a])


def fit_joint_limit(q, lo, hi):
    """Shift a revolute joint angle by ±2π into [lo, hi] (same pose). Returns None if impossible."""
    for k in (0, -1, 1, -2, 2):
        v = q + k * 2 * math.pi
        if lo - 1e-6 <= v <= hi + 1e-6:
            return min(max(v, lo), hi)
    return None


def select_grasp(corners_base, max_opening, margin=0.005):
    """Choose the grasp direction from the block's parallel edges.

    corners_base: (4, 2 or 3) corners of the block's top-face rectangle (base frame), in order
    The fingers press against one pair of parallel edges; the closing direction is perpendicular
    to them. The narrower side is preferred; returns None if even the narrow side is wider than
    the maximum gripper opening.

    Returns dict(yaw=closing direction, width=grasp width, length=other side length, side=0/1)
      side=0: closing direction along corners 0→1; side=1: along corners 1→2
    """
    c = np.asarray(corners_base, np.float64)[:, :2]
    e = [c[(i + 1) % 4] - c[i] for i in range(4)]        # the 4 edges
    L = [float(np.linalg.norm(v)) for v in e]
    lens = [(L[0] + L[2]) / 2, (L[1] + L[3]) / 2]         # pair 0 (edges 0, 2), pair 1 (edges 1, 3)
    # Estimate the orientation from all 4 edges (long edges weigh more; more stable than one short edge):
    # pair-1 edges rotated by 90° align with pair 0; length-weighted circular mean of the doubled
    # angle (edge direction is 180° symmetric)
    s2 = c2 = 0.0
    for i, v in enumerate(e):
        a = math.atan2(v[1], v[0]) - (math.pi / 2 if i % 2 else 0.0)
        s2 += L[i] * math.sin(2 * a)
        c2 += L[i] * math.cos(2 * a)
    theta0 = 0.5 * math.atan2(s2, c2)                     # direction of pair-0 edges
    order = sorted([0, 1], key=lambda i: lens[i])
    for side in order:
        if lens[side] + margin <= max_opening:
            yaw = theta0 + (math.pi / 2 if side == 1 else 0.0)
            return dict(yaw=wrap_to_pi(yaw), width=lens[side], length=lens[1 - side], side=side)
    return None


def yaw_candidates(yaw, reference_yaw):
    """A parallel gripper rotated by 180° is equivalent. Returns [the one closer to the current
    wrist angle, the other one] to avoid large wrist rotations."""
    a = wrap_to_pi(yaw)
    b = wrap_to_pi(yaw + math.pi)
    if abs(wrap_to_pi(a - reference_yaw)) <= abs(wrap_to_pi(b - reference_yaw)):
        return [a, b]
    return [b, a]


def make_transform(translation, quat):
    """(translation, quat) → 4x4 homogeneous transform."""
    T = np.eye(4)
    T[:3, :3] = quat_to_matrix(quat)
    T[:3, 3] = translation
    return T


def apply_transform(T, points):
    """Apply a 4x4 transform to Nx3 points."""
    p = np.asarray(points, np.float64)
    return p @ T[:3, :3].T + T[:3, 3]


def tcp_relative(point_in_link, approach_axis, tcp_offset):
    """Convert a point in the gripper link frame to coordinates relative to the gripper centre (TCP).
    The TCP is tcp_offset along the approach axis from the link origin."""
    return np.asarray(point_in_link, np.float64) - axis_vector(approach_axis) * tcp_offset


def matrix_from_rpy(roll, pitch, yaw):
    """URDF / static_transform_publisher rpy (fixed axes X→Y→Z, radians) → rotation matrix."""
    cr, sr = math.cos(roll), math.sin(roll)
    cp, sp = math.cos(pitch), math.sin(pitch)
    cy, sy = math.cos(yaw), math.sin(yaw)
    Rx = np.array([[1, 0, 0], [0, cr, -sr], [0, sr, cr]])
    Ry = np.array([[cp, 0, sp], [0, 1, 0], [-sp, 0, cp]])
    Rz = np.array([[cy, -sy, 0], [sy, cy, 0], [0, 0, 1]])
    return Rz @ Ry @ Rx


def rpy_from_matrix(R):
    """Rotation matrix → (roll, pitch, yaw). At pitch = ±90° the roll is merged into yaw."""
    R = np.asarray(R, np.float64)
    pitch = math.atan2(-R[2, 0], math.hypot(R[2, 1], R[2, 2]))
    if math.hypot(R[2, 1], R[2, 2]) < 1e-9:
        return 0.0, pitch, math.atan2(-R[0, 1], R[1, 1])
    return math.atan2(R[2, 1], R[2, 2]), pitch, math.atan2(R[1, 0], R[0, 0])
