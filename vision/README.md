# Team 6 - RealSense Object Detection

## Overview

This module detects Red, Green and Yellow blocks using
the Intel RealSense RGB-D camera.

## ROS 2 Environment

- ROS 2 Jazzy
- Python 3
- OpenCV and NumPy
- cv_bridge
- realsense2_camera
- cobot_interfaces

## Published ROS 2 Topic

Topic: /vision/blocks

Message type: cobot_interfaces/msg/BlockTargetArray

Coordinate frame: camera_color_optical_frame

Position unit: metres

## Message Fields

Each detected block contains:

- header: Image timestamp and coordinate frame
- color: red, green or yellow
- center: 3D position (x, y, z)
- corners: Four 3D corner positions
- should_grasp: Grasp readiness flag
- confidence: Detection confidence field

## Current Implementation

Red:
- Colour detection available
- 3D centre position available
- Corners currently NaN

Green:
- Colour detection available
- 3D centre position available
- Corners currently NaN

Yellow:
- Colour detection available
- 3D centre position available
- Experimental 3D top-face corner detection available

## Important Limitations

- should_grasp is currently false.
- confidence is currently 0.0 (placeholder).
- Yellow corner accuracy requires further validation.
- Empty detection arrays may occasionally occur.
- 3D positions are expressed in the camera coordinate frame.

## Integration with myCobot

The RealSense camera will be fixed to the front of LeoRover.

The robot arm must transform detected positions from
camera_color_optical_frame into its own base coordinate frame.

A calibrated TF2 transformation is required.

Before grasping, the arm controller must verify the
target position, freshness, reachability and grasp safety.

## Running

1. Source ROS 2 Jazzy.
2. Build and source the cobot_interfaces package.
3. Start the RealSense camera driver with aligned depth enabled.
4. Run the vision/object_3d_detection.py script.
5. Subscribe to /vision/blocks to receive detected targets.

## Version

RGY-perspective-size-filter-2026-11-11

Maintainer: Team 6 Vision Module
