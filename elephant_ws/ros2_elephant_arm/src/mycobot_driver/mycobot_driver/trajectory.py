"""Turn a joint trajectory into timed myCobot commands (no ROS imports, unit-tested).

The myCobot firmware has no trajectory interface: it takes one target (send_angles) plus a speed
1..100, and with fresh mode on a new target replaces the current one. So a trajectory is played
back by sending each waypoint when the previous one is due, with the speed chosen so the arm
covers that segment in the time the trajectory gives it.
"""
import math

# myCobot 280 joint limits in degrees (slightly inside the factory limits; same as the URDF)
LIMITS_DEG = [(-165, 165), (-135, 135), (-150, 150), (-145, 145), (-165, 165), (-175, 175)]


class TrajectoryError(ValueError):
    pass


def speed_for(deg, dt, max_deg_per_s, min_speed=5, max_speed=100):
    """myCobot speed (int) to move `deg` degrees in `dt` seconds."""
    if dt <= 1e-6:
        return max_speed
    s = math.ceil(100.0 * (deg / dt) / max_deg_per_s)
    return int(max(min_speed, min(max_speed, s)))


def check_limits(deg):
    for i, (a, (lo, hi)) in enumerate(zip(deg, LIMITS_DEG)):
        if not lo - 1e-6 <= a <= hi + 1e-6:
            raise TrajectoryError(f'joint{i + 1} = {a:.1f} deg is outside its limits [{lo}, {hi}]')


def plan_commands(current_deg, points, max_deg_per_s, min_period=0.1, default_speed=40,
                  min_speed=5, max_speed=100):
    """Plan when to send which target.

    current_deg: 6 current joint angles [deg]
    points:      [(time_from_start [s], 6 angles [deg]), ...], times non-decreasing
    Returns [(send_at [s], target_deg, speed), ...] and the trajectory duration [s].

    Waypoints closer together than min_period are thinned out (the serial link and the
    firmware cannot follow faster than that); the last waypoint is always kept.
    """
    if not points:
        raise TrajectoryError('trajectory has no points')
    last_t = -1.0
    for t, deg in points:
        if len(deg) != 6:
            raise TrajectoryError(f'need 6 joint positions per point, got {len(deg)}')
        if t < last_t - 1e-9:
            raise TrajectoryError('time_from_start must not decrease')
        last_t = t
        check_limits(deg)

    # thin out: keep a point if it is >= min_period after the previously kept one, or it is last
    kept, prev_t = [], 0.0
    for k, (t, deg) in enumerate(points):
        if k == len(points) - 1 or t - prev_t >= min_period - 1e-9:
            kept.append((t, list(deg)))
            prev_t = t

    commands, prev_t, prev_deg = [], 0.0, list(current_deg)
    for t, deg in kept:
        dt = t - prev_t
        delta = max(abs(a - b) for a, b in zip(deg, prev_deg))
        if dt <= 1e-6:
            # no timing given (e.g. a single point at t=0): use the default speed
            speed = default_speed
        else:
            speed = speed_for(delta, dt, max_deg_per_s, min_speed, max_speed)
        commands.append((prev_t, deg, speed))
        prev_t, prev_deg = t, deg
    return commands, kept[-1][0]


def estimate_duration(from_deg, to_deg, speed, max_deg_per_s):
    """Rough time [s] for a single send_angles move at the given speed."""
    delta = max(abs(a - b) for a, b in zip(from_deg, to_deg))
    return delta / (max_deg_per_s * max(speed, 1) / 100.0)
