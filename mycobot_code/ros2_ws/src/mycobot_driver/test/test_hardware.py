import os
import sys
import time

import pytest

sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..'))

from mycobot_driver.hardware import ArmError, FakeArm, open_backend  # noqa: E402


def test_fake_arm_moves_towards_target():
    arm = FakeArm()
    arm.send_angles([10, 0, 0, 0, 0, 0], 100)
    time.sleep(0.1)
    a = arm.get_angles()
    assert 0 < a[0] <= 10
    assert arm.call('is_moving') in (0, 1)


def test_fake_gripper():
    arm = FakeArm()
    arm.call('set_gripper_value', 0, 50)
    assert arm.call('get_gripper_value') == 0


def test_disallowed_command_rejected():
    with pytest.raises(ArmError):
        FakeArm().call('__init__')


def test_unknown_backend():
    with pytest.raises(ValueError):
        open_backend('tcp')
