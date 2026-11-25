# Team 6 vision + myCobot integration (ROS 2 Jazzy)

The integration branch imports these three packages from `elephant-arm-code`:
- `mycobot_driver` – physical robot driver (arm Pi)
- `mycobot_vision_grasp` – grasp controller, TF and Actions (NUC)
- `cobot_interfaces` – shared messages and Actions, now a **single** package

The original, tested vision algorithms from `feature/vision-rgy` remain in
`vision/team6_vision`, a standard `ament_python` ROS 2 package:
- `ros2 run team6_vision object_detection` – publishes `/vision/blocks`
- `ros2 run team6_vision bin_detection --max-fps 15` – experimental bin detector

## Package layout

The authoritative `cobot_interfaces` is in `/cobot_interfaces` at repository
root. The arm workspace contains **relative symlinks** to that package and to
`vision/team6_vision`, so `colcon` can resolve both in one workspace. Do not
create an additional real copy of `cobot_interfaces` anywhere in a workspace.

## Commands (NUC)

```bash
source /opt/ros/jazzy/setup.bash
cd ~/robotics-team-6-code/mycobot_code/ros2_ws
colcon build --packages-select cobot_interfaces team6_vision mycobot_driver mycobot_vision_grasp --symlink-install
source install/setup.bash
ros2 launch mycobot_vision_grasp real_robot.launch.py camera:=false autorun:=false
```

On a shared network the arm driver runs separately on the robot Pi. Start the
RealSense separately with `enable_sync:=true` when `camera:=false`.

`real_robot.launch.py` starts `team6_vision object_detection` by default. If
already running externally, pass `vision:=false`. Do NOT start the arm team's
old `block_vision_node` simultaneously on the real robot.

## Safety

`enable_grasp_candidates:=false` by default; this makes `should_grasp=false`.
Opting in requires **physical** verification of TF extrinsics, TCP offset,
block top-face geometry, inverse kinematics, limits, collision clearance and
an accessible emergency stop. The RGB-D quality score is not a verified grasp
pose. Red/green corner geometry is unavailable; the arm keeps its wrist angle.
Bin detection is for visual debugging, not verified autonomous dropping.
