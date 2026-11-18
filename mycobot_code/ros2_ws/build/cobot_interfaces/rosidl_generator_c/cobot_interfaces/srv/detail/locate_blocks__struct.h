// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from cobot_interfaces:srv/LocateBlocks.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cobot_interfaces/srv/locate_blocks.h"


#ifndef COBOT_INTERFACES__SRV__DETAIL__LOCATE_BLOCKS__STRUCT_H_
#define COBOT_INTERFACES__SRV__DETAIL__LOCATE_BLOCKS__STRUCT_H_

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

/// Struct defined in srv/LocateBlocks in the package cobot_interfaces.
typedef struct cobot_interfaces__srv__LocateBlocks_Request
{
  /// only this colour; "" = all colours
  rosidl_runtime_c__String color;
  /// true = move the arm to its home pose (out of the camera view) first
  bool go_home;
} cobot_interfaces__srv__LocateBlocks_Request;

// Struct for a sequence of cobot_interfaces__srv__LocateBlocks_Request.
typedef struct cobot_interfaces__srv__LocateBlocks_Request__Sequence
{
  cobot_interfaces__srv__LocateBlocks_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cobot_interfaces__srv__LocateBlocks_Request__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"
// Member 'blocks'
#include "cobot_interfaces/msg/detail/block_info__struct.h"

/// Struct defined in srv/LocateBlocks in the package cobot_interfaces.
typedef struct cobot_interfaces__srv__LocateBlocks_Response
{
  bool success;
  rosidl_runtime_c__String message;
  /// sorted: graspable first, then by confidence
  cobot_interfaces__msg__BlockInfo__Sequence blocks;
} cobot_interfaces__srv__LocateBlocks_Response;

// Struct for a sequence of cobot_interfaces__srv__LocateBlocks_Response.
typedef struct cobot_interfaces__srv__LocateBlocks_Response__Sequence
{
  cobot_interfaces__srv__LocateBlocks_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cobot_interfaces__srv__LocateBlocks_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  cobot_interfaces__srv__LocateBlocks_Event__request__MAX_SIZE = 1
};
// response
enum
{
  cobot_interfaces__srv__LocateBlocks_Event__response__MAX_SIZE = 1
};

/// Struct defined in srv/LocateBlocks in the package cobot_interfaces.
typedef struct cobot_interfaces__srv__LocateBlocks_Event
{
  service_msgs__msg__ServiceEventInfo info;
  cobot_interfaces__srv__LocateBlocks_Request__Sequence request;
  cobot_interfaces__srv__LocateBlocks_Response__Sequence response;
} cobot_interfaces__srv__LocateBlocks_Event;

// Struct for a sequence of cobot_interfaces__srv__LocateBlocks_Event.
typedef struct cobot_interfaces__srv__LocateBlocks_Event__Sequence
{
  cobot_interfaces__srv__LocateBlocks_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cobot_interfaces__srv__LocateBlocks_Event__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // COBOT_INTERFACES__SRV__DETAIL__LOCATE_BLOCKS__STRUCT_H_
