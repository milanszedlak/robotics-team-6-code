// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from cobot_interfaces:msg/BlockTargetArray.idl
// generated code does not contain a copyright notice
#include "cobot_interfaces/msg/detail/block_target_array__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `blocks`
#include "cobot_interfaces/msg/detail/block_target__functions.h"

bool
cobot_interfaces__msg__BlockTargetArray__init(cobot_interfaces__msg__BlockTargetArray * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    cobot_interfaces__msg__BlockTargetArray__fini(msg);
    return false;
  }
  // blocks
  if (!cobot_interfaces__msg__BlockTarget__Sequence__init(&msg->blocks, 0)) {
    cobot_interfaces__msg__BlockTargetArray__fini(msg);
    return false;
  }
  return true;
}

void
cobot_interfaces__msg__BlockTargetArray__fini(cobot_interfaces__msg__BlockTargetArray * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // blocks
  cobot_interfaces__msg__BlockTarget__Sequence__fini(&msg->blocks);
}

bool
cobot_interfaces__msg__BlockTargetArray__are_equal(const cobot_interfaces__msg__BlockTargetArray * lhs, const cobot_interfaces__msg__BlockTargetArray * rhs)
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
  // blocks
  if (!cobot_interfaces__msg__BlockTarget__Sequence__are_equal(
      &(lhs->blocks), &(rhs->blocks)))
  {
    return false;
  }
  return true;
}

bool
cobot_interfaces__msg__BlockTargetArray__copy(
  const cobot_interfaces__msg__BlockTargetArray * input,
  cobot_interfaces__msg__BlockTargetArray * output)
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
  // blocks
  if (!cobot_interfaces__msg__BlockTarget__Sequence__copy(
      &(input->blocks), &(output->blocks)))
  {
    return false;
  }
  return true;
}

cobot_interfaces__msg__BlockTargetArray *
cobot_interfaces__msg__BlockTargetArray__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot_interfaces__msg__BlockTargetArray * msg = (cobot_interfaces__msg__BlockTargetArray *)allocator.allocate(sizeof(cobot_interfaces__msg__BlockTargetArray), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(cobot_interfaces__msg__BlockTargetArray));
  bool success = cobot_interfaces__msg__BlockTargetArray__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
cobot_interfaces__msg__BlockTargetArray__destroy(cobot_interfaces__msg__BlockTargetArray * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    cobot_interfaces__msg__BlockTargetArray__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
cobot_interfaces__msg__BlockTargetArray__Sequence__init(cobot_interfaces__msg__BlockTargetArray__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot_interfaces__msg__BlockTargetArray * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(cobot_interfaces__msg__BlockTargetArray)) {
      return false;
    }
    data = (cobot_interfaces__msg__BlockTargetArray *)allocator.zero_allocate(size, sizeof(cobot_interfaces__msg__BlockTargetArray), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = cobot_interfaces__msg__BlockTargetArray__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        cobot_interfaces__msg__BlockTargetArray__fini(&data[i - 1]);
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
cobot_interfaces__msg__BlockTargetArray__Sequence__fini(cobot_interfaces__msg__BlockTargetArray__Sequence * array)
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
      cobot_interfaces__msg__BlockTargetArray__fini(&array->data[i]);
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

cobot_interfaces__msg__BlockTargetArray__Sequence *
cobot_interfaces__msg__BlockTargetArray__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot_interfaces__msg__BlockTargetArray__Sequence * array = (cobot_interfaces__msg__BlockTargetArray__Sequence *)allocator.allocate(sizeof(cobot_interfaces__msg__BlockTargetArray__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = cobot_interfaces__msg__BlockTargetArray__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
cobot_interfaces__msg__BlockTargetArray__Sequence__destroy(cobot_interfaces__msg__BlockTargetArray__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    cobot_interfaces__msg__BlockTargetArray__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
cobot_interfaces__msg__BlockTargetArray__Sequence__are_equal(const cobot_interfaces__msg__BlockTargetArray__Sequence * lhs, const cobot_interfaces__msg__BlockTargetArray__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!cobot_interfaces__msg__BlockTargetArray__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
cobot_interfaces__msg__BlockTargetArray__Sequence__copy(
  const cobot_interfaces__msg__BlockTargetArray__Sequence * input,
  cobot_interfaces__msg__BlockTargetArray__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(cobot_interfaces__msg__BlockTargetArray)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(cobot_interfaces__msg__BlockTargetArray);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    cobot_interfaces__msg__BlockTargetArray * data =
      (cobot_interfaces__msg__BlockTargetArray *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!cobot_interfaces__msg__BlockTargetArray__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          cobot_interfaces__msg__BlockTargetArray__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!cobot_interfaces__msg__BlockTargetArray__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
