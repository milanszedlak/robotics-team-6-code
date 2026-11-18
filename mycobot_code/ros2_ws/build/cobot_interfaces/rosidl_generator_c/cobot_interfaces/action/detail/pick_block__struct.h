// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from cobot_interfaces:action/PickBlock.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cobot_interfaces/action/pick_block.h"


#ifndef COBOT_INTERFACES__ACTION__DETAIL__PICK_BLOCK__STRUCT_H_
#define COBOT_INTERFACES__ACTION__DETAIL__PICK_BLOCK__STRUCT_H_

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

/// Struct defined in action/PickBlock in the package cobot_interfaces.
typedef struct cobot_interfaces__action__PickBlock_Goal
{
  /// colour to pick; "" = the best graspable block of any colour
  rosidl_runtime_c__String color;
} cobot_interfaces__action__PickBlock_Goal;

// Struct for a sequence of cobot_interfaces__action__PickBlock_Goal.
typedef struct cobot_interfaces__action__PickBlock_Goal__Sequence
{
  cobot_interfaces__action__PickBlock_Goal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cobot_interfaces__action__PickBlock_Goal__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'message'
// Member 'color'
// already included above
// #include "rosidl_runtime_c/string.h"
// Member 'position'
#include "geometry_msgs/msg/detail/point__struct.h"

/// Struct defined in action/PickBlock in the package cobot_interfaces.
typedef struct cobot_interfaces__action__PickBlock_Result
{
  bool success;
  rosidl_runtime_c__String message;
  /// colour actually picked
  rosidl_runtime_c__String color;
  /// where it was picked (top-face centre, base_link)
  geometry_msgs__msg__Point position;
} cobot_interfaces__action__PickBlock_Result;

// Struct for a sequence of cobot_interfaces__action__PickBlock_Result.
typedef struct cobot_interfaces__action__PickBlock_Result__Sequence
{
  cobot_interfaces__action__PickBlock_Result * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cobot_interfaces__action__PickBlock_Result__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'stage'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in action/PickBlock in the package cobot_interfaces.
typedef struct cobot_interfaces__action__PickBlock_Feedback
{
  /// e.g. "locating", "approaching", "descending", "grasping", "lifting"
  rosidl_runtime_c__String stage;
} cobot_interfaces__action__PickBlock_Feedback;

// Struct for a sequence of cobot_interfaces__action__PickBlock_Feedback.
typedef struct cobot_interfaces__action__PickBlock_Feedback__Sequence
{
  cobot_interfaces__action__PickBlock_Feedback * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cobot_interfaces__action__PickBlock_Feedback__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
#include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'goal'
#include "cobot_interfaces/action/detail/pick_block__struct.h"

/// Struct defined in action/PickBlock in the package cobot_interfaces.
typedef struct cobot_interfaces__action__PickBlock_SendGoal_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
  cobot_interfaces__action__PickBlock_Goal goal;
} cobot_interfaces__action__PickBlock_SendGoal_Request;

// Struct for a sequence of cobot_interfaces__action__PickBlock_SendGoal_Request.
typedef struct cobot_interfaces__action__PickBlock_SendGoal_Request__Sequence
{
  cobot_interfaces__action__PickBlock_SendGoal_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cobot_interfaces__action__PickBlock_SendGoal_Request__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'stamp'
#include "builtin_interfaces/msg/detail/time__struct.h"

/// Struct defined in action/PickBlock in the package cobot_interfaces.
typedef struct cobot_interfaces__action__PickBlock_SendGoal_Response
{
  bool accepted;
  builtin_interfaces__msg__Time stamp;
} cobot_interfaces__action__PickBlock_SendGoal_Response;

// Struct for a sequence of cobot_interfaces__action__PickBlock_SendGoal_Response.
typedef struct cobot_interfaces__action__PickBlock_SendGoal_Response__Sequence
{
  cobot_interfaces__action__PickBlock_SendGoal_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cobot_interfaces__action__PickBlock_SendGoal_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  cobot_interfaces__action__PickBlock_SendGoal_Event__request__MAX_SIZE = 1
};
// response
enum
{
  cobot_interfaces__action__PickBlock_SendGoal_Event__response__MAX_SIZE = 1
};

/// Struct defined in action/PickBlock in the package cobot_interfaces.
typedef struct cobot_interfaces__action__PickBlock_SendGoal_Event
{
  service_msgs__msg__ServiceEventInfo info;
  cobot_interfaces__action__PickBlock_SendGoal_Request__Sequence request;
  cobot_interfaces__action__PickBlock_SendGoal_Response__Sequence response;
} cobot_interfaces__action__PickBlock_SendGoal_Event;

// Struct for a sequence of cobot_interfaces__action__PickBlock_SendGoal_Event.
typedef struct cobot_interfaces__action__PickBlock_SendGoal_Event__Sequence
{
  cobot_interfaces__action__PickBlock_SendGoal_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cobot_interfaces__action__PickBlock_SendGoal_Event__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"

/// Struct defined in action/PickBlock in the package cobot_interfaces.
typedef struct cobot_interfaces__action__PickBlock_GetResult_Request
{
  unique_identifier_msgs__msg__UUID goal_id;
} cobot_interfaces__action__PickBlock_GetResult_Request;

// Struct for a sequence of cobot_interfaces__action__PickBlock_GetResult_Request.
typedef struct cobot_interfaces__action__PickBlock_GetResult_Request__Sequence
{
  cobot_interfaces__action__PickBlock_GetResult_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cobot_interfaces__action__PickBlock_GetResult_Request__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'result'
// already included above
// #include "cobot_interfaces/action/detail/pick_block__struct.h"

/// Struct defined in action/PickBlock in the package cobot_interfaces.
typedef struct cobot_interfaces__action__PickBlock_GetResult_Response
{
  int8_t status;
  cobot_interfaces__action__PickBlock_Result result;
} cobot_interfaces__action__PickBlock_GetResult_Response;

// Struct for a sequence of cobot_interfaces__action__PickBlock_GetResult_Response.
typedef struct cobot_interfaces__action__PickBlock_GetResult_Response__Sequence
{
  cobot_interfaces__action__PickBlock_GetResult_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cobot_interfaces__action__PickBlock_GetResult_Response__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'info'
// already included above
// #include "service_msgs/msg/detail/service_event_info__struct.h"

// constants for array fields with an upper bound
// request
enum
{
  cobot_interfaces__action__PickBlock_GetResult_Event__request__MAX_SIZE = 1
};
// response
enum
{
  cobot_interfaces__action__PickBlock_GetResult_Event__response__MAX_SIZE = 1
};

/// Struct defined in action/PickBlock in the package cobot_interfaces.
typedef struct cobot_interfaces__action__PickBlock_GetResult_Event
{
  service_msgs__msg__ServiceEventInfo info;
  cobot_interfaces__action__PickBlock_GetResult_Request__Sequence request;
  cobot_interfaces__action__PickBlock_GetResult_Response__Sequence response;
} cobot_interfaces__action__PickBlock_GetResult_Event;

// Struct for a sequence of cobot_interfaces__action__PickBlock_GetResult_Event.
typedef struct cobot_interfaces__action__PickBlock_GetResult_Event__Sequence
{
  cobot_interfaces__action__PickBlock_GetResult_Event * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cobot_interfaces__action__PickBlock_GetResult_Event__Sequence;

// Constants defined in the message

// Include directives for member types
// Member 'goal_id'
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__struct.h"
// Member 'feedback'
// already included above
// #include "cobot_interfaces/action/detail/pick_block__struct.h"

/// Struct defined in action/PickBlock in the package cobot_interfaces.
typedef struct cobot_interfaces__action__PickBlock_FeedbackMessage
{
  unique_identifier_msgs__msg__UUID goal_id;
  cobot_interfaces__action__PickBlock_Feedback feedback;
} cobot_interfaces__action__PickBlock_FeedbackMessage;

// Struct for a sequence of cobot_interfaces__action__PickBlock_FeedbackMessage.
typedef struct cobot_interfaces__action__PickBlock_FeedbackMessage__Sequence
{
  cobot_interfaces__action__PickBlock_FeedbackMessage * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} cobot_interfaces__action__PickBlock_FeedbackMessage__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // COBOT_INTERFACES__ACTION__DETAIL__PICK_BLOCK__STRUCT_H_
