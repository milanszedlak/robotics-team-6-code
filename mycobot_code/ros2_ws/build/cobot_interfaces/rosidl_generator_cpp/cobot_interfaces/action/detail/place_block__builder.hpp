// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from cobot_interfaces:action/PlaceBlock.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cobot_interfaces/action/place_block.hpp"


#ifndef COBOT_INTERFACES__ACTION__DETAIL__PLACE_BLOCK__BUILDER_HPP_
#define COBOT_INTERFACES__ACTION__DETAIL__PLACE_BLOCK__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "cobot_interfaces/action/detail/place_block__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace cobot_interfaces
{

namespace action
{

namespace builder
{

class Init_PlaceBlock_Goal_position
{
public:
  explicit Init_PlaceBlock_Goal_position(::cobot_interfaces::action::PlaceBlock_Goal & msg)
  : msg_(msg)
  {}
  ::cobot_interfaces::action::PlaceBlock_Goal position(::cobot_interfaces::action::PlaceBlock_Goal::_position_type arg)
  {
    msg_.position = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cobot_interfaces::action::PlaceBlock_Goal msg_;
};

class Init_PlaceBlock_Goal_use_position
{
public:
  explicit Init_PlaceBlock_Goal_use_position(::cobot_interfaces::action::PlaceBlock_Goal & msg)
  : msg_(msg)
  {}
  Init_PlaceBlock_Goal_position use_position(::cobot_interfaces::action::PlaceBlock_Goal::_use_position_type arg)
  {
    msg_.use_position = std::move(arg);
    return Init_PlaceBlock_Goal_position(msg_);
  }

private:
  ::cobot_interfaces::action::PlaceBlock_Goal msg_;
};

class Init_PlaceBlock_Goal_location
{
public:
  Init_PlaceBlock_Goal_location()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PlaceBlock_Goal_use_position location(::cobot_interfaces::action::PlaceBlock_Goal::_location_type arg)
  {
    msg_.location = std::move(arg);
    return Init_PlaceBlock_Goal_use_position(msg_);
  }

private:
  ::cobot_interfaces::action::PlaceBlock_Goal msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::cobot_interfaces::action::PlaceBlock_Goal>()
{
  return cobot_interfaces::action::builder::Init_PlaceBlock_Goal_location();
}

}  // namespace cobot_interfaces


namespace cobot_interfaces
{

namespace action
{

namespace builder
{

class Init_PlaceBlock_Result_message
{
public:
  explicit Init_PlaceBlock_Result_message(::cobot_interfaces::action::PlaceBlock_Result & msg)
  : msg_(msg)
  {}
  ::cobot_interfaces::action::PlaceBlock_Result message(::cobot_interfaces::action::PlaceBlock_Result::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cobot_interfaces::action::PlaceBlock_Result msg_;
};

class Init_PlaceBlock_Result_success
{
public:
  Init_PlaceBlock_Result_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PlaceBlock_Result_message success(::cobot_interfaces::action::PlaceBlock_Result::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_PlaceBlock_Result_message(msg_);
  }

private:
  ::cobot_interfaces::action::PlaceBlock_Result msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::cobot_interfaces::action::PlaceBlock_Result>()
{
  return cobot_interfaces::action::builder::Init_PlaceBlock_Result_success();
}

}  // namespace cobot_interfaces


namespace cobot_interfaces
{

namespace action
{

namespace builder
{

class Init_PlaceBlock_Feedback_stage
{
public:
  Init_PlaceBlock_Feedback_stage()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::cobot_interfaces::action::PlaceBlock_Feedback stage(::cobot_interfaces::action::PlaceBlock_Feedback::_stage_type arg)
  {
    msg_.stage = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cobot_interfaces::action::PlaceBlock_Feedback msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::cobot_interfaces::action::PlaceBlock_Feedback>()
{
  return cobot_interfaces::action::builder::Init_PlaceBlock_Feedback_stage();
}

}  // namespace cobot_interfaces


namespace cobot_interfaces
{

namespace action
{

namespace builder
{

class Init_PlaceBlock_SendGoal_Request_goal
{
public:
  explicit Init_PlaceBlock_SendGoal_Request_goal(::cobot_interfaces::action::PlaceBlock_SendGoal_Request & msg)
  : msg_(msg)
  {}
  ::cobot_interfaces::action::PlaceBlock_SendGoal_Request goal(::cobot_interfaces::action::PlaceBlock_SendGoal_Request::_goal_type arg)
  {
    msg_.goal = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cobot_interfaces::action::PlaceBlock_SendGoal_Request msg_;
};

class Init_PlaceBlock_SendGoal_Request_goal_id
{
public:
  Init_PlaceBlock_SendGoal_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PlaceBlock_SendGoal_Request_goal goal_id(::cobot_interfaces::action::PlaceBlock_SendGoal_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_PlaceBlock_SendGoal_Request_goal(msg_);
  }

private:
  ::cobot_interfaces::action::PlaceBlock_SendGoal_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::cobot_interfaces::action::PlaceBlock_SendGoal_Request>()
{
  return cobot_interfaces::action::builder::Init_PlaceBlock_SendGoal_Request_goal_id();
}

}  // namespace cobot_interfaces


namespace cobot_interfaces
{

namespace action
{

namespace builder
{

class Init_PlaceBlock_SendGoal_Response_stamp
{
public:
  explicit Init_PlaceBlock_SendGoal_Response_stamp(::cobot_interfaces::action::PlaceBlock_SendGoal_Response & msg)
  : msg_(msg)
  {}
  ::cobot_interfaces::action::PlaceBlock_SendGoal_Response stamp(::cobot_interfaces::action::PlaceBlock_SendGoal_Response::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cobot_interfaces::action::PlaceBlock_SendGoal_Response msg_;
};

class Init_PlaceBlock_SendGoal_Response_accepted
{
public:
  Init_PlaceBlock_SendGoal_Response_accepted()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PlaceBlock_SendGoal_Response_stamp accepted(::cobot_interfaces::action::PlaceBlock_SendGoal_Response::_accepted_type arg)
  {
    msg_.accepted = std::move(arg);
    return Init_PlaceBlock_SendGoal_Response_stamp(msg_);
  }

private:
  ::cobot_interfaces::action::PlaceBlock_SendGoal_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::cobot_interfaces::action::PlaceBlock_SendGoal_Response>()
{
  return cobot_interfaces::action::builder::Init_PlaceBlock_SendGoal_Response_accepted();
}

}  // namespace cobot_interfaces


namespace cobot_interfaces
{

namespace action
{

namespace builder
{

class Init_PlaceBlock_SendGoal_Event_response
{
public:
  explicit Init_PlaceBlock_SendGoal_Event_response(::cobot_interfaces::action::PlaceBlock_SendGoal_Event & msg)
  : msg_(msg)
  {}
  ::cobot_interfaces::action::PlaceBlock_SendGoal_Event response(::cobot_interfaces::action::PlaceBlock_SendGoal_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cobot_interfaces::action::PlaceBlock_SendGoal_Event msg_;
};

class Init_PlaceBlock_SendGoal_Event_request
{
public:
  explicit Init_PlaceBlock_SendGoal_Event_request(::cobot_interfaces::action::PlaceBlock_SendGoal_Event & msg)
  : msg_(msg)
  {}
  Init_PlaceBlock_SendGoal_Event_response request(::cobot_interfaces::action::PlaceBlock_SendGoal_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_PlaceBlock_SendGoal_Event_response(msg_);
  }

private:
  ::cobot_interfaces::action::PlaceBlock_SendGoal_Event msg_;
};

class Init_PlaceBlock_SendGoal_Event_info
{
public:
  Init_PlaceBlock_SendGoal_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PlaceBlock_SendGoal_Event_request info(::cobot_interfaces::action::PlaceBlock_SendGoal_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_PlaceBlock_SendGoal_Event_request(msg_);
  }

private:
  ::cobot_interfaces::action::PlaceBlock_SendGoal_Event msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::cobot_interfaces::action::PlaceBlock_SendGoal_Event>()
{
  return cobot_interfaces::action::builder::Init_PlaceBlock_SendGoal_Event_info();
}

}  // namespace cobot_interfaces


namespace cobot_interfaces
{

namespace action
{

namespace builder
{

class Init_PlaceBlock_GetResult_Request_goal_id
{
public:
  Init_PlaceBlock_GetResult_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::cobot_interfaces::action::PlaceBlock_GetResult_Request goal_id(::cobot_interfaces::action::PlaceBlock_GetResult_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cobot_interfaces::action::PlaceBlock_GetResult_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::cobot_interfaces::action::PlaceBlock_GetResult_Request>()
{
  return cobot_interfaces::action::builder::Init_PlaceBlock_GetResult_Request_goal_id();
}

}  // namespace cobot_interfaces


namespace cobot_interfaces
{

namespace action
{

namespace builder
{

class Init_PlaceBlock_GetResult_Response_result
{
public:
  explicit Init_PlaceBlock_GetResult_Response_result(::cobot_interfaces::action::PlaceBlock_GetResult_Response & msg)
  : msg_(msg)
  {}
  ::cobot_interfaces::action::PlaceBlock_GetResult_Response result(::cobot_interfaces::action::PlaceBlock_GetResult_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cobot_interfaces::action::PlaceBlock_GetResult_Response msg_;
};

class Init_PlaceBlock_GetResult_Response_status
{
public:
  Init_PlaceBlock_GetResult_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PlaceBlock_GetResult_Response_result status(::cobot_interfaces::action::PlaceBlock_GetResult_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_PlaceBlock_GetResult_Response_result(msg_);
  }

private:
  ::cobot_interfaces::action::PlaceBlock_GetResult_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::cobot_interfaces::action::PlaceBlock_GetResult_Response>()
{
  return cobot_interfaces::action::builder::Init_PlaceBlock_GetResult_Response_status();
}

}  // namespace cobot_interfaces


namespace cobot_interfaces
{

namespace action
{

namespace builder
{

class Init_PlaceBlock_GetResult_Event_response
{
public:
  explicit Init_PlaceBlock_GetResult_Event_response(::cobot_interfaces::action::PlaceBlock_GetResult_Event & msg)
  : msg_(msg)
  {}
  ::cobot_interfaces::action::PlaceBlock_GetResult_Event response(::cobot_interfaces::action::PlaceBlock_GetResult_Event::_response_type arg)
  {
    msg_.response = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cobot_interfaces::action::PlaceBlock_GetResult_Event msg_;
};

class Init_PlaceBlock_GetResult_Event_request
{
public:
  explicit Init_PlaceBlock_GetResult_Event_request(::cobot_interfaces::action::PlaceBlock_GetResult_Event & msg)
  : msg_(msg)
  {}
  Init_PlaceBlock_GetResult_Event_response request(::cobot_interfaces::action::PlaceBlock_GetResult_Event::_request_type arg)
  {
    msg_.request = std::move(arg);
    return Init_PlaceBlock_GetResult_Event_response(msg_);
  }

private:
  ::cobot_interfaces::action::PlaceBlock_GetResult_Event msg_;
};

class Init_PlaceBlock_GetResult_Event_info
{
public:
  Init_PlaceBlock_GetResult_Event_info()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PlaceBlock_GetResult_Event_request info(::cobot_interfaces::action::PlaceBlock_GetResult_Event::_info_type arg)
  {
    msg_.info = std::move(arg);
    return Init_PlaceBlock_GetResult_Event_request(msg_);
  }

private:
  ::cobot_interfaces::action::PlaceBlock_GetResult_Event msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::cobot_interfaces::action::PlaceBlock_GetResult_Event>()
{
  return cobot_interfaces::action::builder::Init_PlaceBlock_GetResult_Event_info();
}

}  // namespace cobot_interfaces


namespace cobot_interfaces
{

namespace action
{

namespace builder
{

class Init_PlaceBlock_FeedbackMessage_feedback
{
public:
  explicit Init_PlaceBlock_FeedbackMessage_feedback(::cobot_interfaces::action::PlaceBlock_FeedbackMessage & msg)
  : msg_(msg)
  {}
  ::cobot_interfaces::action::PlaceBlock_FeedbackMessage feedback(::cobot_interfaces::action::PlaceBlock_FeedbackMessage::_feedback_type arg)
  {
    msg_.feedback = std::move(arg);
    return std::move(msg_);
  }

private:
  ::cobot_interfaces::action::PlaceBlock_FeedbackMessage msg_;
};

class Init_PlaceBlock_FeedbackMessage_goal_id
{
public:
  Init_PlaceBlock_FeedbackMessage_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_PlaceBlock_FeedbackMessage_feedback goal_id(::cobot_interfaces::action::PlaceBlock_FeedbackMessage::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_PlaceBlock_FeedbackMessage_feedback(msg_);
  }

private:
  ::cobot_interfaces::action::PlaceBlock_FeedbackMessage msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::cobot_interfaces::action::PlaceBlock_FeedbackMessage>()
{
  return cobot_interfaces::action::builder::Init_PlaceBlock_FeedbackMessage_goal_id();
}

}  // namespace cobot_interfaces

#endif  // COBOT_INTERFACES__ACTION__DETAIL__PLACE_BLOCK__BUILDER_HPP_
