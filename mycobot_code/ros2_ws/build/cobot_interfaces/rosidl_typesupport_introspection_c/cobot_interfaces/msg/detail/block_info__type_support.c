// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from cobot_interfaces:msg/BlockInfo.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "cobot_interfaces/msg/detail/block_info__rosidl_typesupport_introspection_c.h"
#include "cobot_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "cobot_interfaces/msg/detail/block_info__functions.h"
#include "cobot_interfaces/msg/detail/block_info__struct.h"


// Include directives for member types
// Member `color`
#include "rosidl_runtime_c/string_functions.h"
// Member `position`
#include "geometry_msgs/msg/point.h"
// Member `position`
#include "geometry_msgs/msg/detail/point__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void cobot_interfaces__msg__BlockInfo__rosidl_typesupport_introspection_c__BlockInfo_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  cobot_interfaces__msg__BlockInfo__init(message_memory);
}

void cobot_interfaces__msg__BlockInfo__rosidl_typesupport_introspection_c__BlockInfo_fini_function(void * message_memory)
{
  cobot_interfaces__msg__BlockInfo__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember cobot_interfaces__msg__BlockInfo__rosidl_typesupport_introspection_c__BlockInfo_message_member_array[6] = {
  {
    "color",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot_interfaces__msg__BlockInfo, color),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "confidence",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot_interfaces__msg__BlockInfo, confidence),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "graspable",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot_interfaces__msg__BlockInfo, graspable),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "position",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot_interfaces__msg__BlockInfo, position),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "grasp_yaw",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot_interfaces__msg__BlockInfo, grasp_yaw),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "width",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_DOUBLE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot_interfaces__msg__BlockInfo, width),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers cobot_interfaces__msg__BlockInfo__rosidl_typesupport_introspection_c__BlockInfo_message_members = {
  "cobot_interfaces__msg",  // message namespace
  "BlockInfo",  // message name
  6,  // number of fields
  sizeof(cobot_interfaces__msg__BlockInfo),
  false,  // has_any_key_member_
  cobot_interfaces__msg__BlockInfo__rosidl_typesupport_introspection_c__BlockInfo_message_member_array,  // message members
  cobot_interfaces__msg__BlockInfo__rosidl_typesupport_introspection_c__BlockInfo_init_function,  // function to initialize message memory (memory has to be allocated)
  cobot_interfaces__msg__BlockInfo__rosidl_typesupport_introspection_c__BlockInfo_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t cobot_interfaces__msg__BlockInfo__rosidl_typesupport_introspection_c__BlockInfo_message_type_support_handle = {
  0,
  &cobot_interfaces__msg__BlockInfo__rosidl_typesupport_introspection_c__BlockInfo_message_members,
  get_message_typesupport_handle_function,
  &cobot_interfaces__msg__BlockInfo__get_type_hash,
  &cobot_interfaces__msg__BlockInfo__get_type_description,
  &cobot_interfaces__msg__BlockInfo__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_cobot_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot_interfaces, msg, BlockInfo)() {
  cobot_interfaces__msg__BlockInfo__rosidl_typesupport_introspection_c__BlockInfo_message_member_array[3].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Point)();
  if (!cobot_interfaces__msg__BlockInfo__rosidl_typesupport_introspection_c__BlockInfo_message_type_support_handle.typesupport_identifier) {
    cobot_interfaces__msg__BlockInfo__rosidl_typesupport_introspection_c__BlockInfo_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &cobot_interfaces__msg__BlockInfo__rosidl_typesupport_introspection_c__BlockInfo_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
