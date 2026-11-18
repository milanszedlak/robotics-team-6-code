// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from cobot_interfaces:msg/BlockTarget.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "cobot_interfaces/msg/detail/block_target__rosidl_typesupport_introspection_c.h"
#include "cobot_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "cobot_interfaces/msg/detail/block_target__functions.h"
#include "cobot_interfaces/msg/detail/block_target__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `color`
#include "rosidl_runtime_c/string_functions.h"
// Member `center`
// Member `corners`
#include "geometry_msgs/msg/point.h"
// Member `center`
// Member `corners`
#include "geometry_msgs/msg/detail/point__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void cobot_interfaces__msg__BlockTarget__rosidl_typesupport_introspection_c__BlockTarget_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  cobot_interfaces__msg__BlockTarget__init(message_memory);
}

void cobot_interfaces__msg__BlockTarget__rosidl_typesupport_introspection_c__BlockTarget_fini_function(void * message_memory)
{
  cobot_interfaces__msg__BlockTarget__fini(message_memory);
}

size_t cobot_interfaces__msg__BlockTarget__rosidl_typesupport_introspection_c__size_function__BlockTarget__corners(
  const void * untyped_member)
{
  (void)untyped_member;
  return 4;
}

const void * cobot_interfaces__msg__BlockTarget__rosidl_typesupport_introspection_c__get_const_function__BlockTarget__corners(
  const void * untyped_member, size_t index)
{
  const geometry_msgs__msg__Point * member =
    (const geometry_msgs__msg__Point *)(untyped_member);
  return &member[index];
}

void * cobot_interfaces__msg__BlockTarget__rosidl_typesupport_introspection_c__get_function__BlockTarget__corners(
  void * untyped_member, size_t index)
{
  geometry_msgs__msg__Point * member =
    (geometry_msgs__msg__Point *)(untyped_member);
  return &member[index];
}

void cobot_interfaces__msg__BlockTarget__rosidl_typesupport_introspection_c__fetch_function__BlockTarget__corners(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const geometry_msgs__msg__Point * item =
    ((const geometry_msgs__msg__Point *)
    cobot_interfaces__msg__BlockTarget__rosidl_typesupport_introspection_c__get_const_function__BlockTarget__corners(untyped_member, index));
  geometry_msgs__msg__Point * value =
    (geometry_msgs__msg__Point *)(untyped_value);
  *value = *item;
}

void cobot_interfaces__msg__BlockTarget__rosidl_typesupport_introspection_c__assign_function__BlockTarget__corners(
  void * untyped_member, size_t index, const void * untyped_value)
{
  geometry_msgs__msg__Point * item =
    ((geometry_msgs__msg__Point *)
    cobot_interfaces__msg__BlockTarget__rosidl_typesupport_introspection_c__get_function__BlockTarget__corners(untyped_member, index));
  const geometry_msgs__msg__Point * value =
    (const geometry_msgs__msg__Point *)(untyped_value);
  *item = *value;
}

static rosidl_typesupport_introspection_c__MessageMember cobot_interfaces__msg__BlockTarget__rosidl_typesupport_introspection_c__BlockTarget_message_member_array[6] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot_interfaces__msg__BlockTarget, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "color",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot_interfaces__msg__BlockTarget, color),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "should_grasp",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot_interfaces__msg__BlockTarget, should_grasp),  // bytes offset in struct
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
    offsetof(cobot_interfaces__msg__BlockTarget, confidence),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "center",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot_interfaces__msg__BlockTarget, center),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "corners",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    4,  // array size
    false,  // is upper bound
    offsetof(cobot_interfaces__msg__BlockTarget, corners),  // bytes offset in struct
    NULL,  // default value
    cobot_interfaces__msg__BlockTarget__rosidl_typesupport_introspection_c__size_function__BlockTarget__corners,  // size() function pointer
    cobot_interfaces__msg__BlockTarget__rosidl_typesupport_introspection_c__get_const_function__BlockTarget__corners,  // get_const(index) function pointer
    cobot_interfaces__msg__BlockTarget__rosidl_typesupport_introspection_c__get_function__BlockTarget__corners,  // get(index) function pointer
    cobot_interfaces__msg__BlockTarget__rosidl_typesupport_introspection_c__fetch_function__BlockTarget__corners,  // fetch(index, &value) function pointer
    cobot_interfaces__msg__BlockTarget__rosidl_typesupport_introspection_c__assign_function__BlockTarget__corners,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers cobot_interfaces__msg__BlockTarget__rosidl_typesupport_introspection_c__BlockTarget_message_members = {
  "cobot_interfaces__msg",  // message namespace
  "BlockTarget",  // message name
  6,  // number of fields
  sizeof(cobot_interfaces__msg__BlockTarget),
  false,  // has_any_key_member_
  cobot_interfaces__msg__BlockTarget__rosidl_typesupport_introspection_c__BlockTarget_message_member_array,  // message members
  cobot_interfaces__msg__BlockTarget__rosidl_typesupport_introspection_c__BlockTarget_init_function,  // function to initialize message memory (memory has to be allocated)
  cobot_interfaces__msg__BlockTarget__rosidl_typesupport_introspection_c__BlockTarget_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t cobot_interfaces__msg__BlockTarget__rosidl_typesupport_introspection_c__BlockTarget_message_type_support_handle = {
  0,
  &cobot_interfaces__msg__BlockTarget__rosidl_typesupport_introspection_c__BlockTarget_message_members,
  get_message_typesupport_handle_function,
  &cobot_interfaces__msg__BlockTarget__get_type_hash,
  &cobot_interfaces__msg__BlockTarget__get_type_description,
  &cobot_interfaces__msg__BlockTarget__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_cobot_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot_interfaces, msg, BlockTarget)() {
  cobot_interfaces__msg__BlockTarget__rosidl_typesupport_introspection_c__BlockTarget_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  cobot_interfaces__msg__BlockTarget__rosidl_typesupport_introspection_c__BlockTarget_message_member_array[4].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Point)();
  cobot_interfaces__msg__BlockTarget__rosidl_typesupport_introspection_c__BlockTarget_message_member_array[5].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, geometry_msgs, msg, Point)();
  if (!cobot_interfaces__msg__BlockTarget__rosidl_typesupport_introspection_c__BlockTarget_message_type_support_handle.typesupport_identifier) {
    cobot_interfaces__msg__BlockTarget__rosidl_typesupport_introspection_c__BlockTarget_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &cobot_interfaces__msg__BlockTarget__rosidl_typesupport_introspection_c__BlockTarget_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
