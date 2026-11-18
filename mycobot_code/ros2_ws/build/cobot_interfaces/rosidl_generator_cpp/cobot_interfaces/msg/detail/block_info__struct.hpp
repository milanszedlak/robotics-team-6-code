// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from cobot_interfaces:msg/BlockInfo.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cobot_interfaces/msg/block_info.hpp"


#ifndef COBOT_INTERFACES__MSG__DETAIL__BLOCK_INFO__STRUCT_HPP_
#define COBOT_INTERFACES__MSG__DETAIL__BLOCK_INFO__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'position'
#include "geometry_msgs/msg/detail/point__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__cobot_interfaces__msg__BlockInfo __attribute__((deprecated))
#else
# define DEPRECATED__cobot_interfaces__msg__BlockInfo __declspec(deprecated)
#endif

namespace cobot_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct BlockInfo_
{
  using Type = BlockInfo_<ContainerAllocator>;

  explicit BlockInfo_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : position(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->color = "";
      this->confidence = 0.0f;
      this->graspable = false;
      this->grasp_yaw = 0.0;
      this->width = 0.0;
    }
  }

  explicit BlockInfo_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : color(_alloc),
    position(_alloc, _init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->color = "";
      this->confidence = 0.0f;
      this->graspable = false;
      this->grasp_yaw = 0.0;
      this->width = 0.0;
    }
  }

  // field types and members
  using _color_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _color_type color;
  using _confidence_type =
    float;
  _confidence_type confidence;
  using _graspable_type =
    bool;
  _graspable_type graspable;
  using _position_type =
    geometry_msgs::msg::Point_<ContainerAllocator>;
  _position_type position;
  using _grasp_yaw_type =
    double;
  _grasp_yaw_type grasp_yaw;
  using _width_type =
    double;
  _width_type width;

  // setters for named parameter idiom
  Type & set__color(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->color = _arg;
    return *this;
  }
  Type & set__confidence(
    const float & _arg)
  {
    this->confidence = _arg;
    return *this;
  }
  Type & set__graspable(
    const bool & _arg)
  {
    this->graspable = _arg;
    return *this;
  }
  Type & set__position(
    const geometry_msgs::msg::Point_<ContainerAllocator> & _arg)
  {
    this->position = _arg;
    return *this;
  }
  Type & set__grasp_yaw(
    const double & _arg)
  {
    this->grasp_yaw = _arg;
    return *this;
  }
  Type & set__width(
    const double & _arg)
  {
    this->width = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    cobot_interfaces::msg::BlockInfo_<ContainerAllocator> *;
  using ConstRawPtr =
    const cobot_interfaces::msg::BlockInfo_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cobot_interfaces::msg::BlockInfo_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cobot_interfaces::msg::BlockInfo_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cobot_interfaces::msg::BlockInfo_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cobot_interfaces::msg::BlockInfo_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cobot_interfaces::msg::BlockInfo_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cobot_interfaces::msg::BlockInfo_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cobot_interfaces::msg::BlockInfo_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cobot_interfaces::msg::BlockInfo_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cobot_interfaces__msg__BlockInfo
    std::shared_ptr<cobot_interfaces::msg::BlockInfo_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cobot_interfaces__msg__BlockInfo
    std::shared_ptr<cobot_interfaces::msg::BlockInfo_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const BlockInfo_ & other) const
  {
    if (this->color != other.color) {
      return false;
    }
    if (this->confidence != other.confidence) {
      return false;
    }
    if (this->graspable != other.graspable) {
      return false;
    }
    if (this->position != other.position) {
      return false;
    }
    if (this->grasp_yaw != other.grasp_yaw) {
      return false;
    }
    if (this->width != other.width) {
      return false;
    }
    return true;
  }
  bool operator!=(const BlockInfo_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct BlockInfo_

// alias to use template instance with default allocator
using BlockInfo =
  cobot_interfaces::msg::BlockInfo_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace cobot_interfaces

#endif  // COBOT_INTERFACES__MSG__DETAIL__BLOCK_INFO__STRUCT_HPP_
