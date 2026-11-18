// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from cobot_interfaces:srv/LocateBlocks.idl
// generated code does not contain a copyright notice
#include "cobot_interfaces/srv/detail/locate_blocks__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"

// Include directives for member types
// Member `color`
#include "rosidl_runtime_c/string_functions.h"

bool
cobot_interfaces__srv__LocateBlocks_Request__init(cobot_interfaces__srv__LocateBlocks_Request * msg)
{
  if (!msg) {
    return false;
  }
  // color
  if (!rosidl_runtime_c__String__init(&msg->color)) {
    cobot_interfaces__srv__LocateBlocks_Request__fini(msg);
    return false;
  }
  // go_home
  return true;
}

void
cobot_interfaces__srv__LocateBlocks_Request__fini(cobot_interfaces__srv__LocateBlocks_Request * msg)
{
  if (!msg) {
    return;
  }
  // color
  rosidl_runtime_c__String__fini(&msg->color);
  // go_home
}

bool
cobot_interfaces__srv__LocateBlocks_Request__are_equal(const cobot_interfaces__srv__LocateBlocks_Request * lhs, const cobot_interfaces__srv__LocateBlocks_Request * rhs)
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
  // go_home
  if (lhs->go_home != rhs->go_home) {
    return false;
  }
  return true;
}

bool
cobot_interfaces__srv__LocateBlocks_Request__copy(
  const cobot_interfaces__srv__LocateBlocks_Request * input,
  cobot_interfaces__srv__LocateBlocks_Request * output)
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
  // go_home
  output->go_home = input->go_home;
  return true;
}

cobot_interfaces__srv__LocateBlocks_Request *
cobot_interfaces__srv__LocateBlocks_Request__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot_interfaces__srv__LocateBlocks_Request * msg = (cobot_interfaces__srv__LocateBlocks_Request *)allocator.allocate(sizeof(cobot_interfaces__srv__LocateBlocks_Request), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(cobot_interfaces__srv__LocateBlocks_Request));
  bool success = cobot_interfaces__srv__LocateBlocks_Request__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
cobot_interfaces__srv__LocateBlocks_Request__destroy(cobot_interfaces__srv__LocateBlocks_Request * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    cobot_interfaces__srv__LocateBlocks_Request__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
cobot_interfaces__srv__LocateBlocks_Request__Sequence__init(cobot_interfaces__srv__LocateBlocks_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot_interfaces__srv__LocateBlocks_Request * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(cobot_interfaces__srv__LocateBlocks_Request)) {
      return false;
    }
    data = (cobot_interfaces__srv__LocateBlocks_Request *)allocator.zero_allocate(size, sizeof(cobot_interfaces__srv__LocateBlocks_Request), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = cobot_interfaces__srv__LocateBlocks_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        cobot_interfaces__srv__LocateBlocks_Request__fini(&data[i - 1]);
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
cobot_interfaces__srv__LocateBlocks_Request__Sequence__fini(cobot_interfaces__srv__LocateBlocks_Request__Sequence * array)
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
      cobot_interfaces__srv__LocateBlocks_Request__fini(&array->data[i]);
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

cobot_interfaces__srv__LocateBlocks_Request__Sequence *
cobot_interfaces__srv__LocateBlocks_Request__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot_interfaces__srv__LocateBlocks_Request__Sequence * array = (cobot_interfaces__srv__LocateBlocks_Request__Sequence *)allocator.allocate(sizeof(cobot_interfaces__srv__LocateBlocks_Request__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = cobot_interfaces__srv__LocateBlocks_Request__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
cobot_interfaces__srv__LocateBlocks_Request__Sequence__destroy(cobot_interfaces__srv__LocateBlocks_Request__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    cobot_interfaces__srv__LocateBlocks_Request__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
cobot_interfaces__srv__LocateBlocks_Request__Sequence__are_equal(const cobot_interfaces__srv__LocateBlocks_Request__Sequence * lhs, const cobot_interfaces__srv__LocateBlocks_Request__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!cobot_interfaces__srv__LocateBlocks_Request__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
cobot_interfaces__srv__LocateBlocks_Request__Sequence__copy(
  const cobot_interfaces__srv__LocateBlocks_Request__Sequence * input,
  cobot_interfaces__srv__LocateBlocks_Request__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(cobot_interfaces__srv__LocateBlocks_Request)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(cobot_interfaces__srv__LocateBlocks_Request);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    cobot_interfaces__srv__LocateBlocks_Request * data =
      (cobot_interfaces__srv__LocateBlocks_Request *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!cobot_interfaces__srv__LocateBlocks_Request__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          cobot_interfaces__srv__LocateBlocks_Request__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!cobot_interfaces__srv__LocateBlocks_Request__copy(
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
// Member `blocks`
#include "cobot_interfaces/msg/detail/block_info__functions.h"

bool
cobot_interfaces__srv__LocateBlocks_Response__init(cobot_interfaces__srv__LocateBlocks_Response * msg)
{
  if (!msg) {
    return false;
  }
  // success
  // message
  if (!rosidl_runtime_c__String__init(&msg->message)) {
    cobot_interfaces__srv__LocateBlocks_Response__fini(msg);
    return false;
  }
  // blocks
  if (!cobot_interfaces__msg__BlockInfo__Sequence__init(&msg->blocks, 0)) {
    cobot_interfaces__srv__LocateBlocks_Response__fini(msg);
    return false;
  }
  return true;
}

void
cobot_interfaces__srv__LocateBlocks_Response__fini(cobot_interfaces__srv__LocateBlocks_Response * msg)
{
  if (!msg) {
    return;
  }
  // success
  // message
  rosidl_runtime_c__String__fini(&msg->message);
  // blocks
  cobot_interfaces__msg__BlockInfo__Sequence__fini(&msg->blocks);
}

bool
cobot_interfaces__srv__LocateBlocks_Response__are_equal(const cobot_interfaces__srv__LocateBlocks_Response * lhs, const cobot_interfaces__srv__LocateBlocks_Response * rhs)
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
  // blocks
  if (!cobot_interfaces__msg__BlockInfo__Sequence__are_equal(
      &(lhs->blocks), &(rhs->blocks)))
  {
    return false;
  }
  return true;
}

bool
cobot_interfaces__srv__LocateBlocks_Response__copy(
  const cobot_interfaces__srv__LocateBlocks_Response * input,
  cobot_interfaces__srv__LocateBlocks_Response * output)
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
  // blocks
  if (!cobot_interfaces__msg__BlockInfo__Sequence__copy(
      &(input->blocks), &(output->blocks)))
  {
    return false;
  }
  return true;
}

cobot_interfaces__srv__LocateBlocks_Response *
cobot_interfaces__srv__LocateBlocks_Response__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot_interfaces__srv__LocateBlocks_Response * msg = (cobot_interfaces__srv__LocateBlocks_Response *)allocator.allocate(sizeof(cobot_interfaces__srv__LocateBlocks_Response), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(cobot_interfaces__srv__LocateBlocks_Response));
  bool success = cobot_interfaces__srv__LocateBlocks_Response__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
cobot_interfaces__srv__LocateBlocks_Response__destroy(cobot_interfaces__srv__LocateBlocks_Response * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    cobot_interfaces__srv__LocateBlocks_Response__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
cobot_interfaces__srv__LocateBlocks_Response__Sequence__init(cobot_interfaces__srv__LocateBlocks_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot_interfaces__srv__LocateBlocks_Response * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(cobot_interfaces__srv__LocateBlocks_Response)) {
      return false;
    }
    data = (cobot_interfaces__srv__LocateBlocks_Response *)allocator.zero_allocate(size, sizeof(cobot_interfaces__srv__LocateBlocks_Response), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = cobot_interfaces__srv__LocateBlocks_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        cobot_interfaces__srv__LocateBlocks_Response__fini(&data[i - 1]);
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
cobot_interfaces__srv__LocateBlocks_Response__Sequence__fini(cobot_interfaces__srv__LocateBlocks_Response__Sequence * array)
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
      cobot_interfaces__srv__LocateBlocks_Response__fini(&array->data[i]);
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

cobot_interfaces__srv__LocateBlocks_Response__Sequence *
cobot_interfaces__srv__LocateBlocks_Response__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot_interfaces__srv__LocateBlocks_Response__Sequence * array = (cobot_interfaces__srv__LocateBlocks_Response__Sequence *)allocator.allocate(sizeof(cobot_interfaces__srv__LocateBlocks_Response__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = cobot_interfaces__srv__LocateBlocks_Response__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
cobot_interfaces__srv__LocateBlocks_Response__Sequence__destroy(cobot_interfaces__srv__LocateBlocks_Response__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    cobot_interfaces__srv__LocateBlocks_Response__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
cobot_interfaces__srv__LocateBlocks_Response__Sequence__are_equal(const cobot_interfaces__srv__LocateBlocks_Response__Sequence * lhs, const cobot_interfaces__srv__LocateBlocks_Response__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!cobot_interfaces__srv__LocateBlocks_Response__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
cobot_interfaces__srv__LocateBlocks_Response__Sequence__copy(
  const cobot_interfaces__srv__LocateBlocks_Response__Sequence * input,
  cobot_interfaces__srv__LocateBlocks_Response__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(cobot_interfaces__srv__LocateBlocks_Response)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(cobot_interfaces__srv__LocateBlocks_Response);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    cobot_interfaces__srv__LocateBlocks_Response * data =
      (cobot_interfaces__srv__LocateBlocks_Response *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!cobot_interfaces__srv__LocateBlocks_Response__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          cobot_interfaces__srv__LocateBlocks_Response__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!cobot_interfaces__srv__LocateBlocks_Response__copy(
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
// #include "cobot_interfaces/srv/detail/locate_blocks__functions.h"

bool
cobot_interfaces__srv__LocateBlocks_Event__init(cobot_interfaces__srv__LocateBlocks_Event * msg)
{
  if (!msg) {
    return false;
  }
  // info
  if (!service_msgs__msg__ServiceEventInfo__init(&msg->info)) {
    cobot_interfaces__srv__LocateBlocks_Event__fini(msg);
    return false;
  }
  // request
  if (!cobot_interfaces__srv__LocateBlocks_Request__Sequence__init(&msg->request, 0)) {
    cobot_interfaces__srv__LocateBlocks_Event__fini(msg);
    return false;
  }
  // response
  if (!cobot_interfaces__srv__LocateBlocks_Response__Sequence__init(&msg->response, 0)) {
    cobot_interfaces__srv__LocateBlocks_Event__fini(msg);
    return false;
  }
  return true;
}

void
cobot_interfaces__srv__LocateBlocks_Event__fini(cobot_interfaces__srv__LocateBlocks_Event * msg)
{
  if (!msg) {
    return;
  }
  // info
  service_msgs__msg__ServiceEventInfo__fini(&msg->info);
  // request
  cobot_interfaces__srv__LocateBlocks_Request__Sequence__fini(&msg->request);
  // response
  cobot_interfaces__srv__LocateBlocks_Response__Sequence__fini(&msg->response);
}

bool
cobot_interfaces__srv__LocateBlocks_Event__are_equal(const cobot_interfaces__srv__LocateBlocks_Event * lhs, const cobot_interfaces__srv__LocateBlocks_Event * rhs)
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
  if (!cobot_interfaces__srv__LocateBlocks_Request__Sequence__are_equal(
      &(lhs->request), &(rhs->request)))
  {
    return false;
  }
  // response
  if (!cobot_interfaces__srv__LocateBlocks_Response__Sequence__are_equal(
      &(lhs->response), &(rhs->response)))
  {
    return false;
  }
  return true;
}

bool
cobot_interfaces__srv__LocateBlocks_Event__copy(
  const cobot_interfaces__srv__LocateBlocks_Event * input,
  cobot_interfaces__srv__LocateBlocks_Event * output)
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
  if (!cobot_interfaces__srv__LocateBlocks_Request__Sequence__copy(
      &(input->request), &(output->request)))
  {
    return false;
  }
  // response
  if (!cobot_interfaces__srv__LocateBlocks_Response__Sequence__copy(
      &(input->response), &(output->response)))
  {
    return false;
  }
  return true;
}

cobot_interfaces__srv__LocateBlocks_Event *
cobot_interfaces__srv__LocateBlocks_Event__create(void)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot_interfaces__srv__LocateBlocks_Event * msg = (cobot_interfaces__srv__LocateBlocks_Event *)allocator.allocate(sizeof(cobot_interfaces__srv__LocateBlocks_Event), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(cobot_interfaces__srv__LocateBlocks_Event));
  bool success = cobot_interfaces__srv__LocateBlocks_Event__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
cobot_interfaces__srv__LocateBlocks_Event__destroy(cobot_interfaces__srv__LocateBlocks_Event * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    cobot_interfaces__srv__LocateBlocks_Event__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
cobot_interfaces__srv__LocateBlocks_Event__Sequence__init(cobot_interfaces__srv__LocateBlocks_Event__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot_interfaces__srv__LocateBlocks_Event * data = NULL;

  if (size) {
    if (size > SIZE_MAX / sizeof(cobot_interfaces__srv__LocateBlocks_Event)) {
      return false;
    }
    data = (cobot_interfaces__srv__LocateBlocks_Event *)allocator.zero_allocate(size, sizeof(cobot_interfaces__srv__LocateBlocks_Event), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = cobot_interfaces__srv__LocateBlocks_Event__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        cobot_interfaces__srv__LocateBlocks_Event__fini(&data[i - 1]);
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
cobot_interfaces__srv__LocateBlocks_Event__Sequence__fini(cobot_interfaces__srv__LocateBlocks_Event__Sequence * array)
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
      cobot_interfaces__srv__LocateBlocks_Event__fini(&array->data[i]);
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

cobot_interfaces__srv__LocateBlocks_Event__Sequence *
cobot_interfaces__srv__LocateBlocks_Event__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  cobot_interfaces__srv__LocateBlocks_Event__Sequence * array = (cobot_interfaces__srv__LocateBlocks_Event__Sequence *)allocator.allocate(sizeof(cobot_interfaces__srv__LocateBlocks_Event__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = cobot_interfaces__srv__LocateBlocks_Event__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
cobot_interfaces__srv__LocateBlocks_Event__Sequence__destroy(cobot_interfaces__srv__LocateBlocks_Event__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    cobot_interfaces__srv__LocateBlocks_Event__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
cobot_interfaces__srv__LocateBlocks_Event__Sequence__are_equal(const cobot_interfaces__srv__LocateBlocks_Event__Sequence * lhs, const cobot_interfaces__srv__LocateBlocks_Event__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!cobot_interfaces__srv__LocateBlocks_Event__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
cobot_interfaces__srv__LocateBlocks_Event__Sequence__copy(
  const cobot_interfaces__srv__LocateBlocks_Event__Sequence * input,
  cobot_interfaces__srv__LocateBlocks_Event__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    if (input->size > SIZE_MAX / sizeof(cobot_interfaces__srv__LocateBlocks_Event)) {
      return false;
    }
    const size_t allocation_size =
      input->size * sizeof(cobot_interfaces__srv__LocateBlocks_Event);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    cobot_interfaces__srv__LocateBlocks_Event * data =
      (cobot_interfaces__srv__LocateBlocks_Event *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!cobot_interfaces__srv__LocateBlocks_Event__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          cobot_interfaces__srv__LocateBlocks_Event__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!cobot_interfaces__srv__LocateBlocks_Event__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
