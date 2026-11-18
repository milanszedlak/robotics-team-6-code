// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from cobot_interfaces:msg/BlockTargetArray.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cobot_interfaces/msg/block_target_array.hpp"


#ifndef COBOT_INTERFACES__MSG__DETAIL__BLOCK_TARGET_ARRAY__TRAITS_HPP_
#define COBOT_INTERFACES__MSG__DETAIL__BLOCK_TARGET_ARRAY__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "cobot_interfaces/msg/detail/block_target_array__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"
// Member 'blocks'
#include "cobot_interfaces/msg/detail/block_target__traits.hpp"

namespace cobot_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const BlockTargetArray & msg,
  std::ostream & out)
{
  out << "{";
  // member: header
  {
    out << "header: ";
    to_flow_style_yaml(msg.header, out);
    out << ", ";
  }

  // member: blocks
  {
    if (msg.blocks.size() == 0) {
      out << "blocks: []";
    } else {
      out << "blocks: [";
      size_t pending_items = msg.blocks.size();
      for (auto item : msg.blocks) {
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
  const BlockTargetArray & msg,
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

  // member: blocks
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.blocks.size() == 0) {
      out << "blocks: []\n";
    } else {
      out << "blocks:\n";
      for (auto item : msg.blocks) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const BlockTargetArray & msg, bool use_flow_style = false)
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
  const cobot_interfaces::msg::BlockTargetArray & msg,
  std::ostream & out, size_t indentation = 0)
{
  cobot_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use cobot_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const cobot_interfaces::msg::BlockTargetArray & msg)
{
  return cobot_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<cobot_interfaces::msg::BlockTargetArray>()
{
  return "cobot_interfaces::msg::BlockTargetArray";
}

template<>
inline const char * name<cobot_interfaces::msg::BlockTargetArray>()
{
  return "cobot_interfaces/msg/BlockTargetArray";
}

template<>
struct has_fixed_size<cobot_interfaces::msg::BlockTargetArray>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<cobot_interfaces::msg::BlockTargetArray>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<cobot_interfaces::msg::BlockTargetArray>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // COBOT_INTERFACES__MSG__DETAIL__BLOCK_TARGET_ARRAY__TRAITS_HPP_
