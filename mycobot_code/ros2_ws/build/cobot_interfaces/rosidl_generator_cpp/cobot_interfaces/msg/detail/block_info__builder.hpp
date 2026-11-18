// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from cobot_interfaces:msg/BlockInfo.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cobot_interfaces/msg/block_info.hpp"


#ifndef COBOT_INTERFACES__MSG__DETAIL__BLOCK_INFO__BUILDER_HPP_
#define COBOT_INTERFACES__MSG__DETAIL__BLOCK_INFO__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "cobot_interfaces/msg/detail/block_info__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace cobot_interfaces
{

namespace msg
{

namespace builder
{

class Init_BlockInfo_width
{
public:
  explicit Init_BlockInfo_width(::cobot_interfaces::msg::BlockInfo & msg)
  : msg_(msg)
  {}
  ::cobot_interfaces::msg::BlockInfo width(::cobot_interfaces::msg::BlockInfo::_width_type arg)
  {
    msg_.width = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cobot_interfaces::msg::BlockInfo msg_;
};

class Init_BlockInfo_grasp_yaw
{
public:
  explicit Init_BlockInfo_grasp_yaw(::cobot_interfaces::msg::BlockInfo & msg)
  : msg_(msg)
  {}
  Init_BlockInfo_width grasp_yaw(::cobot_interfaces::msg::BlockInfo::_grasp_yaw_type arg)
  {
    msg_.grasp_yaw = std::move(arg);
    return Init_BlockInfo_width(msg_);
  }

private:
  ::cobot_interfaces::msg::BlockInfo msg_;
};

class Init_BlockInfo_position
{
public:
  explicit Init_BlockInfo_position(::cobot_interfaces::msg::BlockInfo & msg)
  : msg_(msg)
  {}
  Init_BlockInfo_grasp_yaw position(::cobot_interfaces::msg::BlockInfo::_position_type arg)
  {
    msg_.position = std::move(arg);
    return Init_BlockInfo_grasp_yaw(msg_);
  }

private:
  ::cobot_interfaces::msg::BlockInfo msg_;
};

class Init_BlockInfo_graspable
{
public:
  explicit Init_BlockInfo_graspable(::cobot_interfaces::msg::BlockInfo & msg)
  : msg_(msg)
  {}
  Init_BlockInfo_position graspable(::cobot_interfaces::msg::BlockInfo::_graspable_type arg)
  {
    msg_.graspable = std::move(arg);
    return Init_BlockInfo_position(msg_);
  }

private:
  ::cobot_interfaces::msg::BlockInfo msg_;
};

class Init_BlockInfo_confidence
{
public:
  explicit Init_BlockInfo_confidence(::cobot_interfaces::msg::BlockInfo & msg)
  : msg_(msg)
  {}
  Init_BlockInfo_graspable confidence(::cobot_interfaces::msg::BlockInfo::_confidence_type arg)
  {
    msg_.confidence = std::move(arg);
    return Init_BlockInfo_graspable(msg_);
  }

private:
  ::cobot_interfaces::msg::BlockInfo msg_;
};

class Init_BlockInfo_color
{
public:
  Init_BlockInfo_color()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_BlockInfo_confidence color(::cobot_interfaces::msg::BlockInfo::_color_type arg)
  {
    msg_.color = std::move(arg);
    return Init_BlockInfo_confidence(msg_);
  }

private:
  ::cobot_interfaces::msg::BlockInfo msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::cobot_interfaces::msg::BlockInfo>()
{
  return cobot_interfaces::msg::builder::Init_BlockInfo_color();
}

}  // namespace cobot_interfaces

#endif  // COBOT_INTERFACES__MSG__DETAIL__BLOCK_INFO__BUILDER_HPP_
