// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from cobot_interfaces:action/PlaceBlock.idl
// generated code does not contain a copyright notice
#include "cobot_interfaces/action/detail/place_block__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


// Include directives for member types
// Member `location`
#include "rosidl_runtime_c/string_functions.h"
// Member `position`
#include "geometry_msgs/msg/detail/point__functions.h"

bool
cobot_interfaces__action__PlaceBlock_Goal__init(cobot_interfaces__action__PlaceBlock_Goal * msg)
{
  if (!msg) {
    return false;
  }
  // location
  if (!rosidl_runtime_c__String__init(&msg->location)) {
    cobot_interfaces__action__PlaceBlock_Goal__fini(msg);
    return false;
  }
  // use_position
  // position
  if (!geometry_msgs__msg__Point__init(&msg->position)) {
    cobot_interfaces__action__PlaceBlock_Goal__fini(msg);
    return false;
  }
  return true;
}

void
cobot_interfaces__action__PlaceBlock_Goal__fini(cobot_interfaces__action__PlaceBlock_Goal * msg)
{
  if (!msg) {
    return;
  }
  // location
  rosidl_runtime_c__String__fini(&msg->location);
  // use_position
  // position
  geometry_msgs__msg__Point__fini(&msg->position);
}

bool
cobot_interfaces__action__PlaceBlock_Goal__are_equal(const cobot_interfaces__action__PlaceBlock_Goal * lhs, const cobot_interfaces__action__PlaceBlock_Goal * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // location
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->location), &(rhs->location)))
  {
    return false;
  }
  // use_position
  if (lhs->use_position != rhs->use_position) {
    return false;
  }
  // position
  if (!geometry_msgs__msg__Point__are_equal(
      &(lhs->position), &(rhs->position)))
  {
    return false;
  }
  return true;
}

bool
cobot_interfaces__action__PlaceBlock_Goal__copy(
  const cobot_interfaces__action__PlaceBlock_Goal * input,
  cobot_interfaces__action__PlaceBlock_Goal * output)
{
  if (!input || !output) {
    return false;
  }
  // location
  if (!rosidl_runtime_c__String__copy(
      &(input->location), &(output->location)))
  {
    return false;
  }
  // use_position
  output->use_position = input->use_position;
  // position
  if (!geometry_msgs__msg__Point__copy(
      &(input->position), &(output->position)))
  {
    return false;
  }
  return true;
}

cobot_interfaces__action__PlaceBlock_Goal *
cobot_interfaces__action__PlaceBlock_Goal__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot_interfaces__action__PlaceBlock_Goal * msg = (cobot_interfaces__action__PlaceBlock_Goal *)allocator.allocate(sizeof(cobot_interfaces__action__PlaceBlock_Goal), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(cobot_interfaces__action__PlaceBlock_Goal));
  bool success = cobot_interfaces__action__PlaceBlock_Goal__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
cobot_interfaces__action__PlaceBlock_Goal__destroy(cobot_interfaces__action__PlaceBlock_Goal * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    cobot_interfaces__action__PlaceBlock_Goal__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
cobot_interfaces__action__PlaceBlock_Goal__Sequence__init(cobot_interfaces__action__PlaceBlock_Goal__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot_interfaces__action__PlaceBlock_Goal * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(cobot_interfaces__action__PlaceBlock_Goal)) {
      return false;
    }
    data = (cobot_interfaces__action__PlaceBlock_Goal *)allocator.zero_allocate(size, sizeof(cobot_interfaces__action__PlaceBlock_Goal), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = cobot_interfaces__action__PlaceBlock_Goal__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        cobot_interfaces__action__PlaceBlock_Goal__fini(&data[i - 1]);
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
cobot_interfaces__action__PlaceBlock_Goal__Sequence__fini(cobot_interfaces__action__PlaceBlock_Goal__Sequence * array)
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
      cobot_interfaces__action__PlaceBlock_Goal__fini(&array->data[i]);
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

cobot_interfaces__action__PlaceBlock_Goal__Sequence *
cobot_interfaces__action__PlaceBlock_Goal__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot_interfaces__action__PlaceBlock_Goal__Sequence * array = (cobot_interfaces__action__PlaceBlock_Goal__Sequence *)allocator.allocate(sizeof(cobot_interfaces__action__PlaceBlock_Goal__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = cobot_interfaces__action__PlaceBlock_Goal__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
cobot_interfaces__action__PlaceBlock_Goal__Sequence__destroy(cobot_interfaces__action__PlaceBlock_Goal__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    cobot_interfaces__action__PlaceBlock_Goal__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
cobot_interfaces__action__PlaceBlock_Goal__Sequence__are_equal(const cobot_interfaces__action__PlaceBlock_Goal__Sequence * lhs, const cobot_interfaces__action__PlaceBlock_Goal__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!cobot_interfaces__action__PlaceBlock_Goal__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
cobot_interfaces__action__PlaceBlock_Goal__Sequence__copy(
  const cobot_interfaces__action__PlaceBlock_Goal__Sequence * input,
  cobot_interfaces__action__PlaceBlock_Goal__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(cobot_interfaces__action__PlaceBlock_Goal)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(cobot_interfaces__action__PlaceBlock_Goal);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    cobot_interfaces__action__PlaceBlock_Goal * data =
      (cobot_interfaces__action__PlaceBlock_Goal *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!cobot_interfaces__action__PlaceBlock_Goal__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          cobot_interfaces__action__PlaceBlock_Goal__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!cobot_interfaces__action__PlaceBlock_Goal__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `message`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

bool
cobot_interfaces__action__PlaceBlock_Result__init(cobot_interfaces__action__PlaceBlock_Result * msg)
{
  if (!msg) {
    return false;
  }
  // success
  // message
  if (!rosidl_runtime_c__String__init(&msg->message)) {
    cobot_interfaces__action__PlaceBlock_Result__fini(msg);
    return false;
  }
  return true;
}

void
cobot_interfaces__action__PlaceBlock_Result__fini(cobot_interfaces__action__PlaceBlock_Result * msg)
{
  if (!msg) {
    return;
  }
  // success
  // message
  rosidl_runtime_c__String__fini(&msg->message);
}

bool
cobot_interfaces__action__PlaceBlock_Result__are_equal(const cobot_interfaces__action__PlaceBlock_Result * lhs, const cobot_interfaces__action__PlaceBlock_Result * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // success
  if (lhs->success != rhs->success) {
    return false;
  }
  // message
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->message), &(rhs->message)))
  {
    return false;
  }
  return true;
}

bool
cobot_interfaces__action__PlaceBlock_Result__copy(
  const cobot_interfaces__action__PlaceBlock_Result * input,
  cobot_interfaces__action__PlaceBlock_Result * output)
{
  if (!input || !output) {
    return false;
  }
  // success
  output->success = input->success;
  // message
  if (!rosidl_runtime_c__String__copy(
      &(input->message), &(output->message)))
  {
    return false;
  }
  return true;
}

cobot_interfaces__action__PlaceBlock_Result *
cobot_interfaces__action__PlaceBlock_Result__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot_interfaces__action__PlaceBlock_Result * msg = (cobot_interfaces__action__PlaceBlock_Result *)allocator.allocate(sizeof(cobot_interfaces__action__PlaceBlock_Result), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(cobot_interfaces__action__PlaceBlock_Result));
  bool success = cobot_interfaces__action__PlaceBlock_Result__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
cobot_interfaces__action__PlaceBlock_Result__destroy(cobot_interfaces__action__PlaceBlock_Result * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    cobot_interfaces__action__PlaceBlock_Result__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
cobot_interfaces__action__PlaceBlock_Result__Sequence__init(cobot_interfaces__action__PlaceBlock_Result__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot_interfaces__action__PlaceBlock_Result * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(cobot_interfaces__action__PlaceBlock_Result)) {
      return false;
    }
    data = (cobot_interfaces__action__PlaceBlock_Result *)allocator.zero_allocate(size, sizeof(cobot_interfaces__action__PlaceBlock_Result), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = cobot_interfaces__action__PlaceBlock_Result__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        cobot_interfaces__action__PlaceBlock_Result__fini(&data[i - 1]);
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
cobot_interfaces__action__PlaceBlock_Result__Sequence__fini(cobot_interfaces__action__PlaceBlock_Result__Sequence * array)
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
      cobot_interfaces__action__PlaceBlock_Result__fini(&array->data[i]);
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

cobot_interfaces__action__PlaceBlock_Result__Sequence *
cobot_interfaces__action__PlaceBlock_Result__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot_interfaces__action__PlaceBlock_Result__Sequence * array = (cobot_interfaces__action__PlaceBlock_Result__Sequence *)allocator.allocate(sizeof(cobot_interfaces__action__PlaceBlock_Result__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = cobot_interfaces__action__PlaceBlock_Result__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
cobot_interfaces__action__PlaceBlock_Result__Sequence__destroy(cobot_interfaces__action__PlaceBlock_Result__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    cobot_interfaces__action__PlaceBlock_Result__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
cobot_interfaces__action__PlaceBlock_Result__Sequence__are_equal(const cobot_interfaces__action__PlaceBlock_Result__Sequence * lhs, const cobot_interfaces__action__PlaceBlock_Result__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!cobot_interfaces__action__PlaceBlock_Result__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
cobot_interfaces__action__PlaceBlock_Result__Sequence__copy(
  const cobot_interfaces__action__PlaceBlock_Result__Sequence * input,
  cobot_interfaces__action__PlaceBlock_Result__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(cobot_interfaces__action__PlaceBlock_Result)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(cobot_interfaces__action__PlaceBlock_Result);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    cobot_interfaces__action__PlaceBlock_Result * data =
      (cobot_interfaces__action__PlaceBlock_Result *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!cobot_interfaces__action__PlaceBlock_Result__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          cobot_interfaces__action__PlaceBlock_Result__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!cobot_interfaces__action__PlaceBlock_Result__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `stage`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

bool
cobot_interfaces__action__PlaceBlock_Feedback__init(cobot_interfaces__action__PlaceBlock_Feedback * msg)
{
  if (!msg) {
    return false;
  }
  // stage
  if (!rosidl_runtime_c__String__init(&msg->stage)) {
    cobot_interfaces__action__PlaceBlock_Feedback__fini(msg);
    return false;
  }
  return true;
}

void
cobot_interfaces__action__PlaceBlock_Feedback__fini(cobot_interfaces__action__PlaceBlock_Feedback * msg)
{
  if (!msg) {
    return;
  }
  // stage
  rosidl_runtime_c__String__fini(&msg->stage);
}

bool
cobot_interfaces__action__PlaceBlock_Feedback__are_equal(const cobot_interfaces__action__PlaceBlock_Feedback * lhs, const cobot_interfaces__action__PlaceBlock_Feedback * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // stage
  if (!rosidl_runtime_c__String__are_equal(
      &(lhs->stage), &(rhs->stage)))
  {
    return false;
  }
  return true;
}

bool
cobot_interfaces__action__PlaceBlock_Feedback__copy(
  const cobot_interfaces__action__PlaceBlock_Feedback * input,
  cobot_interfaces__action__PlaceBlock_Feedback * output)
{
  if (!input || !output) {
    return false;
  }
  // stage
  if (!rosidl_runtime_c__String__copy(
      &(input->stage), &(output->stage)))
  {
    return false;
  }
  return true;
}

cobot_interfaces__action__PlaceBlock_Feedback *
cobot_interfaces__action__PlaceBlock_Feedback__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot_interfaces__action__PlaceBlock_Feedback * msg = (cobot_interfaces__action__PlaceBlock_Feedback *)allocator.allocate(sizeof(cobot_interfaces__action__PlaceBlock_Feedback), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(cobot_interfaces__action__PlaceBlock_Feedback));
  bool success = cobot_interfaces__action__PlaceBlock_Feedback__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
cobot_interfaces__action__PlaceBlock_Feedback__destroy(cobot_interfaces__action__PlaceBlock_Feedback * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    cobot_interfaces__action__PlaceBlock_Feedback__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
cobot_interfaces__action__PlaceBlock_Feedback__Sequence__init(cobot_interfaces__action__PlaceBlock_Feedback__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot_interfaces__action__PlaceBlock_Feedback * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(cobot_interfaces__action__PlaceBlock_Feedback)) {
      return false;
    }
    data = (cobot_interfaces__action__PlaceBlock_Feedback *)allocator.zero_allocate(size, sizeof(cobot_interfaces__action__PlaceBlock_Feedback), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = cobot_interfaces__action__PlaceBlock_Feedback__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        cobot_interfaces__action__PlaceBlock_Feedback__fini(&data[i - 1]);
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
cobot_interfaces__action__PlaceBlock_Feedback__Sequence__fini(cobot_interfaces__action__PlaceBlock_Feedback__Sequence * array)
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
      cobot_interfaces__action__PlaceBlock_Feedback__fini(&array->data[i]);
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

cobot_interfaces__action__PlaceBlock_Feedback__Sequence *
cobot_interfaces__action__PlaceBlock_Feedback__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot_interfaces__action__PlaceBlock_Feedback__Sequence * array = (cobot_interfaces__action__PlaceBlock_Feedback__Sequence *)allocator.allocate(sizeof(cobot_interfaces__action__PlaceBlock_Feedback__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = cobot_interfaces__action__PlaceBlock_Feedback__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
cobot_interfaces__action__PlaceBlock_Feedback__Sequence__destroy(cobot_interfaces__action__PlaceBlock_Feedback__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    cobot_interfaces__action__PlaceBlock_Feedback__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
cobot_interfaces__action__PlaceBlock_Feedback__Sequence__are_equal(const cobot_interfaces__action__PlaceBlock_Feedback__Sequence * lhs, const cobot_interfaces__action__PlaceBlock_Feedback__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!cobot_interfaces__action__PlaceBlock_Feedback__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
cobot_interfaces__action__PlaceBlock_Feedback__Sequence__copy(
  const cobot_interfaces__action__PlaceBlock_Feedback__Sequence * input,
  cobot_interfaces__action__PlaceBlock_Feedback__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(cobot_interfaces__action__PlaceBlock_Feedback)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(cobot_interfaces__action__PlaceBlock_Feedback);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    cobot_interfaces__action__PlaceBlock_Feedback * data =
      (cobot_interfaces__action__PlaceBlock_Feedback *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!cobot_interfaces__action__PlaceBlock_Feedback__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          cobot_interfaces__action__PlaceBlock_Feedback__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!cobot_interfaces__action__PlaceBlock_Feedback__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `goal_id`
#include "unique_identifier_msgs/msg/detail/uuid__functions.h"
// Member `goal`
// already included above
// #include "cobot_interfaces/action/detail/place_block__functions.h"

bool
cobot_interfaces__action__PlaceBlock_SendGoal_Request__init(cobot_interfaces__action__PlaceBlock_SendGoal_Request * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    cobot_interfaces__action__PlaceBlock_SendGoal_Request__fini(msg);
    return false;
  }
  // goal
  if (!cobot_interfaces__action__PlaceBlock_Goal__init(&msg->goal)) {
    cobot_interfaces__action__PlaceBlock_SendGoal_Request__fini(msg);
    return false;
  }
  return true;
}

void
cobot_interfaces__action__PlaceBlock_SendGoal_Request__fini(cobot_interfaces__action__PlaceBlock_SendGoal_Request * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
  // goal
  cobot_interfaces__action__PlaceBlock_Goal__fini(&msg->goal);
}

bool
cobot_interfaces__action__PlaceBlock_SendGoal_Request__are_equal(const cobot_interfaces__action__PlaceBlock_SendGoal_Request * lhs, const cobot_interfaces__action__PlaceBlock_SendGoal_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__are_equal(
      &(lhs->goal_id), &(rhs->goal_id)))
  {
    return false;
  }
  // goal
  if (!cobot_interfaces__action__PlaceBlock_Goal__are_equal(
      &(lhs->goal), &(rhs->goal)))
  {
    return false;
  }
  return true;
}

bool
cobot_interfaces__action__PlaceBlock_SendGoal_Request__copy(
  const cobot_interfaces__action__PlaceBlock_SendGoal_Request * input,
  cobot_interfaces__action__PlaceBlock_SendGoal_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__copy(
      &(input->goal_id), &(output->goal_id)))
  {
    return false;
  }
  // goal
  if (!cobot_interfaces__action__PlaceBlock_Goal__copy(
      &(input->goal), &(output->goal)))
  {
    return false;
  }
  return true;
}

cobot_interfaces__action__PlaceBlock_SendGoal_Request *
cobot_interfaces__action__PlaceBlock_SendGoal_Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot_interfaces__action__PlaceBlock_SendGoal_Request * msg = (cobot_interfaces__action__PlaceBlock_SendGoal_Request *)allocator.allocate(sizeof(cobot_interfaces__action__PlaceBlock_SendGoal_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(cobot_interfaces__action__PlaceBlock_SendGoal_Request));
  bool success = cobot_interfaces__action__PlaceBlock_SendGoal_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
cobot_interfaces__action__PlaceBlock_SendGoal_Request__destroy(cobot_interfaces__action__PlaceBlock_SendGoal_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    cobot_interfaces__action__PlaceBlock_SendGoal_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
cobot_interfaces__action__PlaceBlock_SendGoal_Request__Sequence__init(cobot_interfaces__action__PlaceBlock_SendGoal_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot_interfaces__action__PlaceBlock_SendGoal_Request * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(cobot_interfaces__action__PlaceBlock_SendGoal_Request)) {
      return false;
    }
    data = (cobot_interfaces__action__PlaceBlock_SendGoal_Request *)allocator.zero_allocate(size, sizeof(cobot_interfaces__action__PlaceBlock_SendGoal_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = cobot_interfaces__action__PlaceBlock_SendGoal_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        cobot_interfaces__action__PlaceBlock_SendGoal_Request__fini(&data[i - 1]);
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
cobot_interfaces__action__PlaceBlock_SendGoal_Request__Sequence__fini(cobot_interfaces__action__PlaceBlock_SendGoal_Request__Sequence * array)
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
      cobot_interfaces__action__PlaceBlock_SendGoal_Request__fini(&array->data[i]);
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

cobot_interfaces__action__PlaceBlock_SendGoal_Request__Sequence *
cobot_interfaces__action__PlaceBlock_SendGoal_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot_interfaces__action__PlaceBlock_SendGoal_Request__Sequence * array = (cobot_interfaces__action__PlaceBlock_SendGoal_Request__Sequence *)allocator.allocate(sizeof(cobot_interfaces__action__PlaceBlock_SendGoal_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = cobot_interfaces__action__PlaceBlock_SendGoal_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
cobot_interfaces__action__PlaceBlock_SendGoal_Request__Sequence__destroy(cobot_interfaces__action__PlaceBlock_SendGoal_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    cobot_interfaces__action__PlaceBlock_SendGoal_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
cobot_interfaces__action__PlaceBlock_SendGoal_Request__Sequence__are_equal(const cobot_interfaces__action__PlaceBlock_SendGoal_Request__Sequence * lhs, const cobot_interfaces__action__PlaceBlock_SendGoal_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!cobot_interfaces__action__PlaceBlock_SendGoal_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
cobot_interfaces__action__PlaceBlock_SendGoal_Request__Sequence__copy(
  const cobot_interfaces__action__PlaceBlock_SendGoal_Request__Sequence * input,
  cobot_interfaces__action__PlaceBlock_SendGoal_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(cobot_interfaces__action__PlaceBlock_SendGoal_Request)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(cobot_interfaces__action__PlaceBlock_SendGoal_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    cobot_interfaces__action__PlaceBlock_SendGoal_Request * data =
      (cobot_interfaces__action__PlaceBlock_SendGoal_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!cobot_interfaces__action__PlaceBlock_SendGoal_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          cobot_interfaces__action__PlaceBlock_SendGoal_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!cobot_interfaces__action__PlaceBlock_SendGoal_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `stamp`
#include "builtin_interfaces/msg/detail/time__functions.h"

bool
cobot_interfaces__action__PlaceBlock_SendGoal_Response__init(cobot_interfaces__action__PlaceBlock_SendGoal_Response * msg)
{
  if (!msg) {
    return false;
  }
  // accepted
  // stamp
  if (!builtin_interfaces__msg__Time__init(&msg->stamp)) {
    cobot_interfaces__action__PlaceBlock_SendGoal_Response__fini(msg);
    return false;
  }
  return true;
}

void
cobot_interfaces__action__PlaceBlock_SendGoal_Response__fini(cobot_interfaces__action__PlaceBlock_SendGoal_Response * msg)
{
  if (!msg) {
    return;
  }
  // accepted
  // stamp
  builtin_interfaces__msg__Time__fini(&msg->stamp);
}

bool
cobot_interfaces__action__PlaceBlock_SendGoal_Response__are_equal(const cobot_interfaces__action__PlaceBlock_SendGoal_Response * lhs, const cobot_interfaces__action__PlaceBlock_SendGoal_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // accepted
  if (lhs->accepted != rhs->accepted) {
    return false;
  }
  // stamp
  if (!builtin_interfaces__msg__Time__are_equal(
      &(lhs->stamp), &(rhs->stamp)))
  {
    return false;
  }
  return true;
}

bool
cobot_interfaces__action__PlaceBlock_SendGoal_Response__copy(
  const cobot_interfaces__action__PlaceBlock_SendGoal_Response * input,
  cobot_interfaces__action__PlaceBlock_SendGoal_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // accepted
  output->accepted = input->accepted;
  // stamp
  if (!builtin_interfaces__msg__Time__copy(
      &(input->stamp), &(output->stamp)))
  {
    return false;
  }
  return true;
}

cobot_interfaces__action__PlaceBlock_SendGoal_Response *
cobot_interfaces__action__PlaceBlock_SendGoal_Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot_interfaces__action__PlaceBlock_SendGoal_Response * msg = (cobot_interfaces__action__PlaceBlock_SendGoal_Response *)allocator.allocate(sizeof(cobot_interfaces__action__PlaceBlock_SendGoal_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(cobot_interfaces__action__PlaceBlock_SendGoal_Response));
  bool success = cobot_interfaces__action__PlaceBlock_SendGoal_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
cobot_interfaces__action__PlaceBlock_SendGoal_Response__destroy(cobot_interfaces__action__PlaceBlock_SendGoal_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    cobot_interfaces__action__PlaceBlock_SendGoal_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
cobot_interfaces__action__PlaceBlock_SendGoal_Response__Sequence__init(cobot_interfaces__action__PlaceBlock_SendGoal_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot_interfaces__action__PlaceBlock_SendGoal_Response * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(cobot_interfaces__action__PlaceBlock_SendGoal_Response)) {
      return false;
    }
    data = (cobot_interfaces__action__PlaceBlock_SendGoal_Response *)allocator.zero_allocate(size, sizeof(cobot_interfaces__action__PlaceBlock_SendGoal_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = cobot_interfaces__action__PlaceBlock_SendGoal_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        cobot_interfaces__action__PlaceBlock_SendGoal_Response__fini(&data[i - 1]);
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
cobot_interfaces__action__PlaceBlock_SendGoal_Response__Sequence__fini(cobot_interfaces__action__PlaceBlock_SendGoal_Response__Sequence * array)
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
      cobot_interfaces__action__PlaceBlock_SendGoal_Response__fini(&array->data[i]);
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

cobot_interfaces__action__PlaceBlock_SendGoal_Response__Sequence *
cobot_interfaces__action__PlaceBlock_SendGoal_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot_interfaces__action__PlaceBlock_SendGoal_Response__Sequence * array = (cobot_interfaces__action__PlaceBlock_SendGoal_Response__Sequence *)allocator.allocate(sizeof(cobot_interfaces__action__PlaceBlock_SendGoal_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = cobot_interfaces__action__PlaceBlock_SendGoal_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
cobot_interfaces__action__PlaceBlock_SendGoal_Response__Sequence__destroy(cobot_interfaces__action__PlaceBlock_SendGoal_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    cobot_interfaces__action__PlaceBlock_SendGoal_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
cobot_interfaces__action__PlaceBlock_SendGoal_Response__Sequence__are_equal(const cobot_interfaces__action__PlaceBlock_SendGoal_Response__Sequence * lhs, const cobot_interfaces__action__PlaceBlock_SendGoal_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!cobot_interfaces__action__PlaceBlock_SendGoal_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
cobot_interfaces__action__PlaceBlock_SendGoal_Response__Sequence__copy(
  const cobot_interfaces__action__PlaceBlock_SendGoal_Response__Sequence * input,
  cobot_interfaces__action__PlaceBlock_SendGoal_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(cobot_interfaces__action__PlaceBlock_SendGoal_Response)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(cobot_interfaces__action__PlaceBlock_SendGoal_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    cobot_interfaces__action__PlaceBlock_SendGoal_Response * data =
      (cobot_interfaces__action__PlaceBlock_SendGoal_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!cobot_interfaces__action__PlaceBlock_SendGoal_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          cobot_interfaces__action__PlaceBlock_SendGoal_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!cobot_interfaces__action__PlaceBlock_SendGoal_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `info`
#include "service_msgs/msg/detail/service_event_info__functions.h"
// Member `request`
// Member `response`
// already included above
// #include "cobot_interfaces/action/detail/place_block__functions.h"

bool
cobot_interfaces__action__PlaceBlock_SendGoal_Event__init(cobot_interfaces__action__PlaceBlock_SendGoal_Event * msg)
{
  if (!msg) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__init(&msg->info)) {
    cobot_interfaces__action__PlaceBlock_SendGoal_Event__fini(msg);
    return false;
  }
  // request
  if (!cobot_interfaces__action__PlaceBlock_SendGoal_Request__Sequence__init(&msg->request, 0)) {
    cobot_interfaces__action__PlaceBlock_SendGoal_Event__fini(msg);
    return false;
  }
  // response
  if (!cobot_interfaces__action__PlaceBlock_SendGoal_Response__Sequence__init(&msg->response, 0)) {
    cobot_interfaces__action__PlaceBlock_SendGoal_Event__fini(msg);
    return false;
  }
  return true;
}

void
cobot_interfaces__action__PlaceBlock_SendGoal_Event__fini(cobot_interfaces__action__PlaceBlock_SendGoal_Event * msg)
{
  if (!msg) {
    return;
  }
  // info
  service_msgs__msg__ServiceEventInfo__fini(&msg->info);
  // request
  cobot_interfaces__action__PlaceBlock_SendGoal_Request__Sequence__fini(&msg->request);
  // response
  cobot_interfaces__action__PlaceBlock_SendGoal_Response__Sequence__fini(&msg->response);
}

bool
cobot_interfaces__action__PlaceBlock_SendGoal_Event__are_equal(const cobot_interfaces__action__PlaceBlock_SendGoal_Event * lhs, const cobot_interfaces__action__PlaceBlock_SendGoal_Event * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__are_equal(
      &(lhs->info), &(rhs->info)))
  {
    return false;
  }
  // request
  if (!cobot_interfaces__action__PlaceBlock_SendGoal_Request__Sequence__are_equal(
      &(lhs->request), &(rhs->request)))
  {
    return false;
  }
  // response
  if (!cobot_interfaces__action__PlaceBlock_SendGoal_Response__Sequence__are_equal(
      &(lhs->response), &(rhs->response)))
  {
    return false;
  }
  return true;
}

bool
cobot_interfaces__action__PlaceBlock_SendGoal_Event__copy(
  const cobot_interfaces__action__PlaceBlock_SendGoal_Event * input,
  cobot_interfaces__action__PlaceBlock_SendGoal_Event * output)
{
  if (!input || !output) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__copy(
      &(input->info), &(output->info)))
  {
    return false;
  }
  // request
  if (!cobot_interfaces__action__PlaceBlock_SendGoal_Request__Sequence__copy(
      &(input->request), &(output->request)))
  {
    return false;
  }
  // response
  if (!cobot_interfaces__action__PlaceBlock_SendGoal_Response__Sequence__copy(
      &(input->response), &(output->response)))
  {
    return false;
  }
  return true;
}

cobot_interfaces__action__PlaceBlock_SendGoal_Event *
cobot_interfaces__action__PlaceBlock_SendGoal_Event__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot_interfaces__action__PlaceBlock_SendGoal_Event * msg = (cobot_interfaces__action__PlaceBlock_SendGoal_Event *)allocator.allocate(sizeof(cobot_interfaces__action__PlaceBlock_SendGoal_Event), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(cobot_interfaces__action__PlaceBlock_SendGoal_Event));
  bool success = cobot_interfaces__action__PlaceBlock_SendGoal_Event__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
cobot_interfaces__action__PlaceBlock_SendGoal_Event__destroy(cobot_interfaces__action__PlaceBlock_SendGoal_Event * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    cobot_interfaces__action__PlaceBlock_SendGoal_Event__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
cobot_interfaces__action__PlaceBlock_SendGoal_Event__Sequence__init(cobot_interfaces__action__PlaceBlock_SendGoal_Event__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot_interfaces__action__PlaceBlock_SendGoal_Event * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(cobot_interfaces__action__PlaceBlock_SendGoal_Event)) {
      return false;
    }
    data = (cobot_interfaces__action__PlaceBlock_SendGoal_Event *)allocator.zero_allocate(size, sizeof(cobot_interfaces__action__PlaceBlock_SendGoal_Event), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = cobot_interfaces__action__PlaceBlock_SendGoal_Event__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        cobot_interfaces__action__PlaceBlock_SendGoal_Event__fini(&data[i - 1]);
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
cobot_interfaces__action__PlaceBlock_SendGoal_Event__Sequence__fini(cobot_interfaces__action__PlaceBlock_SendGoal_Event__Sequence * array)
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
      cobot_interfaces__action__PlaceBlock_SendGoal_Event__fini(&array->data[i]);
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

cobot_interfaces__action__PlaceBlock_SendGoal_Event__Sequence *
cobot_interfaces__action__PlaceBlock_SendGoal_Event__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot_interfaces__action__PlaceBlock_SendGoal_Event__Sequence * array = (cobot_interfaces__action__PlaceBlock_SendGoal_Event__Sequence *)allocator.allocate(sizeof(cobot_interfaces__action__PlaceBlock_SendGoal_Event__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = cobot_interfaces__action__PlaceBlock_SendGoal_Event__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
cobot_interfaces__action__PlaceBlock_SendGoal_Event__Sequence__destroy(cobot_interfaces__action__PlaceBlock_SendGoal_Event__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    cobot_interfaces__action__PlaceBlock_SendGoal_Event__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
cobot_interfaces__action__PlaceBlock_SendGoal_Event__Sequence__are_equal(const cobot_interfaces__action__PlaceBlock_SendGoal_Event__Sequence * lhs, const cobot_interfaces__action__PlaceBlock_SendGoal_Event__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!cobot_interfaces__action__PlaceBlock_SendGoal_Event__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
cobot_interfaces__action__PlaceBlock_SendGoal_Event__Sequence__copy(
  const cobot_interfaces__action__PlaceBlock_SendGoal_Event__Sequence * input,
  cobot_interfaces__action__PlaceBlock_SendGoal_Event__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(cobot_interfaces__action__PlaceBlock_SendGoal_Event)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(cobot_interfaces__action__PlaceBlock_SendGoal_Event);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    cobot_interfaces__action__PlaceBlock_SendGoal_Event * data =
      (cobot_interfaces__action__PlaceBlock_SendGoal_Event *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!cobot_interfaces__action__PlaceBlock_SendGoal_Event__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          cobot_interfaces__action__PlaceBlock_SendGoal_Event__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!cobot_interfaces__action__PlaceBlock_SendGoal_Event__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__functions.h"

bool
cobot_interfaces__action__PlaceBlock_GetResult_Request__init(cobot_interfaces__action__PlaceBlock_GetResult_Request * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    cobot_interfaces__action__PlaceBlock_GetResult_Request__fini(msg);
    return false;
  }
  return true;
}

void
cobot_interfaces__action__PlaceBlock_GetResult_Request__fini(cobot_interfaces__action__PlaceBlock_GetResult_Request * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
}

bool
cobot_interfaces__action__PlaceBlock_GetResult_Request__are_equal(const cobot_interfaces__action__PlaceBlock_GetResult_Request * lhs, const cobot_interfaces__action__PlaceBlock_GetResult_Request * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__are_equal(
      &(lhs->goal_id), &(rhs->goal_id)))
  {
    return false;
  }
  return true;
}

bool
cobot_interfaces__action__PlaceBlock_GetResult_Request__copy(
  const cobot_interfaces__action__PlaceBlock_GetResult_Request * input,
  cobot_interfaces__action__PlaceBlock_GetResult_Request * output)
{
  if (!input || !output) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__copy(
      &(input->goal_id), &(output->goal_id)))
  {
    return false;
  }
  return true;
}

cobot_interfaces__action__PlaceBlock_GetResult_Request *
cobot_interfaces__action__PlaceBlock_GetResult_Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot_interfaces__action__PlaceBlock_GetResult_Request * msg = (cobot_interfaces__action__PlaceBlock_GetResult_Request *)allocator.allocate(sizeof(cobot_interfaces__action__PlaceBlock_GetResult_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(cobot_interfaces__action__PlaceBlock_GetResult_Request));
  bool success = cobot_interfaces__action__PlaceBlock_GetResult_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
cobot_interfaces__action__PlaceBlock_GetResult_Request__destroy(cobot_interfaces__action__PlaceBlock_GetResult_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    cobot_interfaces__action__PlaceBlock_GetResult_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
cobot_interfaces__action__PlaceBlock_GetResult_Request__Sequence__init(cobot_interfaces__action__PlaceBlock_GetResult_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot_interfaces__action__PlaceBlock_GetResult_Request * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(cobot_interfaces__action__PlaceBlock_GetResult_Request)) {
      return false;
    }
    data = (cobot_interfaces__action__PlaceBlock_GetResult_Request *)allocator.zero_allocate(size, sizeof(cobot_interfaces__action__PlaceBlock_GetResult_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = cobot_interfaces__action__PlaceBlock_GetResult_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        cobot_interfaces__action__PlaceBlock_GetResult_Request__fini(&data[i - 1]);
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
cobot_interfaces__action__PlaceBlock_GetResult_Request__Sequence__fini(cobot_interfaces__action__PlaceBlock_GetResult_Request__Sequence * array)
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
      cobot_interfaces__action__PlaceBlock_GetResult_Request__fini(&array->data[i]);
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

cobot_interfaces__action__PlaceBlock_GetResult_Request__Sequence *
cobot_interfaces__action__PlaceBlock_GetResult_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot_interfaces__action__PlaceBlock_GetResult_Request__Sequence * array = (cobot_interfaces__action__PlaceBlock_GetResult_Request__Sequence *)allocator.allocate(sizeof(cobot_interfaces__action__PlaceBlock_GetResult_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = cobot_interfaces__action__PlaceBlock_GetResult_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
cobot_interfaces__action__PlaceBlock_GetResult_Request__Sequence__destroy(cobot_interfaces__action__PlaceBlock_GetResult_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    cobot_interfaces__action__PlaceBlock_GetResult_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
cobot_interfaces__action__PlaceBlock_GetResult_Request__Sequence__are_equal(const cobot_interfaces__action__PlaceBlock_GetResult_Request__Sequence * lhs, const cobot_interfaces__action__PlaceBlock_GetResult_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!cobot_interfaces__action__PlaceBlock_GetResult_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
cobot_interfaces__action__PlaceBlock_GetResult_Request__Sequence__copy(
  const cobot_interfaces__action__PlaceBlock_GetResult_Request__Sequence * input,
  cobot_interfaces__action__PlaceBlock_GetResult_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(cobot_interfaces__action__PlaceBlock_GetResult_Request)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(cobot_interfaces__action__PlaceBlock_GetResult_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    cobot_interfaces__action__PlaceBlock_GetResult_Request * data =
      (cobot_interfaces__action__PlaceBlock_GetResult_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!cobot_interfaces__action__PlaceBlock_GetResult_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          cobot_interfaces__action__PlaceBlock_GetResult_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!cobot_interfaces__action__PlaceBlock_GetResult_Request__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `result`
// already included above
// #include "cobot_interfaces/action/detail/place_block__functions.h"

bool
cobot_interfaces__action__PlaceBlock_GetResult_Response__init(cobot_interfaces__action__PlaceBlock_GetResult_Response * msg)
{
  if (!msg) {
    return false;
  }
  // status
  // result
  if (!cobot_interfaces__action__PlaceBlock_Result__init(&msg->result)) {
    cobot_interfaces__action__PlaceBlock_GetResult_Response__fini(msg);
    return false;
  }
  return true;
}

void
cobot_interfaces__action__PlaceBlock_GetResult_Response__fini(cobot_interfaces__action__PlaceBlock_GetResult_Response * msg)
{
  if (!msg) {
    return;
  }
  // status
  // result
  cobot_interfaces__action__PlaceBlock_Result__fini(&msg->result);
}

bool
cobot_interfaces__action__PlaceBlock_GetResult_Response__are_equal(const cobot_interfaces__action__PlaceBlock_GetResult_Response * lhs, const cobot_interfaces__action__PlaceBlock_GetResult_Response * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // status
  if (lhs->status != rhs->status) {
    return false;
  }
  // result
  if (!cobot_interfaces__action__PlaceBlock_Result__are_equal(
      &(lhs->result), &(rhs->result)))
  {
    return false;
  }
  return true;
}

bool
cobot_interfaces__action__PlaceBlock_GetResult_Response__copy(
  const cobot_interfaces__action__PlaceBlock_GetResult_Response * input,
  cobot_interfaces__action__PlaceBlock_GetResult_Response * output)
{
  if (!input || !output) {
    return false;
  }
  // status
  output->status = input->status;
  // result
  if (!cobot_interfaces__action__PlaceBlock_Result__copy(
      &(input->result), &(output->result)))
  {
    return false;
  }
  return true;
}

cobot_interfaces__action__PlaceBlock_GetResult_Response *
cobot_interfaces__action__PlaceBlock_GetResult_Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot_interfaces__action__PlaceBlock_GetResult_Response * msg = (cobot_interfaces__action__PlaceBlock_GetResult_Response *)allocator.allocate(sizeof(cobot_interfaces__action__PlaceBlock_GetResult_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(cobot_interfaces__action__PlaceBlock_GetResult_Response));
  bool success = cobot_interfaces__action__PlaceBlock_GetResult_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
cobot_interfaces__action__PlaceBlock_GetResult_Response__destroy(cobot_interfaces__action__PlaceBlock_GetResult_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    cobot_interfaces__action__PlaceBlock_GetResult_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
cobot_interfaces__action__PlaceBlock_GetResult_Response__Sequence__init(cobot_interfaces__action__PlaceBlock_GetResult_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot_interfaces__action__PlaceBlock_GetResult_Response * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(cobot_interfaces__action__PlaceBlock_GetResult_Response)) {
      return false;
    }
    data = (cobot_interfaces__action__PlaceBlock_GetResult_Response *)allocator.zero_allocate(size, sizeof(cobot_interfaces__action__PlaceBlock_GetResult_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = cobot_interfaces__action__PlaceBlock_GetResult_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        cobot_interfaces__action__PlaceBlock_GetResult_Response__fini(&data[i - 1]);
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
cobot_interfaces__action__PlaceBlock_GetResult_Response__Sequence__fini(cobot_interfaces__action__PlaceBlock_GetResult_Response__Sequence * array)
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
      cobot_interfaces__action__PlaceBlock_GetResult_Response__fini(&array->data[i]);
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

cobot_interfaces__action__PlaceBlock_GetResult_Response__Sequence *
cobot_interfaces__action__PlaceBlock_GetResult_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot_interfaces__action__PlaceBlock_GetResult_Response__Sequence * array = (cobot_interfaces__action__PlaceBlock_GetResult_Response__Sequence *)allocator.allocate(sizeof(cobot_interfaces__action__PlaceBlock_GetResult_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = cobot_interfaces__action__PlaceBlock_GetResult_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
cobot_interfaces__action__PlaceBlock_GetResult_Response__Sequence__destroy(cobot_interfaces__action__PlaceBlock_GetResult_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    cobot_interfaces__action__PlaceBlock_GetResult_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
cobot_interfaces__action__PlaceBlock_GetResult_Response__Sequence__are_equal(const cobot_interfaces__action__PlaceBlock_GetResult_Response__Sequence * lhs, const cobot_interfaces__action__PlaceBlock_GetResult_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!cobot_interfaces__action__PlaceBlock_GetResult_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
cobot_interfaces__action__PlaceBlock_GetResult_Response__Sequence__copy(
  const cobot_interfaces__action__PlaceBlock_GetResult_Response__Sequence * input,
  cobot_interfaces__action__PlaceBlock_GetResult_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(cobot_interfaces__action__PlaceBlock_GetResult_Response)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(cobot_interfaces__action__PlaceBlock_GetResult_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    cobot_interfaces__action__PlaceBlock_GetResult_Response * data =
      (cobot_interfaces__action__PlaceBlock_GetResult_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!cobot_interfaces__action__PlaceBlock_GetResult_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          cobot_interfaces__action__PlaceBlock_GetResult_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!cobot_interfaces__action__PlaceBlock_GetResult_Response__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `info`
// already included above
// #include "service_msgs/msg/detail/service_event_info__functions.h"
// Member `request`
// Member `response`
// already included above
// #include "cobot_interfaces/action/detail/place_block__functions.h"

bool
cobot_interfaces__action__PlaceBlock_GetResult_Event__init(cobot_interfaces__action__PlaceBlock_GetResult_Event * msg)
{
  if (!msg) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__init(&msg->info)) {
    cobot_interfaces__action__PlaceBlock_GetResult_Event__fini(msg);
    return false;
  }
  // request
  if (!cobot_interfaces__action__PlaceBlock_GetResult_Request__Sequence__init(&msg->request, 0)) {
    cobot_interfaces__action__PlaceBlock_GetResult_Event__fini(msg);
    return false;
  }
  // response
  if (!cobot_interfaces__action__PlaceBlock_GetResult_Response__Sequence__init(&msg->response, 0)) {
    cobot_interfaces__action__PlaceBlock_GetResult_Event__fini(msg);
    return false;
  }
  return true;
}

void
cobot_interfaces__action__PlaceBlock_GetResult_Event__fini(cobot_interfaces__action__PlaceBlock_GetResult_Event * msg)
{
  if (!msg) {
    return;
  }
  // info
  service_msgs__msg__ServiceEventInfo__fini(&msg->info);
  // request
  cobot_interfaces__action__PlaceBlock_GetResult_Request__Sequence__fini(&msg->request);
  // response
  cobot_interfaces__action__PlaceBlock_GetResult_Response__Sequence__fini(&msg->response);
}

bool
cobot_interfaces__action__PlaceBlock_GetResult_Event__are_equal(const cobot_interfaces__action__PlaceBlock_GetResult_Event * lhs, const cobot_interfaces__action__PlaceBlock_GetResult_Event * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__are_equal(
      &(lhs->info), &(rhs->info)))
  {
    return false;
  }
  // request
  if (!cobot_interfaces__action__PlaceBlock_GetResult_Request__Sequence__are_equal(
      &(lhs->request), &(rhs->request)))
  {
    return false;
  }
  // response
  if (!cobot_interfaces__action__PlaceBlock_GetResult_Response__Sequence__are_equal(
      &(lhs->response), &(rhs->response)))
  {
    return false;
  }
  return true;
}

bool
cobot_interfaces__action__PlaceBlock_GetResult_Event__copy(
  const cobot_interfaces__action__PlaceBlock_GetResult_Event * input,
  cobot_interfaces__action__PlaceBlock_GetResult_Event * output)
{
  if (!input || !output) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__copy(
      &(input->info), &(output->info)))
  {
    return false;
  }
  // request
  if (!cobot_interfaces__action__PlaceBlock_GetResult_Request__Sequence__copy(
      &(input->request), &(output->request)))
  {
    return false;
  }
  // response
  if (!cobot_interfaces__action__PlaceBlock_GetResult_Response__Sequence__copy(
      &(input->response), &(output->response)))
  {
    return false;
  }
  return true;
}

cobot_interfaces__action__PlaceBlock_GetResult_Event *
cobot_interfaces__action__PlaceBlock_GetResult_Event__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot_interfaces__action__PlaceBlock_GetResult_Event * msg = (cobot_interfaces__action__PlaceBlock_GetResult_Event *)allocator.allocate(sizeof(cobot_interfaces__action__PlaceBlock_GetResult_Event), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(cobot_interfaces__action__PlaceBlock_GetResult_Event));
  bool success = cobot_interfaces__action__PlaceBlock_GetResult_Event__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
cobot_interfaces__action__PlaceBlock_GetResult_Event__destroy(cobot_interfaces__action__PlaceBlock_GetResult_Event * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    cobot_interfaces__action__PlaceBlock_GetResult_Event__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
cobot_interfaces__action__PlaceBlock_GetResult_Event__Sequence__init(cobot_interfaces__action__PlaceBlock_GetResult_Event__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot_interfaces__action__PlaceBlock_GetResult_Event * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(cobot_interfaces__action__PlaceBlock_GetResult_Event)) {
      return false;
    }
    data = (cobot_interfaces__action__PlaceBlock_GetResult_Event *)allocator.zero_allocate(size, sizeof(cobot_interfaces__action__PlaceBlock_GetResult_Event), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = cobot_interfaces__action__PlaceBlock_GetResult_Event__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        cobot_interfaces__action__PlaceBlock_GetResult_Event__fini(&data[i - 1]);
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
cobot_interfaces__action__PlaceBlock_GetResult_Event__Sequence__fini(cobot_interfaces__action__PlaceBlock_GetResult_Event__Sequence * array)
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
      cobot_interfaces__action__PlaceBlock_GetResult_Event__fini(&array->data[i]);
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

cobot_interfaces__action__PlaceBlock_GetResult_Event__Sequence *
cobot_interfaces__action__PlaceBlock_GetResult_Event__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot_interfaces__action__PlaceBlock_GetResult_Event__Sequence * array = (cobot_interfaces__action__PlaceBlock_GetResult_Event__Sequence *)allocator.allocate(sizeof(cobot_interfaces__action__PlaceBlock_GetResult_Event__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = cobot_interfaces__action__PlaceBlock_GetResult_Event__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
cobot_interfaces__action__PlaceBlock_GetResult_Event__Sequence__destroy(cobot_interfaces__action__PlaceBlock_GetResult_Event__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    cobot_interfaces__action__PlaceBlock_GetResult_Event__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
cobot_interfaces__action__PlaceBlock_GetResult_Event__Sequence__are_equal(const cobot_interfaces__action__PlaceBlock_GetResult_Event__Sequence * lhs, const cobot_interfaces__action__PlaceBlock_GetResult_Event__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!cobot_interfaces__action__PlaceBlock_GetResult_Event__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
cobot_interfaces__action__PlaceBlock_GetResult_Event__Sequence__copy(
  const cobot_interfaces__action__PlaceBlock_GetResult_Event__Sequence * input,
  cobot_interfaces__action__PlaceBlock_GetResult_Event__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(cobot_interfaces__action__PlaceBlock_GetResult_Event)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(cobot_interfaces__action__PlaceBlock_GetResult_Event);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    cobot_interfaces__action__PlaceBlock_GetResult_Event * data =
      (cobot_interfaces__action__PlaceBlock_GetResult_Event *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!cobot_interfaces__action__PlaceBlock_GetResult_Event__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          cobot_interfaces__action__PlaceBlock_GetResult_Event__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!cobot_interfaces__action__PlaceBlock_GetResult_Event__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}


// Include directives for member types
// Member `goal_id`
// already included above
// #include "unique_identifier_msgs/msg/detail/uuid__functions.h"
// Member `feedback`
// already included above
// #include "cobot_interfaces/action/detail/place_block__functions.h"

bool
cobot_interfaces__action__PlaceBlock_FeedbackMessage__init(cobot_interfaces__action__PlaceBlock_FeedbackMessage * msg)
{
  if (!msg) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__init(&msg->goal_id)) {
    cobot_interfaces__action__PlaceBlock_FeedbackMessage__fini(msg);
    return false;
  }
  // feedback
  if (!cobot_interfaces__action__PlaceBlock_Feedback__init(&msg->feedback)) {
    cobot_interfaces__action__PlaceBlock_FeedbackMessage__fini(msg);
    return false;
  }
  return true;
}

void
cobot_interfaces__action__PlaceBlock_FeedbackMessage__fini(cobot_interfaces__action__PlaceBlock_FeedbackMessage * msg)
{
  if (!msg) {
    return;
  }
  // goal_id
  unique_identifier_msgs__msg__UUID__fini(&msg->goal_id);
  // feedback
  cobot_interfaces__action__PlaceBlock_Feedback__fini(&msg->feedback);
}

bool
cobot_interfaces__action__PlaceBlock_FeedbackMessage__are_equal(const cobot_interfaces__action__PlaceBlock_FeedbackMessage * lhs, const cobot_interfaces__action__PlaceBlock_FeedbackMessage * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__are_equal(
      &(lhs->goal_id), &(rhs->goal_id)))
  {
    return false;
  }
  // feedback
  if (!cobot_interfaces__action__PlaceBlock_Feedback__are_equal(
      &(lhs->feedback), &(rhs->feedback)))
  {
    return false;
  }
  return true;
}

bool
cobot_interfaces__action__PlaceBlock_FeedbackMessage__copy(
  const cobot_interfaces__action__PlaceBlock_FeedbackMessage * input,
  cobot_interfaces__action__PlaceBlock_FeedbackMessage * output)
{
  if (!input || !output) {
    return false;
  }
  // goal_id
  if (!unique_identifier_msgs__msg__UUID__copy(
      &(input->goal_id), &(output->goal_id)))
  {
    return false;
  }
  // feedback
  if (!cobot_interfaces__action__PlaceBlock_Feedback__copy(
      &(input->feedback), &(output->feedback)))
  {
    return false;
  }
  return true;
}

cobot_interfaces__action__PlaceBlock_FeedbackMessage *
cobot_interfaces__action__PlaceBlock_FeedbackMessage__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot_interfaces__action__PlaceBlock_FeedbackMessage * msg = (cobot_interfaces__action__PlaceBlock_FeedbackMessage *)allocator.allocate(sizeof(cobot_interfaces__action__PlaceBlock_FeedbackMessage), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(cobot_interfaces__action__PlaceBlock_FeedbackMessage));
  bool success = cobot_interfaces__action__PlaceBlock_FeedbackMessage__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
cobot_interfaces__action__PlaceBlock_FeedbackMessage__destroy(cobot_interfaces__action__PlaceBlock_FeedbackMessage * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    cobot_interfaces__action__PlaceBlock_FeedbackMessage__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
cobot_interfaces__action__PlaceBlock_FeedbackMessage__Sequence__init(cobot_interfaces__action__PlaceBlock_FeedbackMessage__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot_interfaces__action__PlaceBlock_FeedbackMessage * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(cobot_interfaces__action__PlaceBlock_FeedbackMessage)) {
      return false;
    }
    data = (cobot_interfaces__action__PlaceBlock_FeedbackMessage *)allocator.zero_allocate(size, sizeof(cobot_interfaces__action__PlaceBlock_FeedbackMessage), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = cobot_interfaces__action__PlaceBlock_FeedbackMessage__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        cobot_interfaces__action__PlaceBlock_FeedbackMessage__fini(&data[i - 1]);
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
cobot_interfaces__action__PlaceBlock_FeedbackMessage__Sequence__fini(cobot_interfaces__action__PlaceBlock_FeedbackMessage__Sequence * array)
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
      cobot_interfaces__action__PlaceBlock_FeedbackMessage__fini(&array->data[i]);
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

cobot_interfaces__action__PlaceBlock_FeedbackMessage__Sequence *
cobot_interfaces__action__PlaceBlock_FeedbackMessage__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot_interfaces__action__PlaceBlock_FeedbackMessage__Sequence * array = (cobot_interfaces__action__PlaceBlock_FeedbackMessage__Sequence *)allocator.allocate(sizeof(cobot_interfaces__action__PlaceBlock_FeedbackMessage__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = cobot_interfaces__action__PlaceBlock_FeedbackMessage__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
cobot_interfaces__action__PlaceBlock_FeedbackMessage__Sequence__destroy(cobot_interfaces__action__PlaceBlock_FeedbackMessage__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    cobot_interfaces__action__PlaceBlock_FeedbackMessage__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
cobot_interfaces__action__PlaceBlock_FeedbackMessage__Sequence__are_equal(const cobot_interfaces__action__PlaceBlock_FeedbackMessage__Sequence * lhs, const cobot_interfaces__action__PlaceBlock_FeedbackMessage__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!cobot_interfaces__action__PlaceBlock_FeedbackMessage__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
cobot_interfaces__action__PlaceBlock_FeedbackMessage__Sequence__copy(
  const cobot_interfaces__action__PlaceBlock_FeedbackMessage__Sequence * input,
  cobot_interfaces__action__PlaceBlock_FeedbackMessage__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(cobot_interfaces__action__PlaceBlock_FeedbackMessage)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(cobot_interfaces__action__PlaceBlock_FeedbackMessage);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    cobot_interfaces__action__PlaceBlock_FeedbackMessage * data =
      (cobot_interfaces__action__PlaceBlock_FeedbackMessage *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!cobot_interfaces__action__PlaceBlock_FeedbackMessage__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          cobot_interfaces__action__PlaceBlock_FeedbackMessage__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!cobot_interfaces__action__PlaceBlock_FeedbackMessage__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
