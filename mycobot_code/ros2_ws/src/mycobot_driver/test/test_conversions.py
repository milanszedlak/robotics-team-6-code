import os
import sys

sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..'))

from mycobot_driver.conversions import (clamp_angles, gripper_position_to_value,  # noqa: E402
                                        gripper_value_to_position, reached, speed_percent)


def test_clamp():
    assert clamp_angles([200, -200, 0, 0, 0, 0]) == [165, -135, 0, 0, 0, 0]


def test_speed_percent():
    # 80 deg in 1 s at 160 deg/s max -> 50 %
    assert speed_percent([0] * 6, [80, 0, 0, 0, 0, 0], 1.0, 160.0) == 50
    assert speed_percent([0] * 6, [500, 0, 0, 0, 0, 0], 1.0, 160.0) == 100
    assert speed_percent([0] * 6, [1, 0, 0, 0, 0, 0], 10.0, 160.0) == 5


def test_gripper_mapping_roundtrip():
    assert gripper_position_to_value(0.0, 0.0, -0.7) == 100
    assert gripper_position_to_value(-0.7, 0.0, -0.7) == 0
    assert gripper_position_to_value(-0.35, 0.0, -0.7) == 50
    assert abs(gripper_value_to_position(50, 0.0, -0.7) + 0.35) < 1e-9


def test_reached():
    assert reached([0, 1, 2], [0.5, 1.5, 2.5], 1.0)
    assert not reached([0, 1, 2], [0, 1, 5], 1.0)
