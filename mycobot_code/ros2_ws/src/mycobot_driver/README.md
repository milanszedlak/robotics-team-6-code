# mycobot_driver: ROS 2 driver for the myCobot 280 Pi (runs ON the arm's Pi)

```
arm's Raspberry Pi (ROS 2 Jazzy)                         laptop / NUC (ROS 2 Jazzy)
mycobot_driver_node ── serial /dev/ttyAMA0 ──▶ servos      arm_task_node, MoveIt, ros2 CLI ...
  /joint_states, TF, /arm/*, actions  ◀──── DDS over the Ethernet cable (same ROS_DOMAIN_ID) ────▶
```

The driver owns the arm's serial port and is deliberately light: vision, inverse kinematics and the
pick/place logic run on the laptop / NUC (`mycobot_vision_grasp`).

## Interfaces

| Name | Type | Notes |
|---|---|---|
| `/joint_states` | `sensor_msgs/JointState` | radians, 10 Hz; also the gripper joint (`gripper_controller`) |
| TF `base_link → link6_flange` | tf2 | from the arm's forward kinematics |
| `/arm/flange_pose` | `geometry_msgs/PoseStamped` | flange-face centre in `base_link` (handy for calibration) |
| `/arm_controller/follow_joint_trajectory` | `control_msgs/FollowJointTrajectory` | what MoveIt and `arm_task_node` use |
| `/gripper_action_controller/gripper_cmd` | `control_msgs/GripperCommand` | position 0.0 = open, -0.7 = closed |
| `/arm/joint_command` | `std_msgs/Float64MultiArray` | 6 angles in **degrees**, fire-and-forget |
| `/arm/go_home`, `/arm/stop`, `/arm/power_on`, `/arm/release_servos`, `/arm/open_gripper`, `/arm/close_gripper` | `std_srvs/Trigger` | |

### Frames
`base_link` is the arm firmware's own base frame (the frame of pymycobot `get_coords()`): origin on
the joint-1 axis at the bottom of the base, z up. `link6_flange` is the joint-6 flange face, +z
pointing out of the flange. `mycobot_driver/kinematics.py` reproduces the firmware's forward
kinematics to 0.1 mm / 0.1° (checked against 20 poses read from this arm, see
`test/test_kinematics.py`), and also provides the inverse kinematics used on the laptop.

**Reach with the gripper pointing down** (10 cm gripper, block on the base plane): a ring about
**12–25 cm** from the joint-1 axis. Closer than ~10 cm the wrist runs into itself.

## 1. Pi setup (once, already done on the team arm)

```bash
ssh elephant@10.42.0.107
sudo apt update && sudo apt install ros-jazzy-control-msgs
mkdir -p ~/ros2_ws/src            # copy cobot_interfaces and mycobot_driver into ~/ros2_ws/src
cd ~/ros2_ws && colcon build --symlink-install
echo 'source ~/ros2_ws/install/setup.bash' >> ~/.bashrc
```

The Pi's `~/.bashrc` already sets `ROS_DOMAIN_ID=6`; every machine and terminal that talks to the
arm needs the same value (`export ROS_DOMAIN_ID=6`, in `~/.bashrc` and/or `~/.zshrc`).

To update the code on the Pi after changing it on the laptop:

```bash
cd ~/Documents/robotics-team-6-code/mycobot_code/ros2_ws/src
tar --exclude=__pycache__ -czf - cobot_interfaces mycobot_driver | ssh elephant@10.42.0.107 \
  'tar -xzf - -C ~/ros2_ws/src && cd ~/ros2_ws && source /opt/ros/jazzy/setup.bash && colcon build --symlink-install'
```

Elephant's own workspace (`~/colcon_ws`) is untouched. Don't run its nodes at the same time as
this driver: only one program can use the serial port.

## 2. Run

On the Pi:

```bash
ros2 launch mycobot_driver driver.launch.py
```

From the laptop (same `ROS_DOMAIN_ID`):

```bash
ros2 topic echo /joint_states                                                     # radians
ros2 service call /arm/power_on std_srvs/srv/Trigger
ros2 service call /arm/go_home std_srvs/srv/Trigger                               # all joints 0 = upright
ros2 service call /arm/open_gripper std_srvs/srv/Trigger
ros2 service call /arm/close_gripper std_srvs/srv/Trigger
ros2 topic pub --once /arm/joint_command std_msgs/msg/Float64MultiArray "{data: [30, 0, 0, 0, 0, 0]}"  # DEGREES
ros2 service call /arm/stop std_srvs/srv/Trigger
ros2 service call /arm/release_servos std_srvs/srv/Trigger                        # arm goes limp!
```

## Testing without the arm

On any machine:

```bash
ros2 launch mycobot_driver driver.launch.py backend:=fake
```

Unit tests (no ROS needed): `python3 -m pytest test -v`

Settings are in `config/driver.yaml`.
