# mycobot_vision_grasp: locate, pick and place blocks with a fixed depth camera

Runs on the **laptop / NUC** (not on the arm's Pi). It finds coloured blocks with a RealSense D435
(`block_vision_node`), converts them into the arm's base frame, plans the grasp with the built-in
myCobot 280 kinematics and drives the arm through `mycobot_driver`, which runs on the arm's Pi.

```
Pi:            mycobot_driver_node ─serial─▶ arm
                    ▲ FollowJointTrajectory / GripperCommand, /joint_states, TF   (DDS over the cable)
Laptop / NUC:  D435 ─USB─▶ realsense2_camera ─▶ block_vision_node ─/vision/blocks─▶ arm_task_node
               your program / ros2 CLI ─▶ /arm/locate_blocks, /arm/pick_block, /arm/place_block
```

`arm_task_node` has two modes:
- **Command mode** (default): waits for `/arm/locate_blocks`, `/arm/pick_block`, `/arm/place_block` (see [Command API](#command-api)).
- **Autorun** (`autorun:=true`): the autonomous vehicle hand-off loop below.

Message interfaces are described in `cobot_interfaces/README.md`.

## Autorun flow (vehicle hand-off)

```
camera (fixed) ──/vision/blocks──▶ arm: at the home pose (not blocking the camera), average 3 frames to get the block pose
                                   arm: move above block → descend vertically → grasp → lift to carry pose
                                   arm ──/arm/holding = "red"──▶ vehicle
                                                                vehicle: drive to the red basket
                                   arm ◀──/vehicle/arrived = "red"── vehicle
                                   arm: check the colour matches → move to place pose → release
                                   arm ──/arm/state = "DONE"──▶ vehicle may leave
```

## Frames and transforms

```
Coordinates from the vision node: camera_color_optical_frame (x right, y down, z forward, metres)
     │
     │ T(base ← camera): constant, from config/camera_pose.yaml (published as a static TF by the launch file)
     ▼
Arm base base_link ──▶ used to plan the grasp position and angle
     │
     │ T(gripper centre ← base): current arm pose (only used to report "where is the block relative to the gripper")
     ▼
Gripper centre gripper_tcp ──▶ printed in the log and published on /arm/target_in_gripper
```

| Frame | Origin | Axes |
|---|---|---|
| `base_link` | Centre of the bottom of the arm base (on the joint-1 axis) | x forward, y left, z up |
| `camera_link` | Centre of the D435i body (pose set in `camera_pose.yaml`) | x = lens looking direction |
| `camera_color_optical_frame` | Colour lens | x right, y down, z forward (vision coordinates) |
| `link6_flange` (`ik_link`) | **Centre of the joint-6 flange face** (where the gripper is mounted). Rotates with joint 6 | From the URDF; assumed +z = gripper forward |
| `gripper_tcp` | **Grasp point between the two fingers** = flange-face centre moved `tcp_offset` (default 0.10 m) along gripper forward | z = gripper forward, x = actual finger closing direction (includes the 45° offset) |

`gripper_tcp` is a TF published by the arm node; add a TF display in RViz to see it. Check that:
- its origin is between the two fingers → otherwise adjust `tcp_offset`
- the red x axis matches the finger opening/closing direction → otherwise adjust `gripper_roll_offset_deg` (45 ↔ -45) or `closing_axis`

## Gripper hardware constraints

- **Tilted 45° at zero**: with joint 6 at 0°, the fingers are tilted 45° when the gripper is seen from the front. The grasp angle calculation removes this 45° so that the *actual* finger direction lines up with the block. The direction is set by `gripper_roll_offset_deg` (positive = counter-clockwise).
- **Joint 6 can only turn ±180°**: every computed joint solution is checked. If joint 6 is out of range, an equivalent angle is used; if that is not possible, the grasp rotated by 180° is used instead (a parallel gripper rotated by 180° is equivalent). When both work, the one with the smaller joint-6 rotation is chosen. If the limit would be hit during the descent, the arm stops and reports an error instead of forcing the motion.
- Thanks to the 180° symmetry, a ±180° range covers **every** block angle.

## Grasping the parallel edges
The vision node provides the 4 corners of the block's top face; the arm side then:
- estimates the block orientation from all 4 edges (long edges weigh more), so a 1 mm corner error causes only about 0.5° of angle error;
- presses the fingers against the two long edges (grasping across the narrow side). If the narrow side is wider than the gripper opening, the other side is tried; if both are too wide, the block is skipped;
- keeps the current gripper angle if no corners are given (all zero).

## Files

| File | Purpose |
|---|---|
| `mycobot_vision_grasp/grasp_node.py` | **Main arm program** (executable `arm_task_node`): command API + autorun loop |
| `mycobot_vision_grasp/block_vision_node.py` | **Vision node** (real D435 and Gazebo; executables `block_vision_node` / `sim_vision_node`) |
| `mycobot_vision_grasp/block_detector.py` | HSV detection → rotated rectangle → depth → 3D points |
| `mycobot_vision_grasp/pick_place_demo.py` | Example client: locate → pick → place (copy it into your own program) |
| `mycobot_vision_grasp/geometry.py` | Transforms, gripper orientation (incl. 45° offset), joint-6 limit, parallel-edge selection |
| `mycobot_vision_grasp/targeting.py` | Choosing a target among several blocks; tracking the same block while averaging |
| `mycobot_vision_grasp/fake_vehicle_node.py` | Fake vehicle (reports "arrived" a few seconds after "holding") |
| `mycobot_driver/kinematics.py` (other package) | Forward / inverse kinematics of the real arm (built-in IK, no MoveIt needed) |
| `config/arm_task.yaml` | **Arm and vision parameters** |
| `config/camera_pose.yaml` | **Pose of the fixed camera relative to the arm base (edit this after measuring)** |
| `config/camera_bridge.yaml` | Gazebo camera → the same topic names as a real D435i |
| `models/d435i_fixed.sdf` | Fixed D435i in Gazebo (placed automatically from camera_pose.yaml) |
| `launch/real_robot.launch.py` | **Real robot** (laptop / NUC): camera + vision + arm task node |
| `launch/arm_task.launch.py` | Gazebo simulation (and autorun on the real robot) |
| `vscode/` | VS Code settings; copy to `~/ros2_ws/.vscode/` |

---

## Step 1: Build

On the laptop / NUC the workspace is `mycobot_code/ros2_ws` in this repo; its `src/` holds
`cobot_interfaces`, `mycobot_driver` (for its kinematics) and `mycobot_vision_grasp`:

```bash
cd ~/Documents/robotics-team-6-code/mycobot_code/ros2_ws
rosdep install --from-paths src -y --ignore-src     # installs realsense2_camera etc.
```

```bash
colcon build --symlink-install
source install/setup.bash        # zsh: source install/setup.zsh
```

```bash
source install/setup.bash
```

Everyone (vision, arm, vehicle) needs the same copy of `cobot_interfaces`; the message definitions must be identical on all sides.

Make sure `src/` contains only one copy of each package. If an archive was extracted into an extra folder, colcon fails with "Duplicate package names not supported".

## Step 2: Set the camera pose (`config/camera_pose.yaml`)

```yaml
camera_pose:
  x: 0.25      # metres in front of the base
  y: 0.00      # left
  z: 0.60      # up
  roll: 0.0    # degrees
  pitch: 90.0  # 90 = lens pointing straight down
  yaw: 0.0
```

- Measure from the **centre of the bottom of the arm base** to the **centre of the D435i body**.
- Use rough values until the mounting is final. After editing the file, restart the launch file; no rebuild is needed (with `--symlink-install`).
- In simulation the launch file places the Gazebo camera at the same pose, so simulation and the real robot share one setting.
- The Gazebo world file needs the sensors plugin, otherwise the camera produces no images:
  ```xml
  <plugin filename="gz-sim-sensors-system" name="gz::sim::systems::Sensors">
    <render_engine>ogre2</render_engine>
  </plugin>
  ```

**Checking the camera pose**: put a block at a known spot on the table (e.g. 20 cm straight in front of the base) and read the base coordinates in the log:

```
[red] base frame (0.200, 0.000, 0.025) m │ relative to gripper centre (...) │ ...
```

- Constant x/y offset → adjust x/y in `camera_pose.yaml`
- Error grows with distance → the angles (pitch/yaw) are wrong
- Wrong height z → adjust z

## Step 3: Check the arm parameters (fields marked ★ in `config/arm_task.yaml`)

| Parameter | How to find it |
|---|---|
| `arm_joints`, `gripper_joint` | `ros2 topic echo /joint_states --once` |
| Controller action names | `ros2 action list` |
| `planning_group` | Simulation (MoveIt) only: `<group>` in `mycobot_moveit_config/config/*.srdf` |
| `approach_axis` | `+z` on the real arm (checked against the firmware); in RViz, the blue axis of `link6_flange` |
| `closing_axis` + `gripper_roll_offset_deg` | Set joint 6 to 0° and check in RViz that the red x axis of `gripper_tcp` matches the finger opening direction |
| `tcp_offset` | Distance from the flange face to the point between the fingers |
| `wrist_limits_deg` | Joint-6 range; keep within the driver's clamp (±175°) |
| `home_joints` | A pose where the arm **does not block the camera at all** (the arm returns here before every detection) |
| `carry_joints` / `place_joints` | Move the arm with MoveIt and read `/joint_states` |

## Step 4: Run

### A. Full Gazebo simulation (no vision node or vehicle needed)

```bash
# Terminal 1
ros2 launch mycobot_gazebo mycobot.gazebo.launch.py
```

```bash
# Terminal 2 (RViz is already opened by terminal 1)
ros2 launch mycobot_moveit_config move_group.launch.py use_rviz:=false
```

Wait for `You can start planning now!`, then:

```bash
# Terminal 3: camera bridge + simulated vision + fake vehicle + arm
ros2 launch mycobot_vision_grasp arm_task.launch.py
```

Put a few small red, blue and green blocks (about 6×2.5×2.5 cm) in the camera's view in Gazebo. Remove other red objects from the default world (e.g. `red_cylinder`, `coke_can`, `cheezit_big_original`), or the simulated vision will treat them as red blocks. To see the detections:

```bash
ros2 run rqt_image_view rqt_image_view /vision/debug_image
```

Example command to add a blue block (position in metres, `-Y` = rotation in radians):

```bash
ros2 run ros_gz_sim create -world default -name blue_block -x 0.20 -y 0.05 -z 0.0125 -Y 0.5 -string "<sdf version='1.9'><model name='blue_block'><link name='link'><inertial><mass>0.02</mass><inertia><ixx>2.1e-6</ixx><iyy>7.0e-6</iyy><izz>7.0e-6</izz></inertia></inertial><collision name='c'><geometry><box><size>0.06 0.025 0.025</size></box></geometry><surface><friction><ode><mu>2.0</mu><mu2>2.0</mu2></ode></friction></surface></collision><visual name='v'><geometry><box><size>0.06 0.025 0.025</size></box></geometry><material><ambient>0 0 0.8 1</ambient><diffuse>0 0 0.8 1</diffuse></material></visual></link></model></sdf>"
```

### B. Gazebo + the real vision program

After the vision node is running:

```bash
ros2 launch mycobot_vision_grasp arm_task.launch.py sim_vision:=false
```

### C. Real robot

Both machines need `export ROS_DOMAIN_ID=6` (also in zsh: add it to `~/.zshrc`). Plug the D435
into the laptop / NUC (USB 3).

```bash
# On the arm's Pi (ssh elephant@10.42.0.107)
ros2 launch mycobot_driver driver.launch.py
```

```bash
# On the laptop / NUC: camera + vision + arm task node (command mode)
ros2 launch mycobot_vision_grasp real_robot.launch.py
```

Wait for `Arm ready. Commands: ...`, then use the [Command API](#command-api). For the autonomous
vehicle loop instead: `real_robot.launch.py autorun:=true`.

Seeing what the camera sees (on the laptop / NUC):

```bash
ros2 run rqt_image_view rqt_image_view /vision/debug_image
```

### D. Laptop only, no arm and no camera

```bash
ros2 launch mycobot_driver driver.launch.py backend:=fake
ros2 run tf2_ros static_transform_publisher --x 0.25 --z 0.6 --pitch 1.5708 --frame-id base_link --child-frame-id camera_link
ros2 run tf2_ros static_transform_publisher --roll -1.5708 --yaw -1.5708 --frame-id camera_link --child-frame-id camera_color_optical_frame
ros2 run mycobot_vision_grasp arm_task_node --ros-args --params-file install/mycobot_vision_grasp/share/mycobot_vision_grasp/config/arm_task.yaml -p accept_unstamped:=true -p grasp_check_tolerance:=0.0
```

Then publish a fake block (see `cobot_interfaces/README.md` §3, with `ros2 topic pub -r 5`) and
use the commands below.

## Command API

| Name | Type | What it does |
|---|---|---|
| `/arm/locate_blocks` | service `cobot_interfaces/srv/LocateBlocks` | every block the camera sees, in `base_link` (optionally moves home first) |
| `/arm/pick_block` | action `cobot_interfaces/action/PickBlock` | open → home → locate → above → descend → grasp → lift → carry pose |
| `/arm/place_block` | action `cobot_interfaces/action/PlaceBlock` | named pose (`place` / `carry` / `home`) or an XYZ drop point → release |
| `/arm/open_gripper`, `/arm/close_gripper`, `/arm/go_home`, `/arm/stop` | `std_srvs/Trigger` | direct driver services (from `mycobot_driver`) |

One command runs at a time; goals sent while the arm is busy (or in autorun) are rejected.
Actions send their current stage as feedback and can be cancelled between stages.

```bash
ros2 service call /arm/locate_blocks cobot_interfaces/srv/LocateBlocks "{color: '', go_home: true}"
ros2 action send_goal --feedback /arm/pick_block cobot_interfaces/action/PickBlock "{color: red}"
ros2 action send_goal --feedback /arm/place_block cobot_interfaces/action/PlaceBlock "{location: place}"
ros2 action send_goal --feedback /arm/place_block cobot_interfaces/action/PlaceBlock \
  "{use_position: true, position: {x: 0.15, y: -0.15, z: 0.05}}"     # gripper centre at this point
```

Or all at once with the example client:

```bash
ros2 run mycobot_vision_grasp pick_place_demo --color red                 # locate, pick red, place pose
ros2 run mycobot_vision_grasp pick_place_demo --drop 0.15 -0.15 0.05      # pick any, drop at a point
ros2 run mycobot_vision_grasp pick_place_demo --locate-only
```

`ArmCommander` in `pick_place_demo.py` is a small blocking wrapper you can import from your own node.

**Reach**: with the gripper pointing down, the arm reaches about **12–25 cm** from the base axis
(the joint-1 axis). Blocks outside that ring fail with `No IK solution ... out of reach`.

### Calibrating with the arm

`/arm/flange_pose` (from the driver) is the flange-face centre in `base_link`; the gripper centre is
`tcp_offset` below it when the gripper points down. Jog the arm (`/arm/joint_command`, or release the
servos and move it by hand) until the fingertips touch a block or a table mark, then compare the
flange pose with what `/arm/locate_blocks` reports for that block: the difference is your
`camera_pose.yaml` error (or `tcp_offset` error, if it is only in z).

### Monitoring

```bash
ros2 topic echo /arm/state
```

```bash
ros2 topic echo /arm/flange_pose
```

```bash
ros2 topic echo /arm/target_in_gripper
```

## Developing in VS Code

1. Install the extensions **Python** (Microsoft) and, optionally, **Robot Developer Extensions for ROS 2**
2. Copy the settings:
   ```bash
   mkdir -p ~/ros2_ws/.vscode && cp src/mycobot_vision_grasp/vscode/*.json ~/ros2_ws/.vscode/
   ```
3. Open VS Code from a sourced terminal:
   ```bash
   source ~/ros2_ws/install/setup.bash && code ~/ros2_ws
   ```
4. Useful shortcuts:
   - `Ctrl+Shift+B`: build both packages
   - `F5` → "Debug arm_task_node": set breakpoints in `grasp_node.py` (start the other nodes in terminals first)
   - Testing panel: run the tests in `test/` (no ROS needed)

## Troubleshooting

| Symptom | Likely cause / fix |
|---|---|
| Two Gazebo windows / simulation very slow | An old `gz sim` server is still running. Check with `ps aux \| grep "gz sim" \| grep -v grep` and stop it with `pkill -9 -f "gz sim"` |
| move_group dies with `stomp_moveit/StompPlanner ... does not exist` | STOMP is not installed: `sudo apt install ros-jazzy-moveit-planners-stomp` (or remove `"stomp"` from the planning pipelines) |
| Stuck at "Still waiting for arm_controller action" | The driver is not running on the Pi, or this terminal has a different `ROS_DOMAIN_ID` (must be 6 on both; zsh users: set it in `~/.zshrc`). Check `ros2 topic echo /joint_states` |
| Stuck at "Still waiting for TF base_link ← link6_flange" | Same as above (the driver publishes this TF) |
| Stuck at "Still waiting for TF base_link ← camera_color_optical_frame" | The RealSense driver is not running (it publishes camera_link → optical frame) |
| Stuck at "Still waiting for MoveIt /compute_ik" | Simulation only: move_group is not running or crashed; check its terminal output |
| `realsense2_camera is not installed` | `sudo apt install ros-jazzy-realsense2-camera`, or start the camera yourself and pass `camera:=false` |
| Goal rejected | Another command is still running, the node is in `autorun`, or it is not ready yet (see its log) |
| Stuck at "Still waiting for TF base_link ← camera_color_optical_frame" | Simulation: the launch file did not start correctly; real robot: the RealSense driver is not running or `publish_tf` is off |
| "No new /vision/blocks received" | The vision node is not running; or the timestamp is not the RGB capture time; or in simulation the vision node is not using `use_sim_time:=true` |
| Gazebo camera shows nothing | The world file is missing the `gz-sim-sensors-system` plugin |
| Position off by a constant few cm | x/y/z in `camera_pose.yaml` are wrong |
| Error grows with distance | Angles in `camera_pose.yaml` are wrong |
| Block found only sometimes | The arm blocks the camera at `home_joints` |
| Gripper angle off by 45° or 90° | Wrong sign of `gripper_roll_offset_deg`, or wrong `closing_axis` |
| "Joint 6 would hit its ±180° limit" | Right at the edge of the limit; move the block slightly or check `wrist_limits_deg` |
| No IK solution | Out of reach: with the gripper pointing down the arm reaches a ring about 12–25 cm from the base axis; or `tcp_offset` is wrong |
| Stays in HOLDING | The vehicle did not publish `/vehicle/arrived`, or the colour string does not match (must be lower case) |
| Block slips after lifting (Gazebo) | Increase the friction `<mu>` and lower `max_joint_speed` |

## Tests (no ROS needed)

```bash
cd mycobot_code/ros2_ws/src/mycobot_vision_grasp && python3 -m pytest test -v
cd ../mycobot_driver && python3 -m pytest test -v        # kinematics vs the arm firmware
```
