// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from cobot_interfaces:msg/BlockInfo.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cobot_interfaces/msg/block_info.hpp"


#ifndef COBOT_INTERFACES__MSG__DETAIL__BLOCK_INFO__TRAITS_HPP_
#define COBOT_INTERFACES__MSG__DETAIL__BLOCK_INFO__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "cobot_interfaces/msg/detail/block_info__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'position'
#include "geometry_msgs/msg/detail/point__traits.hpp"

namespace cobot_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const BlockInfo & msg,
  std::ostream & out)
{
  out << "{";
  // member: color
  {
    out << "color: ";
    rosidl_generator_traits::value_to_yaml(msg.color, out);
    out << ", ";
  }

  // member: confidence
  {
    out << "confidence: ";
    rosidl_generator_traits::value_to_yaml(msg.confidence, out);
    out << ", ";
  }

  // member: graspable
  {
    out << "graspable: ";
    rosidl_generator_traits::value_to_yaml(msg.graspable, out);
    out << ", ";
  }

  // member: position
  {
    out << "position: ";
    to_flow_style_yaml(msg.position, out);
    out << ", ";
  }

  // member: grasp_yaw
  {
    out << "grasp_yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.grasp_yaw, out);
    out << ", ";
  }

  // member: width
  {
    out << "width: ";
    rosidl_generator_traits::value_to_yaml(msg.width, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const BlockInfo & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: color
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "color: ";
    rosidl_generator_traits::value_to_yaml(msg.color, out);
    out << "\n";
  }

  // member: confidence
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "confidence: ";
    rosidl_generator_traits::value_to_yaml(msg.confidence, out);
    out << "\n";
  }

  // member: graspable
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "graspable: ";
    rosidl_generator_traits::value_to_yaml(msg.graspable, out);
    out << "\n";
  }

  // member: position
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "position:\n";
    to_block_style_yaml(msg.position, out, indentation + 2);
  }

  // member: grasp_yaw
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "grasp_yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.grasp_yaw, out);
    out << "\n";
  }

  // member: width
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "width: ";
    rosidl_generator_traits::value_to_yaml(msg.width, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const BlockInfo & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace cobot_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use cobot_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const cobot_interfaces::msg::BlockInfo & msg,
  std::ostream & out, size_t indentation = 0)
{
  cobot_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use cobot_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const cobot_interfaces::msg::BlockInfo & msg)
{
  return cobot_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<cobot_interfaces::msg::BlockInfo>()
{
  return "cobot_interfaces::msg::BlockInfo";
}

template<>
inline const char * name<cobot_interfaces::msg::BlockInfo>()
{
  return "cobot_interfaces/msg/BlockInfo";
}

template<>
struct has_fixed_size<cobot_interfaces::msg::BlockInfo>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<cobot_interfaces::msg::BlockInfo>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<cobot_interfaces::msg::BlockInfo>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // COBOT_INTERFACES__MSG__DETAIL__BLOCK_INFO__TRAITS_HPP_
