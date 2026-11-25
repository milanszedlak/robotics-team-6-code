# cobot_interfaces: vision ↔ arm ↔ vehicle interface specification + arm command API

The vision, arm and vehicle programs all share this specification. **Everyone puts this package in their own workspace**:

```bash
cp -r cobot_interfaces ~/ros2_ws/src/
cd ~/ros2_ws
colcon build --packages-select cobot_interfaces
source install/setup.bash
ros2 interface show cobot_interfaces/msg/BlockTarget
```

## 1. Vision → arm: `/vision/blocks`

| Item | Agreement |
|---|---|
| Topic | `/vision/blocks` |
| Type | `cobot_interfaces/msg/BlockTargetArray` |
| Rate | Published continuously, 5–15 Hz. **Publish an empty array when no block is seen** |
| Camera | Intel RealSense D435i, mounted at a **fixed** position (not on the arm) |
| Input images | RGB: `/camera/camera/color/image_raw`<br>Depth: `/camera/camera/aligned_depth_to_color/image_raw` |
| Frame | `camera_color_optical_frame` (x right, y down, z forward) |
| Units | Metres (raw RealSense depth is in millimetres; multiply by 0.001) |
| Timestamp | **Copy `header.stamp` from the RGB image**; do not use `now()` |
| `center` | 3D position of the centre of the block's **top face** |
| `corners` | 3D positions of the 4 corners of the top-face rotated bounding box (`cv2.minAreaRect` → `cv2.boxPoints`), in order |
| `color` | Lower case: `red` / `blue` / `green` / `yellow`; must match the basket colour |
| `should_grasp` | Vision side decides whether the block should be picked |
| `confidence` | 0–1. The arm only picks blocks with ≥ 0.5 |

The arm converts these camera coordinates to its own base frame using the camera pose in `mycobot_vision_grasp/config/camera_pose.yaml`, so the vision side does not need to know anything about the arm.

### Why `corners`?
The arm presses its two fingers against a pair of parallel edges of the block. A centre point alone does not say how the block is rotated, and an angle is easy to misinterpret (which axis is zero, which direction is positive). Four corner points cannot be misread; the arm computes the grasp direction from them.

### Example code for the vision side (rotated bounding box → message)

```python
import cv2, numpy as np
from geometry_msgs.msg import Point
from cobot_interfaces.msg import BlockTarget, BlockTargetArray

# K: `k` from /camera/camera/color/camera_info (depth is aligned to colour, so use the colour intrinsics)
def deproject(u, v, z, K):
    return Point(x=float((u - K[0, 2]) * z / K[0, 0]),
                 y=float((v - K[1, 2]) * z / K[1, 1]),
                 z=float(z))

def depth_at(depth_m, u, v, r=3):
    """Median depth around (u, v), ignoring 0 (invalid)"""
    h, w = depth_m.shape
    win = depth_m[max(v - r, 0):min(v + r + 1, h), max(u - r, 0):min(u + r + 1, w)]
    win = win[win > 0]
    return float(np.median(win)) if win.size else 0.0

def make_block(color_msg, contour, depth_raw, K, color_name, should_grasp, confidence):
    depth_m = depth_raw.astype(np.float32) * 0.001          # 16UC1 millimetres → metres
    rect = cv2.minAreaRect(contour)
    (cu, cv_), box = rect[0], cv2.boxPoints(rect)
    zc = depth_at(depth_m, int(cu), int(cv_))

    b = BlockTarget()
    b.header = color_msg.header                             # ★ RGB capture time + optical frame
    b.color = color_name
    b.should_grasp = should_grasp
    b.confidence = float(confidence)
    b.center = deproject(cu, cv_, zc, K)
    corners = []
    for (u, v) in box:
        # Depth at the edges is unreliable: sample 30% towards the centre, fall back to the centre depth
        iu, iv = int(cu + 0.7 * (u - cu)), int(cv_ + 0.7 * (v - cv_))
        z = depth_at(depth_m, iu, iv) or zc
        corners.append(deproject(u, v, z, K))
    b.corners = corners
    return b

# In the image callback:
#   out = BlockTargetArray(); out.header = color_msg.header
#   out.blocks = [make_block(...) for each detected block]
#   pub.publish(out)          # publish even when nothing is detected (empty blocks)
```

A complete, runnable implementation: `mycobot_vision_grasp/mycobot_vision_grasp/block_vision_node.py` (the team's vision node for the real D435 and for Gazebo).

### Self-check for the vision side

```bash
ros2 topic hz /vision/blocks
```

```bash
ros2 topic echo /vision/blocks --once
```

Check that:
- `header.frame_id` is `camera_color_optical_frame`
- for a block in the middle of the image, `center.x` and `center.y` are close to 0 and `center.z` equals the camera-to-top-face distance (metres)
- the distances between the 4 corners equal the block's side lengths (e.g. 0.025 and 0.06)

## 2. Arm ↔ vehicle

| Topic | Type | Publisher | Content |
|---|---|---|---|
| `/arm/state` | `std_msgs/String` | arm | `IDLE` / `PICKING` / `HOLDING` / `PLACING` / `DONE` / `ERROR` |
| `/arm/holding` | `std_msgs/String` | arm | Colour of the block being held; empty string after release |
| `/vehicle/arrived` | `std_msgs/String` | vehicle | Colour of the basket the vehicle has reached |

- The two arm topics use **transient local** QoS, so a vehicle program started later still receives the latest state.
- Sequence: arm publishes `/arm/holding = red` and `/arm/state = HOLDING` → vehicle drives to the red basket → vehicle publishes `/vehicle/arrived = red` → arm `PLACING` → releases → `DONE` → vehicle may leave.
- If the vehicle reports a colour different from the block being held, the arm **does not release**; it publishes `ERROR` once and keeps waiting.

### Simulating the vehicle by hand

```bash
ros2 topic echo /arm/holding
```

```bash
ros2 topic pub --once /vehicle/arrived std_msgs/msg/String "{data: red}"
```

## 3. Sending a fake block to the arm by hand (arm-side testing)

With the default camera pose (camera 0.60 m above the base, 0.25 m in front, looking straight down), this is a 6 × 2.5 × 2.5 cm red block on the table at base coordinates (0.25, 0, 0.025):

```bash
ros2 topic pub --once /vision/blocks cobot_interfaces/msg/BlockTargetArray "{header: {frame_id: camera_color_optical_frame}, blocks: [{header: {frame_id: camera_color_optical_frame}, color: red, should_grasp: true, confidence: 1.0, center: {x: 0.0, y: 0.0, z: 0.575}, corners: [{x: 0.03, y: 0.0125, z: 0.575}, {x: -0.03, y: 0.0125, z: 0.575}, {x: -0.03, y: -0.0125, z: 0.575}, {x: 0.03, y: -0.0125, z: 0.575}]}]}"
```

Note: the arm only accepts detections captured after it has stopped moving. Messages sent from the command line have timestamp 0 and are normally ignored; to test this way, set the arm parameter `accept_unstamped` to `true` (testing only; set it back to `false` for real runs).

## 4. Arm command API (any program → arm)

Served by `arm_task_node` (`mycobot_vision_grasp`, on the laptop / NUC) when it runs in command mode
(the default). All positions are in the arm base frame `base_link` (metres; origin on the joint-1
axis at the bottom of the base, z up).

| Name | Type | Request / goal | Response / result |
|---|---|---|---|
| `/arm/locate_blocks` | `srv/LocateBlocks` | `color` ("" = all), `go_home` | `success`, `message`, `blocks[]` (`msg/BlockInfo`: colour, confidence, graspable, top-face `position`, `grasp_yaw`, `width`) |
| `/arm/pick_block` | `action/PickBlock` | `color` ("" = best block of any colour) | `success`, `message`, `color`, `position`; feedback `stage` |
| `/arm/place_block` | `action/PlaceBlock` | `location` (`place` / `carry` / `home`) **or** `use_position: true` + `position` (gripper-centre drop point) | `success`, `message`; feedback `stage` |

```bash
ros2 service call /arm/locate_blocks cobot_interfaces/srv/LocateBlocks "{color: red, go_home: true}"
ros2 action send_goal --feedback /arm/pick_block cobot_interfaces/action/PickBlock "{color: red}"
ros2 action send_goal --feedback /arm/place_block cobot_interfaces/action/PlaceBlock "{location: place}"
```

From Python, see `ArmCommander` in `mycobot_vision_grasp/mycobot_vision_grasp/pick_place_demo.py`.
While a command runs, `/arm/state` and `/arm/holding` (section 2) are updated as in the autonomous flow.
