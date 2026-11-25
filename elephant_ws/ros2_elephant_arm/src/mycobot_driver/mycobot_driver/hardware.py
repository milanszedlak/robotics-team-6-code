"""Arm backends used by mycobot_driver (no ROS imports).

  SerialArm: the real myCobot 280 Pi, through pymycobot on the Pi's serial port.
  FakeArm:   a simulated arm (joints move towards their target at a fixed rate), for testing
             the whole stack on a laptop without hardware.

Both expose the same small surface: call(cmd, *args), get_angles(), send_angles(), close().
Only the commands in ALLOWED can be called.
"""
import threading
import time

ALLOWED = {
    'get_angles', 'send_angles', 'send_angle', 'is_moving', 'stop',
    'power_on', 'power_off', 'release_all_servos', 'is_power_on',
    'get_gripper_value', 'set_gripper_value', 'set_gripper_state',
}


class ArmError(RuntimeError):
    pass


class _Backend:
    def __init__(self, device):
        self._dev = device
        self._lock = threading.Lock()       # one serial transaction at a time

    def call(self, cmd, *args):
        if cmd not in ALLOWED:
            raise ArmError(f'command not allowed: {cmd!r}')
        with self._lock:
            return getattr(self._dev, cmd)(*args)

    def get_angles(self):
        a = self.call('get_angles')
        # pymycobot returns -1 / [] / None when the servos do not answer
        if not isinstance(a, (list, tuple)) or len(a) != 6:
            raise ArmError(f'bad angles from arm: {a!r} (is the arm powered?)')
        return [float(x) for x in a]

    def send_angles(self, deg, speed):
        return self.call('send_angles', [round(float(x), 2) for x in deg], int(speed))

    def close(self):
        pass


class SerialArm(_Backend):
    def __init__(self, port='/dev/ttyAMA0', baud=1000000, fresh_mode=True):
        try:                                    # pymycobot >= 3.6
            from pymycobot import MyCobot280 as Arm
        except ImportError:                     # older pymycobot
            from pymycobot.mycobot import MyCobot as Arm
        super().__init__(Arm(port, int(baud)))
        time.sleep(0.05)
        if fresh_mode and hasattr(self._dev, 'set_fresh_mode'):
            # 1 = a new goal replaces the current one instead of queuing behind it
            with self._lock:
                self._dev.set_fresh_mode(1)

    def close(self):
        ser = getattr(self._dev, '_serial_port', None)
        if ser is not None:
            try:
                ser.close()
            except OSError:
                pass


class _SimulatedDevice:
    """Stand-in for the real arm: joints move towards their target at a fixed rate."""

    DEG_PER_S_AT_100 = 160.0

    def __init__(self):
        self.angles = [0.0] * 6
        self.target = [0.0] * 6
        self.speed = 50
        self.gripper = 100
        self.last = time.monotonic()

    def _update(self):
        now = time.monotonic()
        step = self.DEG_PER_S_AT_100 * self.speed / 100.0 * (now - self.last)
        self.last = now
        for i in range(6):
            d = self.target[i] - self.angles[i]
            self.angles[i] += max(-step, min(step, d))

    def get_angles(self):
        self._update()
        return [round(a, 2) for a in self.angles]

    def send_angles(self, angles, speed):
        self._update()
        self.target, self.speed = [float(a) for a in angles], speed

    def send_angle(self, joint_id, angle, speed):
        self._update()
        self.target[joint_id - 1], self.speed = float(angle), speed

    def is_moving(self):
        self._update()
        return int(any(abs(t - a) > 0.1 for t, a in zip(self.target, self.angles)))

    def stop(self):
        self._update()
        self.target = list(self.angles)

    def get_gripper_value(self):
        return self.gripper

    def set_gripper_value(self, value, speed):
        self.gripper = int(value)

    def set_gripper_state(self, flag, speed):
        self.gripper = 0 if flag else 100

    def power_on(self):
        pass

    def power_off(self):
        pass

    def release_all_servos(self):
        pass

    def is_power_on(self):
        return 1


class FakeArm(_Backend):
    def __init__(self):
        super().__init__(_SimulatedDevice())


def open_backend(kind, port='/dev/ttyAMA0', baud=1000000):
    if kind == 'fake':
        return FakeArm()
    if kind == 'serial':
        return SerialArm(port, baud)
    raise ValueError(f"backend must be 'serial' or 'fake', not {kind!r}")
