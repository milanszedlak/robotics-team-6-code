# Team 6 Vision (ROS 2 Jazzy)

An `ament_python` ROS 2 package built from the team's tested vision scripts.
The detection algorithms and message definitions are not modified by packaging.

- `object_detection`: detects red, green and yellow blocks; publishes
  `/vision/blocks` (`cobot_interfaces/msg/BlockTargetArray`).
- `bin_detection`: two-stage red/green/yellow bin body and opening detection;
  publishes **experimental** `/vision/bins/debug_json` and debug points.

Both detectors subscribe to the RealSense D435i RGB image and aligned depth
and use RELIABLE image QoS on the Team 6 NUC.

## Build in a ROS 2 workspace

Place or link this **package directory** under a colcon workspace `src/` and
ensure `cobot_interfaces` is also available (exactly one copy per workspace):

```bash
source /opt/ros/jazzy/setup.bash
cd ~/ros2_ws
colcon build --packages-select team6_vision --symlink-install
source install/setup.bash
```

## Start RealSense in terminal 1

```bash
source /opt/ros/jazzy/setup.bash
source ~/ros2_ws/install/setup.bash
ros2 launch realsense2_camera rs_launch.py \
  enable_color:=true enable_depth:=true \
  rgb_camera.color_profile:=640x480x15 \
  depth_module.depth_profile:=640x480x15 \
  align_depth.enable:=true enable_sync:=true
```

## Run the detection nodes in separate terminals

```bash
source /opt/ros/jazzy/setup.bash
source ~/ros2_ws/install/setup.bash
ros2 run team6_vision object_detection
```

```bash
source /opt/ros/jazzy/setup.bash
source ~/ros2_ws/install/setup.bash
ros2 run team6_vision bin_detection --max-fps 15
```

## Integration notes

The visual detections are in `camera_color_optical_frame` (metres), not the
arm base frame. TF2 calibration is needed for grasping and placing. The
`/vision/blocks` `should_grasp` and `confidence` fields are still placeholders;
red/green corner fields are currently NaN. Do not use these as autonomous
pick permission without an explicit arm/vision integration decision.
Bin debug-point estimates are not verified drop poses.

The ROS package metadata currently contains placeholder maintainer email and
license fields. Set these to the group's agreed values before public release.


## Arm integration (RGY, 2026-11-18)

The real robot uses `team6_vision object_detection` as the *only* publisher of
`/vision/blocks`. The `enable_grasp_candidates` ROS parameter defaults to
`false`, to prevent accidental arm movement before external calibration.

When disabled, valid RGB-D block candidates are published with nonzero,
heuristic depth-support quality scores but `should_grasp=false`. Arm selection
therefore deliberately rejects them. When the operator explicitly enables the
parameter after validating the physical grasp and camera→arm TF, candidates
that pass the HSV, depth and size filters may be marked `should_grasp=true`.
This does NOT guarantee their centres are grasp-ready top-face centres:
red/green remain provisional, and the yellow top-plane is preliminary.

Missing corners use four zero Points in the shared `cobot_interfaces` message;
yellow may provide four measured three-dimensional top corners.
