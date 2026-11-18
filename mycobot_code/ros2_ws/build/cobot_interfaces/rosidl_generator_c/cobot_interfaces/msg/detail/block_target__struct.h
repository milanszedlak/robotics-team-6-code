// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from cobot_interfaces:msg/BlockTarget.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cobot_interfaces/msg/block_target.h"


#ifndef COBOT_INTERFACES__MSG__DETAIL__BLOCK_TARGET__STRUCT_H_
#define COBOT_INTERFACES__MSG__DETAIL__BLOCK_TARGET__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'color'
#include "rosidl_runtime_c/string.h"
// Member 'center'
// Member 'corners'
#include "geometry_msgs/msg/detail/point__struct.h"

/// Struct defined in msg/BlockTarget in the package cobot_interfaces.
/**
  * One block detected by the camera (published by the vision node, consumed by the arm node)
  *
  * Frame:     header.frame_id must be the camera optical frame, e.g. camera_color_optical_frame
  *            (x right, y down, z forward; units: metres)
  * Timestamp: header.stamp must be the capture time of the RGB image
  *            (copy header.stamp from the colour image)
 */
typedef struct cobot_interfaces__msg__BlockTarget
{
  std_msgs__msg__Header header;
  /// lower-case colour name: "red" / "blue" / "green" / "yellow" ... (matches the basket colour)
  rosidl_runtime_c__String color;
  /// vision node decides whether this block should be picked
  bool should_grasp;
  /// 0.0 ~ 1.0
  float confidence;
  /// centre of the block's TOP face
  geometry_msgs__msg__Point center;
  /// the 4 corners of the top-face rotated bounding box, in order
  /// (the order returned by cv2.boxPoints is fine)
  /// If not available, set all 4 to 0; the arm keeps its current gripper angle
  geometry_msgs__msg__Point corners[4];
} cobot_interfaces__msg__BlockTarget;

// Struct for a sequence of cobot_interfaces__msg__BlockTarget.
typedef struct cobot_interfaces__msg__BlockTarget__Sequence
{
  cobot_interfaces__msg__BlockTarget * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cobot_interfaces__msg__BlockTarget__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // COBOT_INTERFACES__MSG__DETAIL__BLOCK_TARGET__STRUCT_H_
