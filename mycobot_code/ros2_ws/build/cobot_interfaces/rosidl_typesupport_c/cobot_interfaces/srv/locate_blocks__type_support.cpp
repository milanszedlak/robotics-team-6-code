// generated from rosidl_typesupport_c/resource/idl__type_support.cpp.em
// with input from cobot_interfaces:srv/LocateBlocks.idl
// generated code does not contain a copyright notice

#include "cstddef"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "cobot_interfaces/srv/detail/locate_blocks__struct.h"
#include "cobot_interfaces/srv/detail/locate_blocks__type_support.h"
#include "cobot_interfaces/srv/detail/locate_blocks__functions.h"
#include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/message_type_support_dispatch.h"
#include "rosidl_typesupport_c/type_support_map.h"
#include "rosidl_typesupport_c/visibility_control.h"
#include "rosidl_typesupport_interface/macros.h"

namespace cobot_interfaces
{

namespace srv
{

namespace rosidl_typesupport_c
{

typedef struct _LocateBlocks_Request_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _LocateBlocks_Request_type_support_ids_t;

static const _LocateBlocks_Request_type_support_ids_t _LocateBlocks_Request_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _LocateBlocks_Request_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _LocateBlocks_Request_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _LocateBlocks_Request_type_support_symbol_names_t _LocateBlocks_Request_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, cobot_interfaces, srv, LocateBlocks_Request)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot_interfaces, srv, LocateBlocks_Request)),
  }
};

typedef struct _LocateBlocks_Request_type_support_data_t
{
  void * data[2];
} _LocateBlocks_Request_type_support_data_t;

static _LocateBlocks_Request_type_support_data_t _LocateBlocks_Request_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _LocateBlocks_Request_message_typesupport_map = {
  2,
  "cobot_interfaces",
  &_LocateBlocks_Request_message_typesupport_ids.typesupport_identifier[0],
  &_LocateBlocks_Request_message_typesupport_symbol_names.symbol_name[0],
  &_LocateBlocks_Request_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t LocateBlocks_Request_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_LocateBlocks_Request_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &cobot_interfaces__srv__LocateBlocks_Request__get_type_hash,
  &cobot_interfaces__srv__LocateBlocks_Request__get_type_description,
  &cobot_interfaces__srv__LocateBlocks_Request__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace cobot_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, cobot_interfaces, srv, LocateBlocks_Request)() {
  return &::cobot_interfaces::srv::rosidl_typesupport_c::LocateBlocks_Request_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "cobot_interfaces/srv/detail/locate_blocks__struct.h"
// already included above
// #include "cobot_interfaces/srv/detail/locate_blocks__type_support.h"
// already included above
// #include "cobot_interfaces/srv/detail/locate_blocks__functions.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace cobot_interfaces
{

namespace srv
{

namespace rosidl_typesupport_c
{

typedef struct _LocateBlocks_Response_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _LocateBlocks_Response_type_support_ids_t;

static const _LocateBlocks_Response_type_support_ids_t _LocateBlocks_Response_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _LocateBlocks_Response_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _LocateBlocks_Response_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _LocateBlocks_Response_type_support_symbol_names_t _LocateBlocks_Response_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, cobot_interfaces, srv, LocateBlocks_Response)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot_interfaces, srv, LocateBlocks_Response)),
  }
};

typedef struct _LocateBlocks_Response_type_support_data_t
{
  void * data[2];
} _LocateBlocks_Response_type_support_data_t;

static _LocateBlocks_Response_type_support_data_t _LocateBlocks_Response_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _LocateBlocks_Response_message_typesupport_map = {
  2,
  "cobot_interfaces",
  &_LocateBlocks_Response_message_typesupport_ids.typesupport_identifier[0],
  &_LocateBlocks_Response_message_typesupport_symbol_names.symbol_name[0],
  &_LocateBlocks_Response_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t LocateBlocks_Response_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_LocateBlocks_Response_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &cobot_interfaces__srv__LocateBlocks_Response__get_type_hash,
  &cobot_interfaces__srv__LocateBlocks_Response__get_type_description,
  &cobot_interfaces__srv__LocateBlocks_Response__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace cobot_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, cobot_interfaces, srv, LocateBlocks_Response)() {
  return &::cobot_interfaces::srv::rosidl_typesupport_c::LocateBlocks_Response_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
// already included above
// #include "rosidl_runtime_c/message_type_support_struct.h"
// already included above
// #include "cobot_interfaces/srv/detail/locate_blocks__struct.h"
// already included above
// #include "cobot_interfaces/srv/detail/locate_blocks__type_support.h"
// already included above
// #include "cobot_interfaces/srv/detail/locate_blocks__functions.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
// already included above
// #include "rosidl_typesupport_c/message_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_c/visibility_control.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"

namespace cobot_interfaces
{

namespace srv
{

namespace rosidl_typesupport_c
{

typedef struct _LocateBlocks_Event_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _LocateBlocks_Event_type_support_ids_t;

static const _LocateBlocks_Event_type_support_ids_t _LocateBlocks_Event_message_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _LocateBlocks_Event_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _LocateBlocks_Event_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _LocateBlocks_Event_type_support_symbol_names_t _LocateBlocks_Event_message_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, cobot_interfaces, srv, LocateBlocks_Event)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot_interfaces, srv, LocateBlocks_Event)),
  }
};

typedef struct _LocateBlocks_Event_type_support_data_t
{
  void * data[2];
} _LocateBlocks_Event_type_support_data_t;

static _LocateBlocks_Event_type_support_data_t _LocateBlocks_Event_message_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _LocateBlocks_Event_message_typesupport_map = {
  2,
  "cobot_interfaces",
  &_LocateBlocks_Event_message_typesupport_ids.typesupport_identifier[0],
  &_LocateBlocks_Event_message_typesupport_symbol_names.symbol_name[0],
  &_LocateBlocks_Event_message_typesupport_data.data[0],
};

static const rosidl_message_type_support_t LocateBlocks_Event_message_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_LocateBlocks_Event_message_typesupport_map),
  rosidl_typesupport_c__get_message_typesupport_handle_function,
  &cobot_interfaces__srv__LocateBlocks_Event__get_type_hash,
  &cobot_interfaces__srv__LocateBlocks_Event__get_type_description,
  &cobot_interfaces__srv__LocateBlocks_Event__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace cobot_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_c, cobot_interfaces, srv, LocateBlocks_Event)() {
  return &::cobot_interfaces::srv::rosidl_typesupport_c::LocateBlocks_Event_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif

// already included above
// #include "cstddef"
#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "cobot_interfaces/srv/detail/locate_blocks__type_support.h"
// already included above
// #include "rosidl_typesupport_c/identifier.h"
#include "rosidl_typesupport_c/service_type_support_dispatch.h"
// already included above
// #include "rosidl_typesupport_c/type_support_map.h"
// already included above
// #include "rosidl_typesupport_interface/macros.h"
#include "service_msgs/msg/service_event_info.h"
#include "builtin_interfaces/msg/time.h"

namespace cobot_interfaces
{

namespace srv
{

namespace rosidl_typesupport_c
{
typedef struct _LocateBlocks_type_support_ids_t
{
  const char * typesupport_identifier[2];
} _LocateBlocks_type_support_ids_t;

static const _LocateBlocks_type_support_ids_t _LocateBlocks_service_typesupport_ids = {
  {
    "rosidl_typesupport_fastrtps_c",  // ::rosidl_typesupport_fastrtps_c::typesupport_identifier,
    "rosidl_typesupport_introspection_c",  // ::rosidl_typesupport_introspection_c::typesupport_identifier,
  }
};

typedef struct _LocateBlocks_type_support_symbol_names_t
{
  const char * symbol_name[2];
} _LocateBlocks_type_support_symbol_names_t;

#define STRINGIFY_(s) #s
#define STRINGIFY(s) STRINGIFY_(s)

static const _LocateBlocks_type_support_symbol_names_t _LocateBlocks_service_typesupport_symbol_names = {
  {
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, cobot_interfaces, srv, LocateBlocks)),
    STRINGIFY(ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, cobot_interfaces, srv, LocateBlocks)),
  }
};

typedef struct _LocateBlocks_type_support_data_t
{
  void * data[2];
} _LocateBlocks_type_support_data_t;

static _LocateBlocks_type_support_data_t _LocateBlocks_service_typesupport_data = {
  {
    0,  // will store the shared library later
    0,  // will store the shared library later
  }
};

static const type_support_map_t _LocateBlocks_service_typesupport_map = {
  2,
  "cobot_interfaces",
  &_LocateBlocks_service_typesupport_ids.typesupport_identifier[0],
  &_LocateBlocks_service_typesupport_symbol_names.symbol_name[0],
  &_LocateBlocks_service_typesupport_data.data[0],
};

static const rosidl_service_type_support_t LocateBlocks_service_type_support_handle = {
  rosidl_typesupport_c__typesupport_identifier,
  reinterpret_cast<const type_support_map_t *>(&_LocateBlocks_service_typesupport_map),
  rosidl_typesupport_c__get_service_typesupport_handle_function,
  &LocateBlocks_Request_message_type_support_handle,
  &LocateBlocks_Response_message_type_support_handle,
  &LocateBlocks_Event_message_type_support_handle,
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_CREATE_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    cobot_interfaces,
    srv,
    LocateBlocks
  ),
  ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_DESTROY_EVENT_MESSAGE_SYMBOL_NAME(
    rosidl_typesupport_c,
    cobot_interfaces,
    srv,
    LocateBlocks
  ),
  &cobot_interfaces__srv__LocateBlocks__get_type_hash,
  &cobot_interfaces__srv__LocateBlocks__get_type_description,
  &cobot_interfaces__srv__LocateBlocks__get_type_description_sources,
};

}  // namespace rosidl_typesupport_c

}  // namespace srv

}  // namespace cobot_interfaces

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_c, cobot_interfaces, srv, LocateBlocks)() {
  return &::cobot_interfaces::srv::rosidl_typesupport_c::LocateBlocks_service_type_support_handle;
}

#ifdef __cplusplus
}
#endif
