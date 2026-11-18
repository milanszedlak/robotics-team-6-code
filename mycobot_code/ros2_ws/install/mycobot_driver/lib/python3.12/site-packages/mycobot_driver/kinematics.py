"""Forward / inverse kinematics of the myCobot 280 Pi (pure numpy, no ROS).

Frames
  base_link    = the arm firmware's base frame (the frame of pymycobot get_coords()):
                 origin on the joint-1 axis at the bottom of the base, z up.
  link6_flange = the joint-6 flange face; +z points OUT of the flange (towards the gripper).

The DH table below reproduces the firmware's own forward kinematics (pymycobot
angles_to_coords) to 0.1 mm / 0.1 deg over 20 test poses (see test/test_kinematics.py).
Joint angles are the servo angles exactly as get_angles()/send_angles() use them (converted
to radians); no sign flips or offsets are needed outside this file.
"""
import math

import numpy as np

from .conversions import DEFAULT_LIMITS_DEG

# Standard DH: (d [m], a [m], alpha [rad], theta offset [rad]) per joint
DH = [
    (0.13935, 0.0, math.pi / 2, 0.0),
    (0.0, -0.1104, 0.0, -math.pi / 2),
    (0.0, -0.096, 0.0, 0.0),
    (0.0634, 0.0, math.pi / 2, -math.pi / 2),
    (0.07505, 0.0, -math.pi / 2, math.pi / 2),
    (0.0456, 0.0, 0.0, 0.0),
]

LIMITS = [(math.radians(lo), math.radians(hi)) for lo, hi in DEFAULT_LIMITS_DEG]

# (joint 2, joint 3, joint 4) [rad] postures used as IK starting points
POSTURES = [(-0.43, -2.2, 1.06), (0.3, -1.9, 0.0), (-0.9, -1.2, 0.6)]


def _dh(theta, d, a, alpha):
    ct, st, ca, sa = math.cos(theta), math.sin(theta), math.cos(alpha), math.sin(alpha)
    return np.array([[ct, -st * ca, st * sa, a * ct],
                     [st, ct * ca, -ct * sa, a * st],
                     [0.0, sa, ca, d],
                     [0.0, 0.0, 0.0, 1.0]])


def fk_frames(q):
    """All joint frames: list of 7 4x4 transforms T(base ← frame i), i = 0..6 (6 = flange)."""
    T = np.eye(4)
    frames = [T]
    for qi, (d, a, alpha, off) in zip(q, DH):
        T = T @ _dh(qi + off, d, a, alpha)
        frames.append(T)
    return frames


def fk(q):
    """Joint angles [rad] (6) → 4x4 transform T(base_link ← link6_flange)."""
    return fk_frames(q)[-1]


def jacobian(q):
    """6x6 geometric Jacobian of the flange (rows: linear xyz, angular xyz) in base_link."""
    frames = fk_frames(q)
    p_end = frames[-1][:3, 3]
    J = np.zeros((6, 6))
    for i in range(6):
        z = frames[i][:3, 2]
        p = frames[i][:3, 3]
        J[:3, i] = np.cross(z, p_end - p)
        J[3:, i] = z
    return J


def pose_error(T, T_target):
    """6-vector error (position, rotation-vector-like) from T to T_target, in base_link."""
    dp = T_target[:3, 3] - T[:3, 3]
    R, Rd = T[:3, :3], T_target[:3, :3]
    dr = 0.5 * sum(np.cross(R[:, k], Rd[:, k]) for k in range(3))
    # The cross-product error vanishes for a 180-degree flip; detect it explicitly
    if np.trace(R.T @ Rd) < -0.99:
        dr = dr + 0.5 * R[:, 0]
    return np.concatenate([dp, dr])


def within_limits(q, limits=LIMITS, eps=1e-6):
    return all(lo - eps <= v <= hi + eps for v, (lo, hi) in zip(q, limits))


def _solve_from(T_target, q0, limits, max_iter, pos_tol, rot_tol):
    q = np.array(q0, np.float64)
    lo = np.array([l for l, _ in limits])
    hi = np.array([h for _, h in limits])
    W = np.diag([1.0, 1.0, 1.0, 0.2, 0.2, 0.2])     # metres vs radians: weight rotation less
    for _ in range(max_iter):
        e = pose_error(fk(q), T_target)
        if np.linalg.norm(e[:3]) < pos_tol and np.linalg.norm(e[3:]) < rot_tol:
            return q, True
        J = jacobian(q)
        Jw, ew = W @ J, W @ e
        lam = 0.02 + 2.0 * np.linalg.norm(ew)          # damping grows when far away
        dq = Jw.T @ np.linalg.solve(Jw @ Jw.T + (lam ** 2) * np.eye(6), ew)
        step = np.max(np.abs(dq))
        if step > 0.3:
            dq *= 0.3 / step
        q = np.clip(q + dq, lo, hi)
    e = pose_error(fk(q), T_target)
    return q, bool(np.linalg.norm(e[:3]) < pos_tol and np.linalg.norm(e[3:]) < rot_tol)


def ik(T_target, seed, limits=LIMITS, pos_tol=5e-4, rot_tol=5e-3, max_iter=150,
       restarts=12, rng_seed=0):
    """Inverse kinematics for the flange pose T_target (4x4, base_link).

    Damped least squares, starting from `seed` (usually the current joints, so the closest
    solution is found first), then from a few deterministic random starts. Among converged
    solutions the one closest to `seed` is returned. Returns a list of 6 angles [rad] or None.
    """
    seed = np.array(seed, np.float64)
    rng = np.random.default_rng(rng_seed)
    starts = [seed]
    # Structured starts: base turned towards the target, arm in typical reaching postures
    # (the first one is the "gripper pointing down over the table" posture)
    yaw = math.atan2(T_target[1, 3], T_target[0, 3])
    for j2, j3, j4 in POSTURES:
        for dj1 in (0.35, 0.0, -0.35):
            starts.append(np.clip([yaw + dj1, j2, j3, j4, 0.0, seed[5]],
                                  [lo for lo, _ in limits], [hi for _, hi in limits]))
    for _ in range(restarts):
        starts.append(np.array([rng.uniform(lo, hi) * 0.8 for lo, hi in limits]))
    n_structured = 1 + 3 * len(POSTURES)
    best = None
    for k, q0 in enumerate(starts):
        if best is not None and k >= n_structured:
            break                      # random restarts only when nothing else converged
        q, ok = _solve_from(T_target, q0, limits, max_iter, pos_tol, rot_tol)
        if not ok:
            continue
        cost = float(np.max(np.abs(q - seed)))
        if best is None or cost < best[1]:
            best = (q, cost)
        if k == 0:                     # converged from the seed itself: that is the one we want
            break
    return None if best is None else [float(v) for v in best[0]]


def matrix_to_quat(R):
    """3x3 rotation matrix → (x, y, z, w)."""
    R = np.asarray(R, np.float64)
    tr = R[0, 0] + R[1, 1] + R[2, 2]
    if tr > 0:
        s = math.sqrt(tr + 1.0) * 2
        return ((R[2, 1] - R[1, 2]) / s, (R[0, 2] - R[2, 0]) / s, (R[1, 0] - R[0, 1]) / s, 0.25 * s)
    if R[0, 0] > R[1, 1] and R[0, 0] > R[2, 2]:
        s = math.sqrt(1.0 + R[0, 0] - R[1, 1] - R[2, 2]) * 2
        return (0.25 * s, (R[0, 1] + R[1, 0]) / s, (R[0, 2] + R[2, 0]) / s, (R[2, 1] - R[1, 2]) / s)
    if R[1, 1] > R[2, 2]:
        s = math.sqrt(1.0 + R[1, 1] - R[0, 0] - R[2, 2]) * 2
        return ((R[0, 1] + R[1, 0]) / s, 0.25 * s, (R[1, 2] + R[2, 1]) / s, (R[0, 2] - R[2, 0]) / s)
    s = math.sqrt(1.0 + R[2, 2] - R[0, 0] - R[1, 1]) * 2
    return ((R[0, 2] + R[2, 0]) / s, (R[1, 2] + R[2, 1]) / s, 0.25 * s, (R[1, 0] - R[0, 1]) / s)
