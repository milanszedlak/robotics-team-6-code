// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from cobot_interfaces:msg/BlockTargetArray.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "cobot_interfaces/msg/detail/block_target_array__rosidl_typesupport_introspection_c.h"
#include "cobot_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "cobot_interfaces/msg/detail/block_target_array__functions.h"
#include "cobot_interfaces/msg/detail/block_target_array__struct.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/header.h"
// Member `header`
#include "std_msgs/msg/detail/header__rosidl_typesupport_introspection_c.h"
// Member `blocks`
#include "cobot_interfaces/msg/block_target.h"
// Member `blocks`
#include "cobot_interfaces/msg/detail/block_target__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void cobot_interfaces__msg__BlockTargetArray__rosidl_typesupport_introspection_c__BlockTargetArray_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  cobot_interfaces__msg__BlockTargetArray__init(message_memory);
}

void cobot_interfaces__msg__BlockTargetArray__rosidl_typesupport_introspection_c__BlockTargetArray_fini_function(void * message_memory)
{
  cobot_interfaces__msg__BlockTargetArray__fini(message_memory);
}

size_t cobot_interfaces__msg__BlockTargetArray__rosidl_typesupport_introspection_c__size_function__BlockTargetArray__blocks(
  const void * untyped_member)
{
  const cobot_interfaces__msg__BlockTarget__Sequence * member =
    (const cobot_interfaces__msg__BlockTarget__Sequence *)(untyped_member);
  return member->size;
}

const void * cobot_interfaces__msg__BlockTargetArray__rosidl_typesupport_introspection_c__get_const_function__BlockTargetArray__blocks(
  const void * untyped_member, size_t index)
{
  const cobot_interfaces__msg__BlockTarget__Sequence * member =
    (const cobot_interfaces__msg__BlockTarget__Sequence *)(untyped_member);
  return &member->data[index];
}

void * cobot_interfaces__msg__BlockTargetArray__rosidl_typesupport_introspection_c__get_function__BlockTargetArray__blocks(
  void * untyped_member, size_t index)
{
  cobot_interfaces__msg__BlockTarget__Sequence * member =
    (cobot_interfaces__msg__BlockTarget__Sequence *)(untyped_member);
  return &member->data[index];
}

void cobot_interfaces__msg__BlockTargetArray__rosidl_typesupport_introspection_c__fetch_function__BlockTargetArray__blocks(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const cobot_interfaces__msg__BlockTarget * item =
    ((const cobot_interfaces__msg__BlockTarget *)
    cobot_interfaces__msg__BlockTargetArray__rosidl_typesupport_introspection_c__get_const_function__BlockTargetArray__blocks(untyped_member, index));
  cobot_interfaces__msg__BlockTarget * value =
    (cobot_interfaces__msg__BlockTarget *)(untyped_value);
  *value = *item;
}

void cobot_interfaces__msg__BlockTargetArray__rosidl_typesupport_introspection_c__assign_function__BlockTargetArray__blocks(
  void * untyped_member, size_t index, const void * untyped_value)
{
  cobot_interfaces__msg__BlockTarget * item =
    ((cobot_interfaces__msg__BlockTarget *)
    cobot_interfaces__msg__BlockTargetArray__rosidl_typesupport_introspection_c__get_function__BlockTargetArray__blocks(untyped_member, index));
  const cobot_interfaces__msg__BlockTarget * value =
    (const cobot_interfaces__msg__BlockTarget *)(untyped_value);
  *item = *value;
}

bool cobot_interfaces__msg__BlockTargetArray__rosidl_typesupport_introspection_c__resize_function__BlockTargetArray__blocks(
  void * untyped_member, size_t size)
{
  cobot_interfaces__msg__BlockTarget__Sequence * member =
    (cobot_interfaces__msg__BlockTarget__Sequence *)(untyped_member);
  cobot_interfaces__msg__BlockTarget__Sequence__fini(member);
  return cobot_interfaces__msg__BlockTarget__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember cobot_interfaces__msg__BlockTargetArray__rosidl_typesupport_introspection_c__BlockTargetArray_message_member_array[2] = {
  {
    "header",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot_interfaces__msg__BlockTargetArray, header),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "blocks",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot_interfaces__msg__BlockTargetArray, blocks),  // bytes offset in struct
    NULL,  // default value
    cobot_interfaces__msg__BlockTargetArray__rosidl_typesupport_introspection_c__size_function__BlockTargetArray__blocks,  // size() function pointer
    cobot_interfaces__msg__BlockTargetArray__rosidl_typesupport_introspection_c__get_const_function__BlockTargetArray__blocks,  // get_const(index) function pointer
    cobot_interfaces__msg__BlockTargetArray__rosidl_typesupport_introspection_c__get_function__BlockTargetArray__blocks,  // get(index) function pointer
    cobot_interfaces__msg__BlockTargetArray__rosidl_typesupport_introspection_c__fetch_function__BlockTargetArray__blocks,  // fetch(index, &value) function pointer
    cobot_interfaces__msg__BlockTargetArray__rosidl_typesupport_introspection_c__assign_function__BlockTargetArray__blocks,  // assign(index, value) function pointer
    cobot_interfaces__msg__BlockTargetArray__rosidl_typesupport_introspection_c__resize_function__BlockTargetArray__blocks  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers cobot_interfaces__msg__BlockTargetArray__rosidl_typesupport_introspection_c__BlockTargetArray_message_members = {
  "cobot_interfaces__msg",  // message namespace
  "BlockTargetArray",  // message name
  2,  // number of fields
  sizeof(cobot_interfaces__msg__BlockTargetArray),
  false,  // has_any_key_member_
  cobot_interfaces__msg__BlockTargetArray__rosidl_typesupport_introspection_c__BlockTargetArray_message_member_array,  // message members
  cobot_interfaces__msg__BlockTargetArray__rosidl_typesupport_introspection_c__BlockTargetArray_init_function,  // function to initialize message memory (memory has to be allocated)
  cobot_interfaces__msg__BlockTargetArray__rosidl_typesupport_introspection_c__BlockTargetArray_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t cobot_interfaces__msg__BlockTargetArray__rosidl_typesupport_introspection_c__BlockTargetArray_message_type_support_handle = {
  0,
  &cobot_interfaces__msg__BlockTargetArray__rosidl_typesupport_introspection_c__BlockTargetArray_message_members,
  get_message_typesupport_handle_function,
  &cobot_interfaces__msg__BlockTargetArray__get_type_hash,
  &cobot_interfaces__msg__BlockTargetArray__get_type_description,
  &cobot_interfaces__msg__BlockTargetArray__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_cobot_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot_interfaces, msg, BlockTargetArray)() {
  cobot_interfaces__msg__BlockTargetArray__rosidl_typesupport_introspection_c__BlockTargetArray_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, std_msgs, msg, Header)();
  cobot_interfaces__msg__BlockTargetArray__rosidl_typesupport_introspection_c__BlockTargetArray_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot_interfaces, msg, BlockTarget)();
  if (!cobot_interfaces__msg__BlockTargetArray__rosidl_typesupport_introspection_c__BlockTargetArray_message_type_support_handle.typesupport_identifier) {
    cobot_interfaces__msg__BlockTargetArray__rosidl_typesupport_introspection_c__BlockTargetArray_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &cobot_interfaces__msg__BlockTargetArray__rosidl_typesupport_introspection_c__BlockTargetArray_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
