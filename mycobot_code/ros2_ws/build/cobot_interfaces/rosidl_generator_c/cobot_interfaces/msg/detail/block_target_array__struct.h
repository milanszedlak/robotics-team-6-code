// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from cobot_interfaces:msg/BlockTargetArray.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cobot_interfaces/msg/block_target_array.h"


#ifndef COBOT_INTERFACES__MSG__DETAIL__BLOCK_TARGET_ARRAY__STRUCT_H_
#define COBOT_INTERFACES__MSG__DETAIL__BLOCK_TARGET_ARRAY__STRUCT_H_

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
// Member 'blocks'
#include "cobot_interfaces/msg/detail/block_target__struct.h"

/// Struct defined in msg/BlockTargetArray in the package cobot_interfaces.
/**
  * All blocks detected in one image. Publish it even when no block is seen (empty `blocks`).
  * The header matches the RGB image (stamp = capture time, frame_id = camera optical frame)
 */
typedef struct cobot_interfaces__msg__BlockTargetArray
{
  std_msgs__msg__Header header;
  cobot_interfaces__msg__BlockTarget__Sequence blocks;
} cobot_interfaces__msg__BlockTargetArray;

// Struct for a sequence of cobot_interfaces__msg__BlockTargetArray.
typedef struct cobot_interfaces__msg__BlockTargetArray__Sequence
{
  cobot_interfaces__msg__BlockTargetArray * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cobot_interfaces__msg__BlockTargetArray__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // COBOT_INTERFACES__MSG__DETAIL__BLOCK_TARGET_ARRAY__STRUCT_H_
