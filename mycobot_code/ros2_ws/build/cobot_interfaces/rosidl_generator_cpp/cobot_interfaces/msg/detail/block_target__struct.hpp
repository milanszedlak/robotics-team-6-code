// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from cobot_interfaces:msg/BlockTarget.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cobot_interfaces/msg/block_target.hpp"


#ifndef COBOT_INTERFACES__MSG__DETAIL__BLOCK_TARGET__STRUCT_HPP_
#define COBOT_INTERFACES__MSG__DETAIL__BLOCK_TARGET__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"
// Member 'center'
// Member 'corners'
#include "geometry_msgs/msg/detail/point__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__cobot_interfaces__msg__BlockTarget __attribute__((deprecated))
#else
# define DEPRECATED__cobot_interfaces__msg__BlockTarget __declspec(deprecated)
#endif

namespace cobot_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct BlockTarget_
{
  using Type = BlockTarget_<ContainerAllocator>;

  explicit BlockTarget_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init),
    center(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->color = "";
      this->should_grasp = false;
      this->confidence = 0.0f;
      this->corners.fill(geometry_msgs::msg::Point_<ContainerAllocator>{_init});
    }
  }

  explicit BlockTarget_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    color(_alloc),
    center(_alloc, _init),
    corners(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->color = "";
      this->should_grasp = false;
      this->confidence = 0.0f;
      this->corners.fill(geometry_msgs::msg::Point_<ContainerAllocator>{_alloc, _init});
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _color_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _color_type color;
  using _should_grasp_type =
    bool;
  _should_grasp_type should_grasp;
  using _confidence_type =
    float;
  _confidence_type confidence;
  using _center_type =
    geometry_msgs::msg::Point_<ContainerAllocator>;
  _center_type center;
  using _corners_type =
    std::array<geometry_msgs::msg::Point_<ContainerAllocator>, 4>;
  _corners_type corners;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__color(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->color = _arg;
    return *this;
  }
  Type & set__should_grasp(
    const bool & _arg)
  {
    this->should_grasp = _arg;
    return *this;
  }
  Type & set__confidence(
    const float & _arg)
  {
    this->confidence = _arg;
    return *this;
  }
  Type & set__center(
    const geometry_msgs::msg::Point_<ContainerAllocator> & _arg)
  {
    this->center = _arg;
    return *this;
  }
  Type & set__corners(
    const std::array<geometry_msgs::msg::Point_<ContainerAllocator>, 4> & _arg)
  {
    this->corners = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    cobot_interfaces::msg::BlockTarget_<ContainerAllocator> *;
  using ConstRawPtr =
    const cobot_interfaces::msg::BlockTarget_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cobot_interfaces::msg::BlockTarget_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cobot_interfaces::msg::BlockTarget_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cobot_interfaces::msg::BlockTarget_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cobot_interfaces::msg::BlockTarget_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cobot_interfaces::msg::BlockTarget_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cobot_interfaces::msg::BlockTarget_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cobot_interfaces::msg::BlockTarget_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cobot_interfaces::msg::BlockTarget_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cobot_interfaces__msg__BlockTarget
    std::shared_ptr<cobot_interfaces::msg::BlockTarget_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cobot_interfaces__msg__BlockTarget
    std::shared_ptr<cobot_interfaces::msg::BlockTarget_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const BlockTarget_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->color != other.color) {
      return false;
    }
    if (this->should_grasp != other.should_grasp) {
      return false;
    }
    if (this->confidence != other.confidence) {
      return false;
    }
    if (this->center != other.center) {
      return false;
    }
    if (this->corners != other.corners) {
      return false;
    }
    return true;
  }
  bool operator!=(const BlockTarget_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct BlockTarget_

// alias to use template instance with default allocator
using BlockTarget =
  cobot_interfaces::msg::BlockTarget_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace cobot_interfaces

#endif  // COBOT_INTERFACES__MSG__DETAIL__BLOCK_TARGET__STRUCT_HPP_
