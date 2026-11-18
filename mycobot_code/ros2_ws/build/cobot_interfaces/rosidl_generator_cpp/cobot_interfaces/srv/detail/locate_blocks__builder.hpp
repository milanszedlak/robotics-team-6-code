// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from cobot_interfaces:srv/LocateBlocks.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cobot_interfaces/srv/locate_blocks.hpp"


#ifndef COBOT_INTERFACES__SRV__DETAIL__LOCATE_BLOCKS__BUILDER_HPP_
#define COBOT_INTERFACES__SRV__DETAIL__LOCATE_BLOCKS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "cobot_interfaces/srv/detail/locate_blocks__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace cobot_interfaces
{

namespace srv
{

namespace builder
{

class Init_LocateBlocks_Request_go_home
{
public:
  explicit Init_LocateBlocks_Request_go_home(::cobot_interfaces::srv::LocateBlocks_Request & msg)
  : msg_(msg)
  {}
  ::cobot_interfaces::srv::LocateBlocks_Request go_home(::cobot_interfaces::srv::LocateBlocks_Request::_go_home_type arg)
  {
    msg_.go_home = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cobot_interfaces::srv::LocateBlocks_Request msg_;
};

class Init_LocateBlocks_Request_color
{
public:
  Init_LocateBlocks_Request_color()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LocateBlocks_Request_go_home color(::cobot_interfaces::srv::LocateBlocks_Request::_color_type arg)
  {
    msg_.color = std::move(arg);
    return Init_LocateBlocks_Request_go_home(msg_);
  }

private:
  ::cobot_interfaces::srv::LocateBlocks_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::cobot_interfaces::srv::LocateBlocks_Request>()
{
  return cobot_interfaces::srv::builder::Init_LocateBlocks_Request_color();
}

}  // namespace cobot_interfaces


namespace cobot_interfaces
{

namespace srv
{

namespace builder
{

class Init_LocateBlocks_Response_blocks
{
public:
  explicit Init_LocateBlocks_Response_blocks(::cobot_interfaces::srv::LocateBlocks_Response & msg)
  : msg_(msg)
  {}
  ::cobot_interfaces::srv::LocateBlocks_Response blocks(::cobot_interfaces::srv::LocateBlocks_Response::_blocks_type arg)
  {
    msg_.blocks = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cobot_interfaces::srv::LocateBlocks_Response msg_;
};

class Init_LocateBlocks_Response_message
{
public:
  explicit Init_LocateBlocks_Response_message(::cobot_interfaces::srv::LocateBlocks_Response & msg)
  : msg_(msg)
  {}
  Init_LocateBlocks_Response_blocks message(::cobot_interfaces::srv::LocateBlocks_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return Init_LocateBlocks_Response_blocks(msg_);
  }

private:
  ::cobot_interfaces::srv::LocateBlocks_Response msg_;
};

class Init_LocateBlocks_Response_success
{
public:
  Init_LocateBlocks_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LocateBlocks_Response_message success(::cobot_interfaces::srv::LocateBlocks_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_LocateBlocks_Response_message(msg_);
  }

private:
  ::cobot_interfaces::srv::LocateBlocks_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::cobot_interfaces::srv::LocateBlocks_Response>()
{
  return cobot_interfaces::srv::builder::Init_LocateBlocks_Response_success();
}

}  // namespace cobot_interfaces


namespace cobot_interfaces
{

namespace srv
{

namespace builder
{

class Init_LocateBlocks_Event_response
{
public:
  explicit Init_LocateBlocks_Event_response(::cobot_interfaces::srv::LocateBlocks_Event & msg)
  : msg_(msg)
  {}
  ::cobot_interfaces::srv::LocateBlocks_Event response(::cobot_interfaces::srv::LocateBlocks_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cobot_interfaces::srv::LocateBlocks_Event msg_;
};

class Init_LocateBlocks_Event_request
{
public:
  explicit Init_LocateBlocks_Event_request(::cobot_interfaces::srv::LocateBlocks_Event & msg)
  : msg_(msg)
  {}
  Init_LocateBlocks_Event_response request(::cobot_interfaces::srv::LocateBlocks_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_LocateBlocks_Event_response(msg_);
  }

private:
  ::cobot_interfaces::srv::LocateBlocks_Event msg_;
};

class Init_LocateBlocks_Event_info
{
public:
  Init_LocateBlocks_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_LocateBlocks_Event_request info(::cobot_interfaces::srv::LocateBlocks_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_LocateBlocks_Event_request(msg_);
  }

private:
  ::cobot_interfaces::srv::LocateBlocks_Event msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::cobot_interfaces::srv::LocateBlocks_Event>()
{
  return cobot_interfaces::srv::builder::Init_LocateBlocks_Event_info();
}

}  // namespace cobot_interfaces

#endif  // COBOT_INTERFACES__SRV__DETAIL__LOCATE_BLOCKS__BUILDER_HPP_
