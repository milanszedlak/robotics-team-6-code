// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from cobot_interfaces:msg/BlockTarget.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cobot_interfaces/msg/block_target.hpp"


#ifndef COBOT_INTERFACES__MSG__DETAIL__BLOCK_TARGET__TRAITS_HPP_
#define COBOT_INTERFACES__MSG__DETAIL__BLOCK_TARGET__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "cobot_interfaces/msg/detail/block_target__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'center'
// Member 'corners'
#include "geometry_msgs/msg/detail/point__traits.hpp"

namespace cobot_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const BlockTarget & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: color
  {
    out << "color: ";
    rosidl_generator_traits::value_to_yaml(msg.color, out);
    out << ", ";
  }

  // member: should_grasp
  {
    out << "should_grasp: ";
    rosidl_generator_traits::value_to_yaml(msg.should_grasp, out);
    out << ", ";
  }

  // member: confidence
  {
    out << "confidence: ";
    rosidl_generator_traits::value_to_yaml(msg.confidence, out);
    out << ", ";
  }

  // member: center
  {
    out << "center: ";
    to_flow_style_yaml(msg.center, out);
    out << ", ";
  }

  // member: corners
  {
    if (msg.corners.size() == 0) {
      out << "corners: []";
    } else {
      out << "corners: [";
      size_t pending_items = msg.corners.size();
      for (auto item : msg.corners) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const BlockTarget & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: header
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "header:\n";
    to_block_style_yaml(msg.header, out, indentation + 2);
  }

  // member: color
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "color: ";
    rosidl_generator_traits::value_to_yaml(msg.color, out);
    out << "\n";
  }

  // member: should_grasp
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "should_grasp: ";
    rosidl_generator_traits::value_to_yaml(msg.should_grasp, out);
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

  // member: center
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "center:\n";
    to_block_style_yaml(msg.center, out, indentation + 2);
  }

  // member: corners
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.corners.size() == 0) {
      out << "corners: []\n";
    } else {
      out << "corners:\n";
      for (auto item : msg.corners) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const BlockTarget & msg, bool use_flow_style = false)
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
  const cobot_interfaces::msg::BlockTarget & msg,
  std::ostream & out, size_t indentation = 0)
{
  cobot_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use cobot_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const cobot_interfaces::msg::BlockTarget & msg)
{
  return cobot_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<cobot_interfaces::msg::BlockTarget>()
{
  return "cobot_interfaces::msg::BlockTarget";
}

template<>
inline const char * name<cobot_interfaces::msg::BlockTarget>()
{
  return "cobot_interfaces/msg/BlockTarget";
}

template<>
struct has_fixed_size<cobot_interfaces::msg::BlockTarget>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<cobot_interfaces::msg::BlockTarget>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<cobot_interfaces::msg::BlockTarget>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // COBOT_INTERFACES__MSG__DETAIL__BLOCK_TARGET__TRAITS_HPP_
