// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from cobot_interfaces:msg/BlockTargetArray.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cobot_interfaces/msg/block_target_array.hpp"


#ifndef COBOT_INTERFACES__MSG__DETAIL__BLOCK_TARGET_ARRAY__BUILDER_HPP_
#define COBOT_INTERFACES__MSG__DETAIL__BLOCK_TARGET_ARRAY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "cobot_interfaces/msg/detail/block_target_array__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace cobot_interfaces
{

namespace msg
{

namespace builder
{

class Init_BlockTargetArray_blocks
{
public:
  explicit Init_BlockTargetArray_blocks(::cobot_interfaces::msg::BlockTargetArray & msg)
  : msg_(msg)
  {}
  ::cobot_interfaces::msg::BlockTargetArray blocks(::cobot_interfaces::msg::BlockTargetArray::_blocks_type arg)
  {
    msg_.blocks = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cobot_interfaces::msg::BlockTargetArray msg_;
};

class Init_BlockTargetArray_header
{
public:
  Init_BlockTargetArray_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_BlockTargetArray_blocks header(::cobot_interfaces::msg::BlockTargetArray::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_BlockTargetArray_blocks(msg_);
  }

private:
  ::cobot_interfaces::msg::BlockTargetArray msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::cobot_interfaces::msg::BlockTargetArray>()
{
  return cobot_interfaces::msg::builder::Init_BlockTargetArray_header();
}

}  // namespace cobot_interfaces

#endif  // COBOT_INTERFACES__MSG__DETAIL__BLOCK_TARGET_ARRAY__BUILDER_HPP_
