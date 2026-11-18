// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from cobot_interfaces:msg/BlockTarget.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cobot_interfaces/msg/block_target.hpp"


#ifndef COBOT_INTERFACES__MSG__DETAIL__BLOCK_TARGET__BUILDER_HPP_
#define COBOT_INTERFACES__MSG__DETAIL__BLOCK_TARGET__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "cobot_interfaces/msg/detail/block_target__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace cobot_interfaces
{

namespace msg
{

namespace builder
{

class Init_BlockTarget_corners
{
public:
  explicit Init_BlockTarget_corners(::cobot_interfaces::msg::BlockTarget & msg)
  : msg_(msg)
  {}
  ::cobot_interfaces::msg::BlockTarget corners(::cobot_interfaces::msg::BlockTarget::_corners_type arg)
  {
    msg_.corners = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cobot_interfaces::msg::BlockTarget msg_;
};

class Init_BlockTarget_center
{
public:
  explicit Init_BlockTarget_center(::cobot_interfaces::msg::BlockTarget & msg)
  : msg_(msg)
  {}
  Init_BlockTarget_corners center(::cobot_interfaces::msg::BlockTarget::_center_type arg)
  {
    msg_.center = std::move(arg);
    return Init_BlockTarget_corners(msg_);
  }

private:
  ::cobot_interfaces::msg::BlockTarget msg_;
};

class Init_BlockTarget_confidence
{
public:
  explicit Init_BlockTarget_confidence(::cobot_interfaces::msg::BlockTarget & msg)
  : msg_(msg)
  {}
  Init_BlockTarget_center confidence(::cobot_interfaces::msg::BlockTarget::_confidence_type arg)
  {
    msg_.confidence = std::move(arg);
    return Init_BlockTarget_center(msg_);
  }

private:
  ::cobot_interfaces::msg::BlockTarget msg_;
};

class Init_BlockTarget_should_grasp
{
public:
  explicit Init_BlockTarget_should_grasp(::cobot_interfaces::msg::BlockTarget & msg)
  : msg_(msg)
  {}
  Init_BlockTarget_confidence should_grasp(::cobot_interfaces::msg::BlockTarget::_should_grasp_type arg)
  {
    msg_.should_grasp = std::move(arg);
    return Init_BlockTarget_confidence(msg_);
  }

private:
  ::cobot_interfaces::msg::BlockTarget msg_;
};

class Init_BlockTarget_color
{
public:
  explicit Init_BlockTarget_color(::cobot_interfaces::msg::BlockTarget & msg)
  : msg_(msg)
  {}
  Init_BlockTarget_should_grasp color(::cobot_interfaces::msg::BlockTarget::_color_type arg)
  {
    msg_.color = std::move(arg);
    return Init_BlockTarget_should_grasp(msg_);
  }

private:
  ::cobot_interfaces::msg::BlockTarget msg_;
};

class Init_BlockTarget_header
{
public:
  Init_BlockTarget_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_BlockTarget_color header(::cobot_interfaces::msg::BlockTarget::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_BlockTarget_color(msg_);
  }

private:
  ::cobot_interfaces::msg::BlockTarget msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::cobot_interfaces::msg::BlockTarget>()
{
  return cobot_interfaces::msg::builder::Init_BlockTarget_header();
}

}  // namespace cobot_interfaces

#endif  // COBOT_INTERFACES__MSG__DETAIL__BLOCK_TARGET__BUILDER_HPP_
