"""Pure helper maths (no ROS), so it can be unit-tested."""
import math

# myCobot 280 joint limits in degrees (slightly inside the factory limits)
DEFAULT_LIMITS_DEG = [(-165, 165), (-135, 135), (-150, 150), (-145, 145), (-165, 165), (-175, 175)]


def clamp_angles(deg, limits=DEFAULT_LIMITS_DEG):
    return [max(lo, min(hi, float(a))) for a, (lo, hi) in zip(deg, limits)]


def rad_to_deg(values):
    return [math.degrees(v) for v in values]


def deg_to_rad(values):
    return [math.radians(v) for v in values]


def speed_percent(start_deg, goal_deg, duration_s, max_deg_per_s, lo=5, hi=100):
    """myCobot speed (1-100) that makes the largest joint move take about duration_s."""
    delta = max((abs(g - s) for s, g in zip(start_deg, goal_deg)), default=0.0)
    if duration_s <= 0 or delta == 0:
        return hi if duration_s <= 0 else lo
    pct = 100.0 * (delta / duration_s) / max_deg_per_s
    return int(max(lo, min(hi, math.ceil(pct))))


def gripper_position_to_value(position, open_pos, closed_pos):
    """Map a ROS gripper position onto the myCobot gripper value (100 = open, 0 = closed)."""
    if open_pos == closed_pos:
        return 100
    frac = (position - closed_pos) / (open_pos - closed_pos)   # 1 = open, 0 = closed
    return int(round(max(0.0, min(1.0, frac)) * 100))


def gripper_value_to_position(value, open_pos, closed_pos):
    frac = max(0.0, min(100.0, float(value))) / 100.0
    return closed_pos + frac * (open_pos - closed_pos)


def reached(current_deg, goal_deg, tol_deg):
    return all(abs(c - g) <= tol_deg for c, g in zip(current_deg, goal_deg))
