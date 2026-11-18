// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from cobot_interfaces:srv/LocateBlocks.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "cobot_interfaces/srv/detail/locate_blocks__rosidl_typesupport_introspection_c.h"
#include "cobot_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "cobot_interfaces/srv/detail/locate_blocks__functions.h"
#include "cobot_interfaces/srv/detail/locate_blocks__struct.h"


// Include directives for member types
// Member `color`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void cobot_interfaces__srv__LocateBlocks_Request__rosidl_typesupport_introspection_c__LocateBlocks_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  cobot_interfaces__srv__LocateBlocks_Request__init(message_memory);
}

void cobot_interfaces__srv__LocateBlocks_Request__rosidl_typesupport_introspection_c__LocateBlocks_Request_fini_function(void * message_memory)
{
  cobot_interfaces__srv__LocateBlocks_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember cobot_interfaces__srv__LocateBlocks_Request__rosidl_typesupport_introspection_c__LocateBlocks_Request_message_member_array[2] = {
  {
    "color",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot_interfaces__srv__LocateBlocks_Request, color),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "go_home",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot_interfaces__srv__LocateBlocks_Request, go_home),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers cobot_interfaces__srv__LocateBlocks_Request__rosidl_typesupport_introspection_c__LocateBlocks_Request_message_members = {
  "cobot_interfaces__srv",  // message namespace
  "LocateBlocks_Request",  // message name
  2,  // number of fields
  sizeof(cobot_interfaces__srv__LocateBlocks_Request),
  false,  // has_any_key_member_
  cobot_interfaces__srv__LocateBlocks_Request__rosidl_typesupport_introspection_c__LocateBlocks_Request_message_member_array,  // message members
  cobot_interfaces__srv__LocateBlocks_Request__rosidl_typesupport_introspection_c__LocateBlocks_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  cobot_interfaces__srv__LocateBlocks_Request__rosidl_typesupport_introspection_c__LocateBlocks_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t cobot_interfaces__srv__LocateBlocks_Request__rosidl_typesupport_introspection_c__LocateBlocks_Request_message_type_support_handle = {
  0,
  &cobot_interfaces__srv__LocateBlocks_Request__rosidl_typesupport_introspection_c__LocateBlocks_Request_message_members,
  get_message_typesupport_handle_function,
  &cobot_interfaces__srv__LocateBlocks_Request__get_type_hash,
  &cobot_interfaces__srv__LocateBlocks_Request__get_type_description,
  &cobot_interfaces__srv__LocateBlocks_Request__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_cobot_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot_interfaces, srv, LocateBlocks_Request)() {
  if (!cobot_interfaces__srv__LocateBlocks_Request__rosidl_typesupport_introspection_c__LocateBlocks_Request_message_type_support_handle.typesupport_identifier) {
    cobot_interfaces__srv__LocateBlocks_Request__rosidl_typesupport_introspection_c__LocateBlocks_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &cobot_interfaces__srv__LocateBlocks_Request__rosidl_typesupport_introspection_c__LocateBlocks_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "cobot_interfaces/srv/detail/locate_blocks__rosidl_typesupport_introspection_c.h"
// already included above
// #include "cobot_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "cobot_interfaces/srv/detail/locate_blocks__functions.h"
// already included above
// #include "cobot_interfaces/srv/detail/locate_blocks__struct.h"


// Include directives for member types
// Member `message`
// already included above
// #include "rosidl_runtime_c/string_functions.h"
// Member `blocks`
#include "cobot_interfaces/msg/block_info.h"
// Member `blocks`
#include "cobot_interfaces/msg/detail/block_info__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void cobot_interfaces__srv__LocateBlocks_Response__rosidl_typesupport_introspection_c__LocateBlocks_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  cobot_interfaces__srv__LocateBlocks_Response__init(message_memory);
}

void cobot_interfaces__srv__LocateBlocks_Response__rosidl_typesupport_introspection_c__LocateBlocks_Response_fini_function(void * message_memory)
{
  cobot_interfaces__srv__LocateBlocks_Response__fini(message_memory);
}

size_t cobot_interfaces__srv__LocateBlocks_Response__rosidl_typesupport_introspection_c__size_function__LocateBlocks_Response__blocks(
  const void * untyped_member)
{
  const cobot_interfaces__msg__BlockInfo__Sequence * member =
    (const cobot_interfaces__msg__BlockInfo__Sequence *)(untyped_member);
  return member->size;
}

const void * cobot_interfaces__srv__LocateBlocks_Response__rosidl_typesupport_introspection_c__get_const_function__LocateBlocks_Response__blocks(
  const void * untyped_member, size_t index)
{
  const cobot_interfaces__msg__BlockInfo__Sequence * member =
    (const cobot_interfaces__msg__BlockInfo__Sequence *)(untyped_member);
  return &member->data[index];
}

void * cobot_interfaces__srv__LocateBlocks_Response__rosidl_typesupport_introspection_c__get_function__LocateBlocks_Response__blocks(
  void * untyped_member, size_t index)
{
  cobot_interfaces__msg__BlockInfo__Sequence * member =
    (cobot_interfaces__msg__BlockInfo__Sequence *)(untyped_member);
  return &member->data[index];
}

void cobot_interfaces__srv__LocateBlocks_Response__rosidl_typesupport_introspection_c__fetch_function__LocateBlocks_Response__blocks(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const cobot_interfaces__msg__BlockInfo * item =
    ((const cobot_interfaces__msg__BlockInfo *)
    cobot_interfaces__srv__LocateBlocks_Response__rosidl_typesupport_introspection_c__get_const_function__LocateBlocks_Response__blocks(untyped_member, index));
  cobot_interfaces__msg__BlockInfo * value =
    (cobot_interfaces__msg__BlockInfo *)(untyped_value);
  *value = *item;
}

void cobot_interfaces__srv__LocateBlocks_Response__rosidl_typesupport_introspection_c__assign_function__LocateBlocks_Response__blocks(
  void * untyped_member, size_t index, const void * untyped_value)
{
  cobot_interfaces__msg__BlockInfo * item =
    ((cobot_interfaces__msg__BlockInfo *)
    cobot_interfaces__srv__LocateBlocks_Response__rosidl_typesupport_introspection_c__get_function__LocateBlocks_Response__blocks(untyped_member, index));
  const cobot_interfaces__msg__BlockInfo * value =
    (const cobot_interfaces__msg__BlockInfo *)(untyped_value);
  *item = *value;
}

bool cobot_interfaces__srv__LocateBlocks_Response__rosidl_typesupport_introspection_c__resize_function__LocateBlocks_Response__blocks(
  void * untyped_member, size_t size)
{
  cobot_interfaces__msg__BlockInfo__Sequence * member =
    (cobot_interfaces__msg__BlockInfo__Sequence *)(untyped_member);
  cobot_interfaces__msg__BlockInfo__Sequence__fini(member);
  return cobot_interfaces__msg__BlockInfo__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember cobot_interfaces__srv__LocateBlocks_Response__rosidl_typesupport_introspection_c__LocateBlocks_Response_message_member_array[3] = {
  {
    "success",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot_interfaces__srv__LocateBlocks_Response, success),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "message",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot_interfaces__srv__LocateBlocks_Response, message),  // bytes offset in struct
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
    offsetof(cobot_interfaces__srv__LocateBlocks_Response, blocks),  // bytes offset in struct
    NULL,  // default value
    cobot_interfaces__srv__LocateBlocks_Response__rosidl_typesupport_introspection_c__size_function__LocateBlocks_Response__blocks,  // size() function pointer
    cobot_interfaces__srv__LocateBlocks_Response__rosidl_typesupport_introspection_c__get_const_function__LocateBlocks_Response__blocks,  // get_const(index) function pointer
    cobot_interfaces__srv__LocateBlocks_Response__rosidl_typesupport_introspection_c__get_function__LocateBlocks_Response__blocks,  // get(index) function pointer
    cobot_interfaces__srv__LocateBlocks_Response__rosidl_typesupport_introspection_c__fetch_function__LocateBlocks_Response__blocks,  // fetch(index, &value) function pointer
    cobot_interfaces__srv__LocateBlocks_Response__rosidl_typesupport_introspection_c__assign_function__LocateBlocks_Response__blocks,  // assign(index, value) function pointer
    cobot_interfaces__srv__LocateBlocks_Response__rosidl_typesupport_introspection_c__resize_function__LocateBlocks_Response__blocks  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers cobot_interfaces__srv__LocateBlocks_Response__rosidl_typesupport_introspection_c__LocateBlocks_Response_message_members = {
  "cobot_interfaces__srv",  // message namespace
  "LocateBlocks_Response",  // message name
  3,  // number of fields
  sizeof(cobot_interfaces__srv__LocateBlocks_Response),
  false,  // has_any_key_member_
  cobot_interfaces__srv__LocateBlocks_Response__rosidl_typesupport_introspection_c__LocateBlocks_Response_message_member_array,  // message members
  cobot_interfaces__srv__LocateBlocks_Response__rosidl_typesupport_introspection_c__LocateBlocks_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  cobot_interfaces__srv__LocateBlocks_Response__rosidl_typesupport_introspection_c__LocateBlocks_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t cobot_interfaces__srv__LocateBlocks_Response__rosidl_typesupport_introspection_c__LocateBlocks_Response_message_type_support_handle = {
  0,
  &cobot_interfaces__srv__LocateBlocks_Response__rosidl_typesupport_introspection_c__LocateBlocks_Response_message_members,
  get_message_typesupport_handle_function,
  &cobot_interfaces__srv__LocateBlocks_Response__get_type_hash,
  &cobot_interfaces__srv__LocateBlocks_Response__get_type_description,
  &cobot_interfaces__srv__LocateBlocks_Response__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_cobot_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot_interfaces, srv, LocateBlocks_Response)() {
  cobot_interfaces__srv__LocateBlocks_Response__rosidl_typesupport_introspection_c__LocateBlocks_Response_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot_interfaces, msg, BlockInfo)();
  if (!cobot_interfaces__srv__LocateBlocks_Response__rosidl_typesupport_introspection_c__LocateBlocks_Response_message_type_support_handle.typesupport_identifier) {
    cobot_interfaces__srv__LocateBlocks_Response__rosidl_typesupport_introspection_c__LocateBlocks_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &cobot_interfaces__srv__LocateBlocks_Response__rosidl_typesupport_introspection_c__LocateBlocks_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "cobot_interfaces/srv/detail/locate_blocks__rosidl_typesupport_introspection_c.h"
// already included above
// #include "cobot_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "cobot_interfaces/srv/detail/locate_blocks__functions.h"
// already included above
// #include "cobot_interfaces/srv/detail/locate_blocks__struct.h"


// Include directives for member types
// Member `info`
#include "service_msgs/msg/service_event_info.h"
// Member `info`
#include "service_msgs/msg/detail/service_event_info__rosidl_typesupport_introspection_c.h"
// Member `request`
// Member `response`
#include "cobot_interfaces/srv/locate_blocks.h"
// Member `request`
// Member `response`
// already included above
// #include "cobot_interfaces/srv/detail/locate_blocks__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void cobot_interfaces__srv__LocateBlocks_Event__rosidl_typesupport_introspection_c__LocateBlocks_Event_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  cobot_interfaces__srv__LocateBlocks_Event__init(message_memory);
}

void cobot_interfaces__srv__LocateBlocks_Event__rosidl_typesupport_introspection_c__LocateBlocks_Event_fini_function(void * message_memory)
{
  cobot_interfaces__srv__LocateBlocks_Event__fini(message_memory);
}

size_t cobot_interfaces__srv__LocateBlocks_Event__rosidl_typesupport_introspection_c__size_function__LocateBlocks_Event__request(
  const void * untyped_member)
{
  const cobot_interfaces__srv__LocateBlocks_Request__Sequence * member =
    (const cobot_interfaces__srv__LocateBlocks_Request__Sequence *)(untyped_member);
  return member->size;
}

const void * cobot_interfaces__srv__LocateBlocks_Event__rosidl_typesupport_introspection_c__get_const_function__LocateBlocks_Event__request(
  const void * untyped_member, size_t index)
{
  const cobot_interfaces__srv__LocateBlocks_Request__Sequence * member =
    (const cobot_interfaces__srv__LocateBlocks_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void * cobot_interfaces__srv__LocateBlocks_Event__rosidl_typesupport_introspection_c__get_function__LocateBlocks_Event__request(
  void * untyped_member, size_t index)
{
  cobot_interfaces__srv__LocateBlocks_Request__Sequence * member =
    (cobot_interfaces__srv__LocateBlocks_Request__Sequence *)(untyped_member);
  return &member->data[index];
}

void cobot_interfaces__srv__LocateBlocks_Event__rosidl_typesupport_introspection_c__fetch_function__LocateBlocks_Event__request(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const cobot_interfaces__srv__LocateBlocks_Request * item =
    ((const cobot_interfaces__srv__LocateBlocks_Request *)
    cobot_interfaces__srv__LocateBlocks_Event__rosidl_typesupport_introspection_c__get_const_function__LocateBlocks_Event__request(untyped_member, index));
  cobot_interfaces__srv__LocateBlocks_Request * value =
    (cobot_interfaces__srv__LocateBlocks_Request *)(untyped_value);
  *value = *item;
}

void cobot_interfaces__srv__LocateBlocks_Event__rosidl_typesupport_introspection_c__assign_function__LocateBlocks_Event__request(
  void * untyped_member, size_t index, const void * untyped_value)
{
  cobot_interfaces__srv__LocateBlocks_Request * item =
    ((cobot_interfaces__srv__LocateBlocks_Request *)
    cobot_interfaces__srv__LocateBlocks_Event__rosidl_typesupport_introspection_c__get_function__LocateBlocks_Event__request(untyped_member, index));
  const cobot_interfaces__srv__LocateBlocks_Request * value =
    (const cobot_interfaces__srv__LocateBlocks_Request *)(untyped_value);
  *item = *value;
}

bool cobot_interfaces__srv__LocateBlocks_Event__rosidl_typesupport_introspection_c__resize_function__LocateBlocks_Event__request(
  void * untyped_member, size_t size)
{
  cobot_interfaces__srv__LocateBlocks_Request__Sequence * member =
    (cobot_interfaces__srv__LocateBlocks_Request__Sequence *)(untyped_member);
  cobot_interfaces__srv__LocateBlocks_Request__Sequence__fini(member);
  return cobot_interfaces__srv__LocateBlocks_Request__Sequence__init(member, size);
}

size_t cobot_interfaces__srv__LocateBlocks_Event__rosidl_typesupport_introspection_c__size_function__LocateBlocks_Event__response(
  const void * untyped_member)
{
  const cobot_interfaces__srv__LocateBlocks_Response__Sequence * member =
    (const cobot_interfaces__srv__LocateBlocks_Response__Sequence *)(untyped_member);
  return member->size;
}

const void * cobot_interfaces__srv__LocateBlocks_Event__rosidl_typesupport_introspection_c__get_const_function__LocateBlocks_Event__response(
  const void * untyped_member, size_t index)
{
  const cobot_interfaces__srv__LocateBlocks_Response__Sequence * member =
    (const cobot_interfaces__srv__LocateBlocks_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void * cobot_interfaces__srv__LocateBlocks_Event__rosidl_typesupport_introspection_c__get_function__LocateBlocks_Event__response(
  void * untyped_member, size_t index)
{
  cobot_interfaces__srv__LocateBlocks_Response__Sequence * member =
    (cobot_interfaces__srv__LocateBlocks_Response__Sequence *)(untyped_member);
  return &member->data[index];
}

void cobot_interfaces__srv__LocateBlocks_Event__rosidl_typesupport_introspection_c__fetch_function__LocateBlocks_Event__response(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const cobot_interfaces__srv__LocateBlocks_Response * item =
    ((const cobot_interfaces__srv__LocateBlocks_Response *)
    cobot_interfaces__srv__LocateBlocks_Event__rosidl_typesupport_introspection_c__get_const_function__LocateBlocks_Event__response(untyped_member, index));
  cobot_interfaces__srv__LocateBlocks_Response * value =
    (cobot_interfaces__srv__LocateBlocks_Response *)(untyped_value);
  *value = *item;
}

void cobot_interfaces__srv__LocateBlocks_Event__rosidl_typesupport_introspection_c__assign_function__LocateBlocks_Event__response(
  void * untyped_member, size_t index, const void * untyped_value)
{
  cobot_interfaces__srv__LocateBlocks_Response * item =
    ((cobot_interfaces__srv__LocateBlocks_Response *)
    cobot_interfaces__srv__LocateBlocks_Event__rosidl_typesupport_introspection_c__get_function__LocateBlocks_Event__response(untyped_member, index));
  const cobot_interfaces__srv__LocateBlocks_Response * value =
    (const cobot_interfaces__srv__LocateBlocks_Response *)(untyped_value);
  *item = *value;
}

bool cobot_interfaces__srv__LocateBlocks_Event__rosidl_typesupport_introspection_c__resize_function__LocateBlocks_Event__response(
  void * untyped_member, size_t size)
{
  cobot_interfaces__srv__LocateBlocks_Response__Sequence * member =
    (cobot_interfaces__srv__LocateBlocks_Response__Sequence *)(untyped_member);
  cobot_interfaces__srv__LocateBlocks_Response__Sequence__fini(member);
  return cobot_interfaces__srv__LocateBlocks_Response__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember cobot_interfaces__srv__LocateBlocks_Event__rosidl_typesupport_introspection_c__LocateBlocks_Event_message_member_array[3] = {
  {
    "info",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(cobot_interfaces__srv__LocateBlocks_Event, info),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "request",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(cobot_interfaces__srv__LocateBlocks_Event, request),  // bytes offset in struct
    NULL,  // default value
    cobot_interfaces__srv__LocateBlocks_Event__rosidl_typesupport_introspection_c__size_function__LocateBlocks_Event__request,  // size() function pointer
    cobot_interfaces__srv__LocateBlocks_Event__rosidl_typesupport_introspection_c__get_const_function__LocateBlocks_Event__request,  // get_const(index) function pointer
    cobot_interfaces__srv__LocateBlocks_Event__rosidl_typesupport_introspection_c__get_function__LocateBlocks_Event__request,  // get(index) function pointer
    cobot_interfaces__srv__LocateBlocks_Event__rosidl_typesupport_introspection_c__fetch_function__LocateBlocks_Event__request,  // fetch(index, &value) function pointer
    cobot_interfaces__srv__LocateBlocks_Event__rosidl_typesupport_introspection_c__assign_function__LocateBlocks_Event__request,  // assign(index, value) function pointer
    cobot_interfaces__srv__LocateBlocks_Event__rosidl_typesupport_introspection_c__resize_function__LocateBlocks_Event__request  // resize(index) function pointer
  },
  {
    "response",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    false,  // is key
    true,  // is array
    1,  // array size
    true,  // is upper bound
    offsetof(cobot_interfaces__srv__LocateBlocks_Event, response),  // bytes offset in struct
    NULL,  // default value
    cobot_interfaces__srv__LocateBlocks_Event__rosidl_typesupport_introspection_c__size_function__LocateBlocks_Event__response,  // size() function pointer
    cobot_interfaces__srv__LocateBlocks_Event__rosidl_typesupport_introspection_c__get_const_function__LocateBlocks_Event__response,  // get_const(index) function pointer
    cobot_interfaces__srv__LocateBlocks_Event__rosidl_typesupport_introspection_c__get_function__LocateBlocks_Event__response,  // get(index) function pointer
    cobot_interfaces__srv__LocateBlocks_Event__rosidl_typesupport_introspection_c__fetch_function__LocateBlocks_Event__response,  // fetch(index, &value) function pointer
    cobot_interfaces__srv__LocateBlocks_Event__rosidl_typesupport_introspection_c__assign_function__LocateBlocks_Event__response,  // assign(index, value) function pointer
    cobot_interfaces__srv__LocateBlocks_Event__rosidl_typesupport_introspection_c__resize_function__LocateBlocks_Event__response  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers cobot_interfaces__srv__LocateBlocks_Event__rosidl_typesupport_introspection_c__LocateBlocks_Event_message_members = {
  "cobot_interfaces__srv",  // message namespace
  "LocateBlocks_Event",  // message name
  3,  // number of fields
  sizeof(cobot_interfaces__srv__LocateBlocks_Event),
  false,  // has_any_key_member_
  cobot_interfaces__srv__LocateBlocks_Event__rosidl_typesupport_introspection_c__LocateBlocks_Event_message_member_array,  // message members
  cobot_interfaces__srv__LocateBlocks_Event__rosidl_typesupport_introspection_c__LocateBlocks_Event_init_function,  // function to initialize message memory (memory has to be allocated)
  cobot_interfaces__srv__LocateBlocks_Event__rosidl_typesupport_introspection_c__LocateBlocks_Event_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t cobot_interfaces__srv__LocateBlocks_Event__rosidl_typesupport_introspection_c__LocateBlocks_Event_message_type_support_handle = {
  0,
  &cobot_interfaces__srv__LocateBlocks_Event__rosidl_typesupport_introspection_c__LocateBlocks_Event_message_members,
  get_message_typesupport_handle_function,
  &cobot_interfaces__srv__LocateBlocks_Event__get_type_hash,
  &cobot_interfaces__srv__LocateBlocks_Event__get_type_description,
  &cobot_interfaces__srv__LocateBlocks_Event__get_type_description_sources,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_cobot_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot_interfaces, srv, LocateBlocks_Event)() {
  cobot_interfaces__srv__LocateBlocks_Event__rosidl_typesupport_introspection_c__LocateBlocks_Event_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, service_msgs, msg, ServiceEventInfo)();
  cobot_interfaces__srv__LocateBlocks_Event__rosidl_typesupport_introspection_c__LocateBlocks_Event_message_member_array[1].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot_interfaces, srv, LocateBlocks_Request)();
  cobot_interfaces__srv__LocateBlocks_Event__rosidl_typesupport_introspection_c__LocateBlocks_Event_message_member_array[2].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot_interfaces, srv, LocateBlocks_Response)();
  if (!cobot_interfaces__srv__LocateBlocks_Event__rosidl_typesupport_introspection_c__LocateBlocks_Event_message_type_support_handle.typesupport_identifier) {
    cobot_interfaces__srv__LocateBlocks_Event__rosidl_typesupport_introspection_c__LocateBlocks_Event_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &cobot_interfaces__srv__LocateBlocks_Event__rosidl_typesupport_introspection_c__LocateBlocks_Event_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "cobot_interfaces/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "cobot_interfaces/srv/detail/locate_blocks__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers cobot_interfaces__srv__detail__locate_blocks__rosidl_typesupport_introspection_c__LocateBlocks_service_members = {
  "cobot_interfaces__srv",  // service namespace
  "LocateBlocks",  // service name
  // the following fields are initialized below on first access
  NULL,  // request message
  // cobot_interfaces__srv__detail__locate_blocks__rosidl_typesupport_introspection_c__LocateBlocks_Request_message_type_support_handle,
  NULL,  // response message
  // cobot_interfaces__srv__detail__locate_blocks__rosidl_typesupport_introspection_c__LocateBlocks_Response_message_type_support_handle
  NULL  // event_message
  // cobot_interfaces__srv__detail__locate_blocks__rosidl_typesupport_introspection_c__LocateBlocks_Response_message_type_support_handle
};


static rosidl_service_type_support_t cobot_interfaces__srv__detail__locate_blocks__rosidl_typesupport_introspection_c__LocateBlocks_service_type_support_handle = {
  0,
  &cobot_interfaces__srv__detail__locate_blocks__rosidl_typesupport_introspection_c__LocateBlocks_service_members,
  get_service_typesupport_handle_function,
  &cobot_interfaces__srv__LocateBlocks_Request__rosidl_typesupport_introspection_c__LocateBlocks_Request_message_type_support_handle,
  &cobot_interfaces__srv__LocateBlocks_Response__rosidl_typesupport_introspection_c__LocateBlocks_Response_message_type_support_handle,
  &cobot_interfaces__srv__LocateBlocks_Event__rosidl_typesupport_introspection_c__LocateBlocks_Event_message_type_support_handle,
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    cobot_interfaces,
    srv,
    LocateBlocks
  ),
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    cobot_interfaces,
    srv,
    LocateBlocks
  ),
  &cobot_interfaces__srv__LocateBlocks__get_type_hash,
  &cobot_interfaces__srv__LocateBlocks__get_type_description,
  &cobot_interfaces__srv__LocateBlocks__get_type_description_sources,
};

// Forward declaration of message type support functions for service members
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot_interfaces, srv, LocateBlocks_Request)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot_interfaces, srv, LocateBlocks_Response)(void);

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot_interfaces, srv, LocateBlocks_Event)(void);

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_cobot_interfaces
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot_interfaces, srv, LocateBlocks)(void) {
  if (!cobot_interfaces__srv__detail__locate_blocks__rosidl_typesupport_introspection_c__LocateBlocks_service_type_support_handle.typesupport_identifier) {
    cobot_interfaces__srv__detail__locate_blocks__rosidl_typesupport_introspection_c__LocateBlocks_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)cobot_interfaces__srv__detail__locate_blocks__rosidl_typesupport_introspection_c__LocateBlocks_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot_interfaces, srv, LocateBlocks_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot_interfaces, srv, LocateBlocks_Response)()->data;
  }
  if (!service_members->event_members_) {
    service_members->event_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot_interfaces, srv, LocateBlocks_Event)()->data;
  }

  return &cobot_interfaces__srv__detail__locate_blocks__rosidl_typesupport_introspection_c__LocateBlocks_service_type_support_handle;
}
