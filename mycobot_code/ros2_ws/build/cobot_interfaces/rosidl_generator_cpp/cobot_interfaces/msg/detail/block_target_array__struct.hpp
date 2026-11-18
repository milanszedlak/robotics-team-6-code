// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from cobot_interfaces:msg/BlockTargetArray.idl
// generated code does not contain a copyright notice

// IWYU pragma: private, include "cobot_interfaces/msg/block_target_array.hpp"


#ifndef COBOT_INTERFACES__MSG__DETAIL__BLOCK_TARGET_ARRAY__STRUCT_HPP_
#define COBOT_INTERFACES__MSG__DETAIL__BLOCK_TARGET_ARRAY__STRUCT_HPP_

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
// Member 'blocks'
#include "cobot_interfaces/msg/detail/block_target__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__cobot_interfaces__msg__BlockTargetArray __attribute__((deprecated))
#else
# define DEPRECATED__cobot_interfaces__msg__BlockTargetArray __declspec(deprecated)
#endif

namespace cobot_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct BlockTargetArray_
{
  using Type = BlockTargetArray_<ContainerAllocator>;

  explicit BlockTargetArray_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    (void)_init;
  }

  explicit BlockTargetArray_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init)
  {
    (void)_init;
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _blocks_type =
    std::vector<cobot_interfaces::msg::BlockTarget_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<cobot_interfaces::msg::BlockTarget_<ContainerAllocator>>>;
  _blocks_type blocks;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__blocks(
    const std::vector<cobot_interfaces::msg::BlockTarget_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<cobot_interfaces::msg::BlockTarget_<ContainerAllocator>>> & _arg)
  {
    this->blocks = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    cobot_interfaces::msg::BlockTargetArray_<ContainerAllocator> *;
  using ConstRawPtr =
    const cobot_interfaces::msg::BlockTargetArray_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<cobot_interfaces::msg::BlockTargetArray_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<cobot_interfaces::msg::BlockTargetArray_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      cobot_interfaces::msg::BlockTargetArray_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<cobot_interfaces::msg::BlockTargetArray_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      cobot_interfaces::msg::BlockTargetArray_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<cobot_interfaces::msg::BlockTargetArray_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<cobot_interfaces::msg::BlockTargetArray_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<cobot_interfaces::msg::BlockTargetArray_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__cobot_interfaces__msg__BlockTargetArray
    std::shared_ptr<cobot_interfaces::msg::BlockTargetArray_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__cobot_interfaces__msg__BlockTargetArray
    std::shared_ptr<cobot_interfaces::msg::BlockTargetArray_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const BlockTargetArray_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->blocks != other.blocks) {
      return false;
    }
    return true;
  }
  bool operator!=(const BlockTargetArray_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct BlockTargetArray_

// alias to use template instance with default allocator
using BlockTargetArray =
  cobot_interfaces::msg::BlockTargetArray_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace cobot_interfaces

#endif  // COBOT_INTERFACES__MSG__DETAIL__BLOCK_TARGET_ARRAY__STRUCT_HPP_
