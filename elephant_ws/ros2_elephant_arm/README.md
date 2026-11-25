# ros2_elephant_arm — the myCobot 280 Pi side of the architecture

This workspace is the **"Actuators on myCobot 280Pi" / `mycobot_ros2` (Drivers & Gripper Control)**
box of the team architecture. It runs **on the arm's Raspberry Pi** and is the only thing that
talks to the arm's serial port. It does no planning, vision or task logic. Those run on the NUC
(for now, the laptop):

```
 NUC / laptop                                              arm Pi (this workspace)
 ┌──────────────────────────────┐                          ┌──────────────────────────────┐
 │ Task coordinator (py_trees)  │── gripper goals ───────▶ │ mycobot_driver               │── serial ──▶ arm
 │ MoveIt 2 (planning + IK)     │── trajectories ────────▶ │   FollowJointTrajectory      │
 │                              │◀─ /joint_states 20 Hz ── │   GripperCommand             │
 │ RViz                         │◀─ /tf, /robot_description│ robot_state_publisher (URDF) │
 └──────────────────────────────┘◀─ /arm/status ───────── └──────────────────────────────┘
```

| Package | What it is | Where it runs |
|---|---|---|
| `mycobot_driver` | the driver node + launch file | Pi |
| `mycobot_description` | URDF of the arm + gripper. Frames and joint angles match the arm firmware (checked against 20 poses read from the real arm). | Pi (TF) **and** NUC/laptop (MoveIt, RViz) |

All machines need the same `ROS_DOMAIN_ID` (team: **6**).

## The interface

### Published by the Pi
| Name | Type | Content |
|---|---|---|
| `/joint_states` | `sensor_msgs/JointState` | `joint1`…`joint6` [rad] = servo angles, plus `gripper_joint` = finger gap [m], 20 Hz |
| `/arm/status` | `std_msgs/String` | `IDLE`, `MOVING`, `ERROR` (cannot read arm), `RELEASED` (servos limp) |
| `/robot_description` | `std_msgs/String` (latched) | the URDF |
| `/tf`, `/tf_static` | | `base_link → link1 … link6 → link6_flange → gripper_base → gripper_tcp` |

`base_link` = the firmware's base frame: origin on the joint-1 axis at the bottom of the base, z up.
`gripper_tcp` = the point between the fingers (★ `TCP_OFFSET` in `generate_urdf.py`, 10 cm, check it).

### Commands to the Pi
| Name | Type | Use |
|---|---|---|
| `/arm_controller/follow_joint_trajectory` | action `control_msgs/FollowJointTrajectory` | **MoveIt 2** executes plans through this |
| `/gripper_controller/gripper_cmd` | action `control_msgs/GripperCommand` | **MoveIt 2 / coordinator** gripper. `position` = finger gap [m], 0 = closed, 0.04 = open. `stalled: true` = closed on something |
| `/arm_controller/joint_trajectory` | topic `trajectory_msgs/JointTrajectory` | same as the action, no feedback |
| `/arm/joint_command` | topic `std_msgs/Float64MultiArray` | quick test: 6 joint angles in **degrees** |
| `/arm/gripper_command` | topic `std_msgs/Int32` | quick test: 0 = closed … 100 = open |
| `/arm/stop` | service `std_srvs/Trigger` | stop now (cancels any motion) |
| `/arm/home` | service `std_srvs/Trigger` | go to `home_deg` (straight up) |
| `/arm/open_gripper`, `/arm/close_gripper` | service `std_srvs/Trigger` | |
| `/arm/power_on`, `/arm/release_servos` | service `std_srvs/Trigger` | release = arm goes limp, **hold it!** |

One arm motion at a time: a trajectory sent while the arm is moving is **rejected**. Targets
outside the joint limits are refused before anything moves.

How trajectories are played: the myCobot firmware only takes "go to these angles at speed
1–100". So the driver sends each waypoint when the previous one is due, with the speed worked out
from the segment's timing. Waypoints closer together than 0.1 s are skipped. Timing is
approximate (±~0.5 s); the goal succeeds once every joint is within 2° of the last point.

## Start it on the Pi

```bash
ssh elephant@10.42.0.107
export ROS_DOMAIN_ID=6
source ~/ros2_elephant_arm/install/setup.bash
ros2 launch mycobot_driver driver.launch.py
```
Only one program can use the serial port, so stop any old `cobot_arm` node or Elephant demo first.
`publish_tf:=false` skips robot_state_publisher.

## Use it from the laptop

```bash
export ROS_DOMAIN_ID=6
ros2 topic echo /joint_states
ros2 topic echo /arm/status

# move joints (degrees), open/close the gripper
ros2 topic pub --once /arm/joint_command std_msgs/msg/Float64MultiArray "{data: [30, 0, -45, 0, 0, 0]}"
ros2 service call /arm/close_gripper std_srvs/srv/Trigger
ros2 service call /arm/home std_srvs/srv/Trigger

# a timed trajectory, with feedback (radians, seconds)
ros2 action send_goal --feedback /arm_controller/follow_joint_trajectory control_msgs/action/FollowJointTrajectory \
  "{trajectory: {joint_names: [joint1, joint2], points: [
     {positions: [0.5, 0.3], time_from_start: {sec: 1}},
     {positions: [1.0, 0.5], time_from_start: {sec: 2}}]}}"

# gripper to a 1 cm gap
ros2 action send_goal /gripper_controller/gripper_cmd control_msgs/action/GripperCommand "{command: {position: 0.01}}"

# STOP
ros2 service call /arm/stop std_srvs/srv/Trigger
```

To see the arm in RViz, build `mycobot_description` on the laptop too and run
`ros2 launch mycobot_description view.launch.py`. To try it without the arm, use
`view.launch.py gui:=true` (sliders) or run the whole driver with `backend:=fake`.

### Hooking up MoveIt 2 (NUC side, not in this workspace)
Generate a MoveIt config from `mycobot_description/urdf/mycobot_280_pi.urdf` (MoveIt Setup
Assistant). The planning group is `joint1`…`joint6` (tip `gripper_tcp`) and the gripper group is
`gripper_joint`. In `moveit_controllers.yaml`:
```yaml
moveit_controller_manager: moveit_simple_controller_manager/MoveItSimpleControllerManager
moveit_simple_controller_manager:
  controller_names: [arm_controller, gripper_controller]
  arm_controller:
    type: FollowJointTrajectory
    action_ns: follow_joint_trajectory
    default: true
    joints: [joint1, joint2, joint3, joint4, joint5, joint6]
  gripper_controller:
    type: GripperCommand
    action_ns: gripper_cmd
    default: true
    joints: [gripper_joint]
```
Don't start MoveIt's own `ros2_control` / fake controllers or a `joint_state_publisher` while the
Pi driver is running. The Pi already provides `/joint_states`.

## Settings — `src/mycobot_driver/config/driver.yaml`
To check on the real arm (marked ★): `max_deg_per_s_at_speed_100` (affects trajectory timing) and
`gripper_max_gap`. If you change the gripper geometry, edit the constants in
`src/mycobot_description/scripts/generate_urdf.py` and regenerate:
`python3 scripts/generate_urdf.py > urdf/mycobot_280_pi.urdf`.

## Build / install on the Pi

Needs ROS 2 Jazzy with `control_msgs`, `trajectory_msgs`, `robot_state_publisher`, plus `pymycobot`:
```bash
sudo apt install ros-jazzy-control-msgs ros-jazzy-robot-state-publisher   # if missing
```
Copy from the laptop and build:
```bash
cd ~/Documents/robotics-team-6-code/mycobot_code/ros2_elephant_arm
tar --exclude=__pycache__ --exclude=build --exclude=install --exclude=log -czf - src README.md | \
  ssh elephant@10.42.0.107 'mkdir -p ~/ros2_elephant_arm && tar -xzf - -C ~/ros2_elephant_arm && \
    cd ~/ros2_elephant_arm && source /opt/ros/jazzy/setup.bash && colcon build --symlink-install'
```
(The old `cobot_arm` package may still be in `~/ros2_elephant_arm/src` on the Pi. Delete it there if
you no longer want it.)

## Tests (no ROS or arm needed)
```bash
python3 -m pytest src/mycobot_description/test src/mycobot_driver/test -q
```
