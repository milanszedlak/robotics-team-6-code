"""Trajectory playback planning (no ROS, no arm needed)."""
import os
import sys

import pytest

sys.path.insert(0, os.path.join(os.path.dirname(__file__), '..'))

from mycobot_driver.trajectory import (TrajectoryError, check_limits, plan_commands,  # noqa: E402
                                       speed_for)

Z = [0.0] * 6


def test_speed_matches_timing():
    # 80 deg in 1 s at 160 deg/s max = speed 50
    assert speed_for(80, 1.0, 160) == 50
    assert speed_for(1000, 1.0, 160) == 100          # clamped
    assert speed_for(0, 1.0, 160) == 5               # min speed


def test_each_point_sent_when_previous_is_due():
    pts = [(1.0, [10, 0, 0, 0, 0, 0]), (2.0, [20, 0, 0, 0, 0, 0])]
    cmds, dur = plan_commands(Z, pts, 160, min_period=0.1)
    assert dur == 2.0
    assert [c[0] for c in cmds] == [0.0, 1.0]
    assert cmds[-1][1] == [20, 0, 0, 0, 0, 0]


def test_dense_points_thinned_but_last_kept():
    pts = [(i * 0.01, [i * 0.1, 0, 0, 0, 0, 0]) for i in range(101)]
    cmds, dur = plan_commands(Z, pts, 160, min_period=0.1)
    assert len(cmds) <= 11
    assert cmds[-1][1][0] == pytest.approx(10.0)
    assert dur == pytest.approx(1.0)


def test_untimed_single_point_uses_default_speed():
    cmds, dur = plan_commands(Z, [(0.0, [30, 0, 0, 0, 0, 0])], 160, default_speed=42)
    assert cmds == [(0.0, [30, 0, 0, 0, 0, 0], 42)] and dur == 0.0


@pytest.mark.parametrize('pts', [
    [],
    [(1.0, [0, 0, 0])],
    [(1.0, Z), (0.5, Z)],
    [(1.0, [170, 0, 0, 0, 0, 0])],
])
def test_bad_trajectories_rejected(pts):
    with pytest.raises(TrajectoryError):
        plan_commands(Z, pts, 160)


def test_limits():
    check_limits([165, -135, 150, -145, 165, -175])
    with pytest.raises(TrajectoryError):
        check_limits([0, 136, 0, 0, 0, 0])
