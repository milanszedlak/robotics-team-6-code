// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from cobot_interfaces:srv/LocateBlocks.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cobot_interfaces/srv/locate_blocks.hpp"


#ifndef COBOT_INTERFACES__SRV__DETAIL__LOCATE_BLOCKS__TRAITS_HPP_
#define COBOT_INTERFACES__SRV__DETAIL__LOCATE_BLOCKS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "cobot_interfaces/srv/detail/locate_blocks__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace cobot_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const LocateBlocks_Request & msg,
  std::ostream & out)
{
  out << "{";
  // member: color
  {
    out << "color: ";
    rosidl_generator_traits::value_to_yaml(msg.color, out);
    out << ", ";
  }

  // member: go_home
  {
    out << "go_home: ";
    rosidl_generator_traits::value_to_yaml(msg.go_home, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const LocateBlocks_Request & msg,
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

  // member: go_home
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "go_home: ";
    rosidl_generator_traits::value_to_yaml(msg.go_home, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LocateBlocks_Request & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace cobot_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use cobot_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const cobot_interfaces::srv::LocateBlocks_Request & msg,
  std::ostream & out, size_t indentation = 0)
{
  cobot_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use cobot_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const cobot_interfaces::srv::LocateBlocks_Request & msg)
{
  return cobot_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<cobot_interfaces::srv::LocateBlocks_Request>()
{
  return "cobot_interfaces::srv::LocateBlocks_Request";
}

template<>
inline const char * name<cobot_interfaces::srv::LocateBlocks_Request>()
{
  return "cobot_interfaces/srv/LocateBlocks_Request";
}

template<>
struct has_fixed_size<cobot_interfaces::srv::LocateBlocks_Request>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<cobot_interfaces::srv::LocateBlocks_Request>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<cobot_interfaces::srv::LocateBlocks_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'blocks'
#include "cobot_interfaces/msg/detail/block_info__traits.hpp"

namespace cobot_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const LocateBlocks_Response & msg,
  std::ostream & out)
{
  out << "{";
  // member: success
  {
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << ", ";
  }

  // member: message
  {
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
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
  const LocateBlocks_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: success
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "success: ";
    rosidl_generator_traits::value_to_yaml(msg.success, out);
    out << "\n";
  }

  // member: message
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "message: ";
    rosidl_generator_traits::value_to_yaml(msg.message, out);
    out << "\n";
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

inline std::string to_yaml(const LocateBlocks_Response & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace cobot_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use cobot_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const cobot_interfaces::srv::LocateBlocks_Response & msg,
  std::ostream & out, size_t indentation = 0)
{
  cobot_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use cobot_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const cobot_interfaces::srv::LocateBlocks_Response & msg)
{
  return cobot_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<cobot_interfaces::srv::LocateBlocks_Response>()
{
  return "cobot_interfaces::srv::LocateBlocks_Response";
}

template<>
inline const char * name<cobot_interfaces::srv::LocateBlocks_Response>()
{
  return "cobot_interfaces/srv/LocateBlocks_Response";
}

template<>
struct has_fixed_size<cobot_interfaces::srv::LocateBlocks_Response>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<cobot_interfaces::srv::LocateBlocks_Response>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<cobot_interfaces::srv::LocateBlocks_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

// Include directives for member types
// Member 'info'
#include "service_msgs/msg/detail/service_event_info__traits.hpp"

namespace cobot_interfaces
{

namespace srv
{

inline void to_flow_style_yaml(
  const LocateBlocks_Event & msg,
  std::ostream & out)
{
  out << "{";
  // member: info
  {
    out << "info: ";
    to_flow_style_yaml(msg.info, out);
    out << ", ";
  }

  // member: request
  {
    if (msg.request.size() == 0) {
      out << "request: []";
    } else {
      out << "request: [";
      size_t pending_items = msg.request.size();
      for (auto item : msg.request) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: response
  {
    if (msg.response.size() == 0) {
      out << "response: []";
    } else {
      out << "response: [";
      size_t pending_items = msg.response.size();
      for (auto item : msg.response) {
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
  const LocateBlocks_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: info
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "info:\n";
    to_block_style_yaml(msg.info, out, indentation + 2);
  }

  // member: request
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.request.size() == 0) {
      out << "request: []\n";
    } else {
      out << "request:\n";
      for (auto item : msg.request) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }

  // member: response
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.response.size() == 0) {
      out << "response: []\n";
    } else {
      out << "response:\n";
      for (auto item : msg.response) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const LocateBlocks_Event & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace srv

}  // namespace cobot_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use cobot_interfaces::srv::to_block_style_yaml() instead")]]
inline void to_yaml(
  const cobot_interfaces::srv::LocateBlocks_Event & msg,
  std::ostream & out, size_t indentation = 0)
{
  cobot_interfaces::srv::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use cobot_interfaces::srv::to_yaml() instead")]]
inline std::string to_yaml(const cobot_interfaces::srv::LocateBlocks_Event & msg)
{
  return cobot_interfaces::srv::to_yaml(msg);
}

template<>
inline const char * data_type<cobot_interfaces::srv::LocateBlocks_Event>()
{
  return "cobot_interfaces::srv::LocateBlocks_Event";
}

template<>
inline const char * name<cobot_interfaces::srv::LocateBlocks_Event>()
{
  return "cobot_interfaces/srv/LocateBlocks_Event";
}

template<>
struct has_fixed_size<cobot_interfaces::srv::LocateBlocks_Event>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<cobot_interfaces::srv::LocateBlocks_Event>
  : std::integral_constant<bool, has_bounded_size<cobot_interfaces::srv::LocateBlocks_Request>::value && has_bounded_size<cobot_interfaces::srv::LocateBlocks_Response>::value && has_bounded_size<service_msgs::msg::ServiceEventInfo>::value> {};

template<>
struct is_message<cobot_interfaces::srv::LocateBlocks_Event>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<cobot_interfaces::srv::LocateBlocks>()
{
  return "cobot_interfaces::srv::LocateBlocks";
}

template<>
inline const char * name<cobot_interfaces::srv::LocateBlocks>()
{
  return "cobot_interfaces/srv/LocateBlocks";
}

template<>
struct has_fixed_size<cobot_interfaces::srv::LocateBlocks>
  : std::integral_constant<
    bool,
    has_fixed_size<cobot_interfaces::srv::LocateBlocks_Request>::value &&
    has_fixed_size<cobot_interfaces::srv::LocateBlocks_Response>::value
  >
{
};

template<>
struct has_bounded_size<cobot_interfaces::srv::LocateBlocks>
  : std::integral_constant<
    bool,
    has_bounded_size<cobot_interfaces::srv::LocateBlocks_Request>::value &&
    has_bounded_size<cobot_interfaces::srv::LocateBlocks_Response>::value
  >
{
};

template<>
struct is_service<cobot_interfaces::srv::LocateBlocks>
  : std::true_type
{
};

template<>
struct is_service_request<cobot_interfaces::srv::LocateBlocks_Request>
  : std::true_type
{
};

template<>
struct is_service_response<cobot_interfaces::srv::LocateBlocks_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // COBOT_INTERFACES__SRV__DETAIL__LOCATE_BLOCKS__TRAITS_HPP_
