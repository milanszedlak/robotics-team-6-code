// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from cobot_interfaces:msg/BlockInfo.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cobot_interfaces/msg/block_info.h"


#ifndef COBOT_INTERFACES__MSG__DETAIL__BLOCK_INFO__STRUCT_H_
#define COBOT_INTERFACES__MSG__DETAIL__BLOCK_INFO__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Constants defined in the message

// Include directives for member types
// Member 'color'
#include "rosidl_runtime_c/string.h"
// Member 'position'
#include "geometry_msgs/msg/detail/point__struct.h"

/// Struct defined in msg/BlockInfo in the package cobot_interfaces.
/**
  * One block as seen by the arm, already converted to the arm base frame (base_link).
  * Returned by the /arm/locate_blocks service.
 */
typedef struct cobot_interfaces__msg__BlockInfo
{
  /// lower-case colour name ("red", "blue", ...)
  rosidl_runtime_c__String color;
  /// 0.0 ~ 1.0, from the vision node
  float confidence;
  /// vision says pick it, confidence is high enough, and it fits the gripper
  bool graspable;
  /// centre of the block's TOP face in base_link
  geometry_msgs__msg__Point position;
  /// finger closing direction in the base XY plane (0 if no corners)
  double grasp_yaw;
  /// block width across the fingers (0 if no corners)
  double width;
} cobot_interfaces__msg__BlockInfo;

// Struct for a sequence of cobot_interfaces__msg__BlockInfo.
typedef struct cobot_interfaces__msg__BlockInfo__Sequence
{
  cobot_interfaces__msg__BlockInfo * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cobot_interfaces__msg__BlockInfo__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // COBOT_INTERFACES__MSG__DETAIL__BLOCK_INFO__STRUCT_H_
