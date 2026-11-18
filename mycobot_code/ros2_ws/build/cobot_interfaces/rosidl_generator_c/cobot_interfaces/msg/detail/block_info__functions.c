// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from cobot_interfaces:msg/BlockInfo.idl
// generated code does not contain a copyright notice
#include "cobot_interfaces/msg/detail/block_info__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `color`
#include "rosidl_runtime_c/string_functions.h"
// Member `position`
#include "geometry_msgs/msg/detail/point__functions.h"

bool
cobot_interfaces__msg__BlockInfo__init(cobot_interfaces__msg__BlockInfo * msg)
{
  if (!msg) {
    return false;
  }
  // color
  if (!rosidl_runtime_c__String__init(&msg->color)) {
    cobot_interfaces__msg__BlockInfo__fini(msg);
    return false;
  }
  // confidence
  // graspable
  // position
  if (!geometry_msgs__msg__Point__init(&msg->position)) {
    cobot_interfaces__msg__BlockInfo__fini(msg);
    return false;
  }
  // grasp_yaw
  // width
  return true;
}

void
cobot_interfaces__msg__BlockInfo__fini(cobot_interfaces__msg__BlockInfo * msg)
{
  if (!msg) {
    return;
  }
  // color
  rosidl_runtime_c__String__fini(&msg->color);
  // confidence
  // graspable
  // position
  geometry_msgs__msg__Point__fini(&msg->position);
  // grasp_yaw
  // width
}

bool
cobot_interfaces__msg__BlockInfo__are_equal(const cobot_interfaces__msg__BlockInfo * lhs, const cobot_interfaces__msg__BlockInfo * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // color
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->color), &(rhs->color)))
  {
    return false;
  }
  // confidence
  if (lhs->confidence != rhs->confidence) {
    return false;
  }
  // graspable
  if (lhs->graspable != rhs->graspable) {
    return false;
  }
  // position
  if (!geometry_msgs__msg__Point__are_equal(
      &(lhs->position), &(rhs->position)))
  {
    return false;
  }
  // grasp_yaw
  if (lhs->grasp_yaw != rhs->grasp_yaw) {
    return false;
  }
  // width
  if (lhs->width != rhs->width) {
    return false;
  }
  return true;
}

bool
cobot_interfaces__msg__BlockInfo__copy(
  const cobot_interfaces__msg__BlockInfo * input,
  cobot_interfaces__msg__BlockInfo * output)
{
  if (!input || !output) {
    return false;
  }
  // color
  if (!rosidl_runtime_c__String__copy(
      &(input->color), &(output->color)))
  {
    return false;
  }
  // confidence
  output->confidence = input->confidence;
  // graspable
  output->graspable = input->graspable;
  // position
  if (!geometry_msgs__msg__Point__copy(
      &(input->position), &(output->position)))
  {
    return false;
  }
  // grasp_yaw
  output->grasp_yaw = input->grasp_yaw;
  // width
  output->width = input->width;
  return true;
}

cobot_interfaces__msg__BlockInfo *
cobot_interfaces__msg__BlockInfo__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot_interfaces__msg__BlockInfo * msg = (cobot_interfaces__msg__BlockInfo *)allocator.allocate(sizeof(cobot_interfaces__msg__BlockInfo), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(cobot_interfaces__msg__BlockInfo));
  bool success = cobot_interfaces__msg__BlockInfo__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
cobot_interfaces__msg__BlockInfo__destroy(cobot_interfaces__msg__BlockInfo * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    cobot_interfaces__msg__BlockInfo__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
cobot_interfaces__msg__BlockInfo__Sequence__init(cobot_interfaces__msg__BlockInfo__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot_interfaces__msg__BlockInfo * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(cobot_interfaces__msg__BlockInfo)) {
      return false;
    }
    data = (cobot_interfaces__msg__BlockInfo *)allocator.zero_allocate(size, sizeof(cobot_interfaces__msg__BlockInfo), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = cobot_interfaces__msg__BlockInfo__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        cobot_interfaces__msg__BlockInfo__fini(&data[i - 1]);
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
cobot_interfaces__msg__BlockInfo__Sequence__fini(cobot_interfaces__msg__BlockInfo__Sequence * array)
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
      cobot_interfaces__msg__BlockInfo__fini(&array->data[i]);
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

cobot_interfaces__msg__BlockInfo__Sequence *
cobot_interfaces__msg__BlockInfo__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot_interfaces__msg__BlockInfo__Sequence * array = (cobot_interfaces__msg__BlockInfo__Sequence *)allocator.allocate(sizeof(cobot_interfaces__msg__BlockInfo__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = cobot_interfaces__msg__BlockInfo__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
cobot_interfaces__msg__BlockInfo__Sequence__destroy(cobot_interfaces__msg__BlockInfo__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    cobot_interfaces__msg__BlockInfo__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
cobot_interfaces__msg__BlockInfo__Sequence__are_equal(const cobot_interfaces__msg__BlockInfo__Sequence * lhs, const cobot_interfaces__msg__BlockInfo__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!cobot_interfaces__msg__BlockInfo__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
cobot_interfaces__msg__BlockInfo__Sequence__copy(
  const cobot_interfaces__msg__BlockInfo__Sequence * input,
  cobot_interfaces__msg__BlockInfo__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(cobot_interfaces__msg__BlockInfo)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(cobot_interfaces__msg__BlockInfo);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    cobot_interfaces__msg__BlockInfo * data =
      (cobot_interfaces__msg__BlockInfo *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!cobot_interfaces__msg__BlockInfo__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          cobot_interfaces__msg__BlockInfo__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!cobot_interfaces__msg__BlockInfo__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
