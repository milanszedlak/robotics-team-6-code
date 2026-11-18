// generated from rosidl_typesupport_fastrtps_c/resource/idl__rosidl_typesupport_fastrtps_c.h.em
// with input from cobot_interfaces:msg/BlockInfo.idl
// generated code does not contain a copyright notice
#ifndef COBOT_INTERFACES__MSG__DETAIL__BLOCK_INFO__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
#define COBOT_INTERFACES__MSG__DETAIL__BLOCK_INFO__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_


#include <stddef.h>
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_interface/macros.h"
#include "cobot_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "cobot_interfaces/msg/detail/block_info__struct.h"
#include "fastcdr/Cdr.h"

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cobot_interfaces
bool cdr_serialize_cobot_interfaces__msg__BlockInfo(
  const cobot_interfaces__msg__BlockInfo * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cobot_interfaces
bool cdr_deserialize_cobot_interfaces__msg__BlockInfo(
  eprosima::fastcdr::Cdr &,
  cobot_interfaces__msg__BlockInfo * ros_message);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cobot_interfaces
size_t get_serialized_size_cobot_interfaces__msg__BlockInfo(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cobot_interfaces
size_t max_serialized_size_cobot_interfaces__msg__BlockInfo(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cobot_interfaces
bool cdr_serialize_key_cobot_interfaces__msg__BlockInfo(
  const cobot_interfaces__msg__BlockInfo * ros_message,
  eprosima::fastcdr::Cdr & cdr);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cobot_interfaces
size_t get_serialized_size_key_cobot_interfaces__msg__BlockInfo(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cobot_interfaces
size_t max_serialized_size_key_cobot_interfaces__msg__BlockInfo(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_cobot_interfaces
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, cobot_interfaces, msg, BlockInfo)();

#ifdef __cplusplus
}
#endif

#endif  // COBOT_INTERFACES__MSG__DETAIL__BLOCK_INFO__ROSIDL_TYPESUPPORT_FASTRTPS_C_H_
