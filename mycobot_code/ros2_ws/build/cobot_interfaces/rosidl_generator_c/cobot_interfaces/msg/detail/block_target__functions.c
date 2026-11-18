// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from cobot_interfaces:msg/BlockTarget.idl
// generated code does not contain a copyright notice
#include "cobot_interfaces/msg/detail/block_target__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `color`
#include "rosidl_runtime_c/string_functions.h"
// Member `center`
// Member `corners`
#include "geometry_msgs/msg/detail/point__functions.h"

bool
cobot_interfaces__msg__BlockTarget__init(cobot_interfaces__msg__BlockTarget * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    cobot_interfaces__msg__BlockTarget__fini(msg);
    return false;
  }
  // color
  if (!rosidl_runtime_c__String__init(&msg->color)) {
    cobot_interfaces__msg__BlockTarget__fini(msg);
    return false;
  }
  // should_grasp
  // confidence
  // center
  if (!geometry_msgs__msg__Point__init(&msg->center)) {
    cobot_interfaces__msg__BlockTarget__fini(msg);
    return false;
  }
  // corners
  for (size_t i = 0; i < 4; ++i) {
    if (!geometry_msgs__msg__Point__init(&msg->corners[i])) {
      cobot_interfaces__msg__BlockTarget__fini(msg);
      return false;
    }
  }
  return true;
}

void
cobot_interfaces__msg__BlockTarget__fini(cobot_interfaces__msg__BlockTarget * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // color
  rosidl_runtime_c__String__fini(&msg->color);
  // should_grasp
  // confidence
  // center
  geometry_msgs__msg__Point__fini(&msg->center);
  // corners
  for (size_t i = 0; i < 4; ++i) {
    geometry_msgs__msg__Point__fini(&msg->corners[i]);
  }
}

bool
cobot_interfaces__msg__BlockTarget__are_equal(const cobot_interfaces__msg__BlockTarget * lhs, const cobot_interfaces__msg__BlockTarget * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__are_equal(
      &(lhs->header), &(rhs->header)))
  {
    return false;
  }
  // color
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->color), &(rhs->color)))
  {
    return false;
  }
  // should_grasp
  if (lhs->should_grasp != rhs->should_grasp) {
    return false;
  }
  // confidence
  if (lhs->confidence != rhs->confidence) {
    return false;
  }
  // center
  if (!geometry_msgs__msg__Point__are_equal(
      &(lhs->center), &(rhs->center)))
  {
    return false;
  }
  // corners
  for (size_t i = 0; i < 4; ++i) {
    if (!geometry_msgs__msg__Point__are_equal(
        &(lhs->corners[i]), &(rhs->corners[i])))
    {
      return false;
    }
  }
  return true;
}

bool
cobot_interfaces__msg__BlockTarget__copy(
  const cobot_interfaces__msg__BlockTarget * input,
  cobot_interfaces__msg__BlockTarget * output)
{
  if (!input || !output) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__copy(
      &(input->header), &(output->header)))
  {
    return false;
  }
  // color
  if (!rosidl_runtime_c__String__copy(
      &(input->color), &(output->color)))
  {
    return false;
  }
  // should_grasp
  output->should_grasp = input->should_grasp;
  // confidence
  output->confidence = input->confidence;
  // center
  if (!geometry_msgs__msg__Point__copy(
      &(input->center), &(output->center)))
  {
    return false;
  }
  // corners
  for (size_t i = 0; i < 4; ++i) {
    if (!geometry_msgs__msg__Point__copy(
        &(input->corners[i]), &(output->corners[i])))
    {
      return false;
    }
  }
  return true;
}

cobot_interfaces__msg__BlockTarget *
cobot_interfaces__msg__BlockTarget__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot_interfaces__msg__BlockTarget * msg = (cobot_interfaces__msg__BlockTarget *)allocator.allocate(sizeof(cobot_interfaces__msg__BlockTarget), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(cobot_interfaces__msg__BlockTarget));
  bool success = cobot_interfaces__msg__BlockTarget__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
cobot_interfaces__msg__BlockTarget__destroy(cobot_interfaces__msg__BlockTarget * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    cobot_interfaces__msg__BlockTarget__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
cobot_interfaces__msg__BlockTarget__Sequence__init(cobot_interfaces__msg__BlockTarget__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot_interfaces__msg__BlockTarget * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(cobot_interfaces__msg__BlockTarget)) {
      return false;
    }
    data = (cobot_interfaces__msg__BlockTarget *)allocator.zero_allocate(size, sizeof(cobot_interfaces__msg__BlockTarget), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = cobot_interfaces__msg__BlockTarget__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        cobot_interfaces__msg__BlockTarget__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
cobot_interfaces__msg__BlockTarget__Sequence__fini(cobot_interfaces__msg__BlockTarget__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      cobot_interfaces__msg__BlockTarget__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

cobot_interfaces__msg__BlockTarget__Sequence *
cobot_interfaces__msg__BlockTarget__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot_interfaces__msg__BlockTarget__Sequence * array = (cobot_interfaces__msg__BlockTarget__Sequence *)allocator.allocate(sizeof(cobot_interfaces__msg__BlockTarget__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = cobot_interfaces__msg__BlockTarget__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
cobot_interfaces__msg__BlockTarget__Sequence__destroy(cobot_interfaces__msg__BlockTarget__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    cobot_interfaces__msg__BlockTarget__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
cobot_interfaces__msg__BlockTarget__Sequence__are_equal(const cobot_interfaces__msg__BlockTarget__Sequence * lhs, const cobot_interfaces__msg__BlockTarget__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!cobot_interfaces__msg__BlockTarget__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
cobot_interfaces__msg__BlockTarget__Sequence__copy(
  const cobot_interfaces__msg__BlockTarget__Sequence * input,
  cobot_interfaces__msg__BlockTarget__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(cobot_interfaces__msg__BlockTarget)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(cobot_interfaces__msg__BlockTarget);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    cobot_interfaces__msg__BlockTarget * data =
      (cobot_interfaces__msg__BlockTarget *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!cobot_interfaces__msg__BlockTarget__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          cobot_interfaces__msg__BlockTarget__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!cobot_interfaces__msg__BlockTarget__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
