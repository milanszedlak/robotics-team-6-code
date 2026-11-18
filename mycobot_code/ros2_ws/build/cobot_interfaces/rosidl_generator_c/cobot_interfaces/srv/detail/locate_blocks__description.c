// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from cobot_interfaces:srv/LocateBlocks.idl
// generated code does not contain a copyright notice

#include "cobot_interfaces/srv/detail/locate_blocks__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_cobot_interfaces
const rosidl_type_hash_t *
cobot_interfaces__srv__LocateBlocks__get_type_hash(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x2e, 0x63, 0xc3, 0x57, 0x1d, 0xbe, 0xda, 0x96,
      0x13, 0x53, 0x43, 0x00, 0x89, 0x94, 0x83, 0x7b,
      0x75, 0x44, 0xee, 0xdf, 0x71, 0xa0, 0x22, 0x58,
      0x10, 0x75, 0xe9, 0xa1, 0xc9, 0x28, 0x46, 0x75,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_cobot_interfaces
const rosidl_type_hash_t *
cobot_interfaces__srv__LocateBlocks_Request__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0x77, 0x1c, 0xcb, 0x87, 0xfe, 0x76, 0xd7, 0x4a,
      0xf8, 0x79, 0x70, 0x6c, 0x46, 0xf2, 0x47, 0x12,
      0x2f, 0x04, 0x2b, 0x8d, 0xeb, 0x81, 0xb0, 0x71,
      0xe5, 0xef, 0x69, 0x2b, 0x0c, 0x0f, 0xf7, 0x25,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_cobot_interfaces
const rosidl_type_hash_t *
cobot_interfaces__srv__LocateBlocks_Response__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xc9, 0x7b, 0x67, 0x07, 0x48, 0x96, 0xfe, 0x42,
      0xa9, 0xa3, 0x49, 0xab, 0xa7, 0x1b, 0xf0, 0x74,
      0x13, 0x28, 0xd7, 0xde, 0xd1, 0x56, 0xcc, 0x92,
      0x14, 0x1b, 0x13, 0x91, 0xed, 0x29, 0x5b, 0x9d,
    }};
  return &hash;
}

ROSIDL_GENERATOR_C_PUBLIC_cobot_interfaces
const rosidl_type_hash_t *
cobot_interfaces__srv__LocateBlocks_Event__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xe3, 0xc1, 0x03, 0x57, 0x06, 0x91, 0xec, 0x17,
      0x19, 0x17, 0xf7, 0x86, 0xe7, 0x6d, 0x85, 0x65,
      0x85, 0x97, 0xcb, 0xdf, 0x0e, 0x25, 0x47, 0xd5,
      0xcb, 0x15, 0x62, 0x36, 0xbd, 0x0b, 0xd7, 0xbe,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "builtin_interfaces/msg/detail/time__functions.h"
#include "service_msgs/msg/detail/service_event_info__functions.h"
#include "cobot_interfaces/msg/detail/block_info__functions.h"
#include "geometry_msgs/msg/detail/point__functions.h"

// Hashes for external referenced types
#ifndef NDEBUG
static const rosidl_type_hash_t builtin_interfaces__msg__Time__EXPECTED_HASH = {1, {
    0xb1, 0x06, 0x23, 0x5e, 0x25, 0xa4, 0xc5, 0xed,
    0x35, 0x09, 0x8a, 0xa0, 0xa6, 0x1a, 0x3e, 0xe9,
    0xc9, 0xb1, 0x8d, 0x19, 0x7f, 0x39, 0x8b, 0x0e,
    0x42, 0x06, 0xce, 0xa9, 0xac, 0xf9, 0xc1, 0x97,
  }};
static const rosidl_type_hash_t cobot_interfaces__msg__BlockInfo__EXPECTED_HASH = {1, {
    0xc9, 0xb2, 0xd3, 0x0f, 0xef, 0x33, 0x17, 0xeb,
    0xfc, 0x0a, 0x31, 0x73, 0xa4, 0x3c, 0x5c, 0x11,
    0xaa, 0x69, 0x50, 0x89, 0x69, 0xb0, 0xde, 0x17,
    0xc1, 0x21, 0xd2, 0x9e, 0xc8, 0xf1, 0xc4, 0x0c,
  }};
static const rosidl_type_hash_t geometry_msgs__msg__Point__EXPECTED_HASH = {1, {
    0x69, 0x63, 0x08, 0x48, 0x42, 0xa9, 0xb0, 0x44,
    0x94, 0xd6, 0xb2, 0x94, 0x1d, 0x11, 0x44, 0x47,
    0x08, 0xd8, 0x92, 0xda, 0x2f, 0x4b, 0x09, 0x84,
    0x3b, 0x9c, 0x43, 0xf4, 0x2a, 0x7f, 0x68, 0x81,
  }};
static const rosidl_type_hash_t service_msgs__msg__ServiceEventInfo__EXPECTED_HASH = {1, {
    0x41, 0xbc, 0xbb, 0xe0, 0x7a, 0x75, 0xc9, 0xb5,
    0x2b, 0xc9, 0x6b, 0xfd, 0x5c, 0x24, 0xd7, 0xf0,
    0xfc, 0x0a, 0x08, 0xc0, 0xcb, 0x79, 0x21, 0xb3,
    0x37, 0x3c, 0x57, 0x32, 0x34, 0x5a, 0x6f, 0x45,
  }};
#endif

static char cobot_interfaces__srv__LocateBlocks__TYPE_NAME[] = "cobot_interfaces/srv/LocateBlocks";
static char builtin_interfaces__msg__Time__TYPE_NAME[] = "builtin_interfaces/msg/Time";
static char cobot_interfaces__msg__BlockInfo__TYPE_NAME[] = "cobot_interfaces/msg/BlockInfo";
static char cobot_interfaces__srv__LocateBlocks_Event__TYPE_NAME[] = "cobot_interfaces/srv/LocateBlocks_Event";
static char cobot_interfaces__srv__LocateBlocks_Request__TYPE_NAME[] = "cobot_interfaces/srv/LocateBlocks_Request";
static char cobot_interfaces__srv__LocateBlocks_Response__TYPE_NAME[] = "cobot_interfaces/srv/LocateBlocks_Response";
static char geometry_msgs__msg__Point__TYPE_NAME[] = "geometry_msgs/msg/Point";
static char service_msgs__msg__ServiceEventInfo__TYPE_NAME[] = "service_msgs/msg/ServiceEventInfo";

// Define type names, field names, and default values
static char cobot_interfaces__srv__LocateBlocks__FIELD_NAME__request_message[] = "request_message";
static char cobot_interfaces__srv__LocateBlocks__FIELD_NAME__response_message[] = "response_message";
static char cobot_interfaces__srv__LocateBlocks__FIELD_NAME__event_message[] = "event_message";

static rosidl_runtime_c__type_description__Field cobot_interfaces__srv__LocateBlocks__FIELDS[] = {
  {
    {cobot_interfaces__srv__LocateBlocks__FIELD_NAME__request_message, 15, 15},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {cobot_interfaces__srv__LocateBlocks_Request__TYPE_NAME, 41, 41},
    },
    {NULL, 0, 0},
  },
  {
    {cobot_interfaces__srv__LocateBlocks__FIELD_NAME__response_message, 16, 16},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {cobot_interfaces__srv__LocateBlocks_Response__TYPE_NAME, 42, 42},
    },
    {NULL, 0, 0},
  },
  {
    {cobot_interfaces__srv__LocateBlocks__FIELD_NAME__event_message, 13, 13},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {cobot_interfaces__srv__LocateBlocks_Event__TYPE_NAME, 39, 39},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription cobot_interfaces__srv__LocateBlocks__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {cobot_interfaces__msg__BlockInfo__TYPE_NAME, 30, 30},
    {NULL, 0, 0},
  },
  {
    {cobot_interfaces__srv__LocateBlocks_Event__TYPE_NAME, 39, 39},
    {NULL, 0, 0},
  },
  {
    {cobot_interfaces__srv__LocateBlocks_Request__TYPE_NAME, 41, 41},
    {NULL, 0, 0},
  },
  {
    {cobot_interfaces__srv__LocateBlocks_Response__TYPE_NAME, 42, 42},
    {NULL, 0, 0},
  },
  {
    {geometry_msgs__msg__Point__TYPE_NAME, 23, 23},
    {NULL, 0, 0},
  },
  {
    {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
cobot_interfaces__srv__LocateBlocks__get_type_description(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {cobot_interfaces__srv__LocateBlocks__TYPE_NAME, 33, 33},
      {cobot_interfaces__srv__LocateBlocks__FIELDS, 3, 3},
    },
    {cobot_interfaces__srv__LocateBlocks__REFERENCED_TYPE_DESCRIPTIONS, 7, 7},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&cobot_interfaces__msg__BlockInfo__EXPECTED_HASH, cobot_interfaces__msg__BlockInfo__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = cobot_interfaces__msg__BlockInfo__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[2].fields = cobot_interfaces__srv__LocateBlocks_Event__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[3].fields = cobot_interfaces__srv__LocateBlocks_Request__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[4].fields = cobot_interfaces__srv__LocateBlocks_Response__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&geometry_msgs__msg__Point__EXPECTED_HASH, geometry_msgs__msg__Point__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[5].fields = geometry_msgs__msg__Point__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&service_msgs__msg__ServiceEventInfo__EXPECTED_HASH, service_msgs__msg__ServiceEventInfo__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[6].fields = service_msgs__msg__ServiceEventInfo__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char cobot_interfaces__srv__LocateBlocks_Request__FIELD_NAME__color[] = "color";
static char cobot_interfaces__srv__LocateBlocks_Request__FIELD_NAME__go_home[] = "go_home";

static rosidl_runtime_c__type_description__Field cobot_interfaces__srv__LocateBlocks_Request__FIELDS[] = {
  {
    {cobot_interfaces__srv__LocateBlocks_Request__FIELD_NAME__color, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {cobot_interfaces__srv__LocateBlocks_Request__FIELD_NAME__go_home, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
cobot_interfaces__srv__LocateBlocks_Request__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {cobot_interfaces__srv__LocateBlocks_Request__TYPE_NAME, 41, 41},
      {cobot_interfaces__srv__LocateBlocks_Request__FIELDS, 2, 2},
    },
    {NULL, 0, 0},
  };
  if (!constructed) {
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char cobot_interfaces__srv__LocateBlocks_Response__FIELD_NAME__success[] = "success";
static char cobot_interfaces__srv__LocateBlocks_Response__FIELD_NAME__message[] = "message";
static char cobot_interfaces__srv__LocateBlocks_Response__FIELD_NAME__blocks[] = "blocks";

static rosidl_runtime_c__type_description__Field cobot_interfaces__srv__LocateBlocks_Response__FIELDS[] = {
  {
    {cobot_interfaces__srv__LocateBlocks_Response__FIELD_NAME__success, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {cobot_interfaces__srv__LocateBlocks_Response__FIELD_NAME__message, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {cobot_interfaces__srv__LocateBlocks_Response__FIELD_NAME__blocks, 6, 6},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_UNBOUNDED_SEQUENCE,
      0,
      0,
      {cobot_interfaces__msg__BlockInfo__TYPE_NAME, 30, 30},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription cobot_interfaces__srv__LocateBlocks_Response__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {cobot_interfaces__msg__BlockInfo__TYPE_NAME, 30, 30},
    {NULL, 0, 0},
  },
  {
    {geometry_msgs__msg__Point__TYPE_NAME, 23, 23},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
cobot_interfaces__srv__LocateBlocks_Response__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {cobot_interfaces__srv__LocateBlocks_Response__TYPE_NAME, 42, 42},
      {cobot_interfaces__srv__LocateBlocks_Response__FIELDS, 3, 3},
    },
    {cobot_interfaces__srv__LocateBlocks_Response__REFERENCED_TYPE_DESCRIPTIONS, 2, 2},
  };
  if (!constructed) {
    assert(0 == memcmp(&cobot_interfaces__msg__BlockInfo__EXPECTED_HASH, cobot_interfaces__msg__BlockInfo__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = cobot_interfaces__msg__BlockInfo__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&geometry_msgs__msg__Point__EXPECTED_HASH, geometry_msgs__msg__Point__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = geometry_msgs__msg__Point__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}
// Define type names, field names, and default values
static char cobot_interfaces__srv__LocateBlocks_Event__FIELD_NAME__info[] = "info";
static char cobot_interfaces__srv__LocateBlocks_Event__FIELD_NAME__request[] = "request";
static char cobot_interfaces__srv__LocateBlocks_Event__FIELD_NAME__response[] = "response";

static rosidl_runtime_c__type_description__Field cobot_interfaces__srv__LocateBlocks_Event__FIELDS[] = {
  {
    {cobot_interfaces__srv__LocateBlocks_Event__FIELD_NAME__info, 4, 4},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    },
    {NULL, 0, 0},
  },
  {
    {cobot_interfaces__srv__LocateBlocks_Event__FIELD_NAME__request, 7, 7},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_BOUNDED_SEQUENCE,
      1,
      0,
      {cobot_interfaces__srv__LocateBlocks_Request__TYPE_NAME, 41, 41},
    },
    {NULL, 0, 0},
  },
  {
    {cobot_interfaces__srv__LocateBlocks_Event__FIELD_NAME__response, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE_BOUNDED_SEQUENCE,
      1,
      0,
      {cobot_interfaces__srv__LocateBlocks_Response__TYPE_NAME, 42, 42},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription cobot_interfaces__srv__LocateBlocks_Event__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {builtin_interfaces__msg__Time__TYPE_NAME, 27, 27},
    {NULL, 0, 0},
  },
  {
    {cobot_interfaces__msg__BlockInfo__TYPE_NAME, 30, 30},
    {NULL, 0, 0},
  },
  {
    {cobot_interfaces__srv__LocateBlocks_Request__TYPE_NAME, 41, 41},
    {NULL, 0, 0},
  },
  {
    {cobot_interfaces__srv__LocateBlocks_Response__TYPE_NAME, 42, 42},
    {NULL, 0, 0},
  },
  {
    {geometry_msgs__msg__Point__TYPE_NAME, 23, 23},
    {NULL, 0, 0},
  },
  {
    {service_msgs__msg__ServiceEventInfo__TYPE_NAME, 33, 33},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
cobot_interfaces__srv__LocateBlocks_Event__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {cobot_interfaces__srv__LocateBlocks_Event__TYPE_NAME, 39, 39},
      {cobot_interfaces__srv__LocateBlocks_Event__FIELDS, 3, 3},
    },
    {cobot_interfaces__srv__LocateBlocks_Event__REFERENCED_TYPE_DESCRIPTIONS, 6, 6},
  };
  if (!constructed) {
    assert(0 == memcmp(&builtin_interfaces__msg__Time__EXPECTED_HASH, builtin_interfaces__msg__Time__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = builtin_interfaces__msg__Time__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&cobot_interfaces__msg__BlockInfo__EXPECTED_HASH, cobot_interfaces__msg__BlockInfo__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[1].fields = cobot_interfaces__msg__BlockInfo__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[2].fields = cobot_interfaces__srv__LocateBlocks_Request__get_type_description(NULL)->type_description.fields;
    description.referenced_type_descriptions.data[3].fields = cobot_interfaces__srv__LocateBlocks_Response__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&geometry_msgs__msg__Point__EXPECTED_HASH, geometry_msgs__msg__Point__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[4].fields = geometry_msgs__msg__Point__get_type_description(NULL)->type_description.fields;
    assert(0 == memcmp(&service_msgs__msg__ServiceEventInfo__EXPECTED_HASH, service_msgs__msg__ServiceEventInfo__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[5].fields = service_msgs__msg__ServiceEventInfo__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# /arm/locate_blocks: report every block the camera sees, in the arm base frame.\n"
  "string color        # only this colour; \"\" = all colours\n"
  "bool go_home        # true = move the arm to its home pose (out of the camera view) first\n"
  "---\n"
  "bool success\n"
  "string message\n"
  "cobot_interfaces/BlockInfo[] blocks   # sorted: graspable first, then by confidence";

static char srv_encoding[] = "srv";
static char implicit_encoding[] = "implicit";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
cobot_interfaces__srv__LocateBlocks__get_individual_type_description_source(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {cobot_interfaces__srv__LocateBlocks__TYPE_NAME, 33, 33},
    {srv_encoding, 3, 3},
    {toplevel_type_raw_source, 344, 344},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
cobot_interfaces__srv__LocateBlocks_Request__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {cobot_interfaces__srv__LocateBlocks_Request__TYPE_NAME, 41, 41},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
cobot_interfaces__srv__LocateBlocks_Response__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {cobot_interfaces__srv__LocateBlocks_Response__TYPE_NAME, 42, 42},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource *
cobot_interfaces__srv__LocateBlocks_Event__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {cobot_interfaces__srv__LocateBlocks_Event__TYPE_NAME, 39, 39},
    {implicit_encoding, 8, 8},
    {NULL, 0, 0},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
cobot_interfaces__srv__LocateBlocks__get_type_description_sources(
  const rosidl_service_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[8];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 8, 8};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *cobot_interfaces__srv__LocateBlocks__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *cobot_interfaces__msg__BlockInfo__get_individual_type_description_source(NULL);
    sources[3] = *cobot_interfaces__srv__LocateBlocks_Event__get_individual_type_description_source(NULL);
    sources[4] = *cobot_interfaces__srv__LocateBlocks_Request__get_individual_type_description_source(NULL);
    sources[5] = *cobot_interfaces__srv__LocateBlocks_Response__get_individual_type_description_source(NULL);
    sources[6] = *geometry_msgs__msg__Point__get_individual_type_description_source(NULL);
    sources[7] = *service_msgs__msg__ServiceEventInfo__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
cobot_interfaces__srv__LocateBlocks_Request__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[1];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 1, 1};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *cobot_interfaces__srv__LocateBlocks_Request__get_individual_type_description_source(NULL),
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
cobot_interfaces__srv__LocateBlocks_Response__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[3];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 3, 3};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *cobot_interfaces__srv__LocateBlocks_Response__get_individual_type_description_source(NULL),
    sources[1] = *cobot_interfaces__msg__BlockInfo__get_individual_type_description_source(NULL);
    sources[2] = *geometry_msgs__msg__Point__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
cobot_interfaces__srv__LocateBlocks_Event__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[7];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 7, 7};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *cobot_interfaces__srv__LocateBlocks_Event__get_individual_type_description_source(NULL),
    sources[1] = *builtin_interfaces__msg__Time__get_individual_type_description_source(NULL);
    sources[2] = *cobot_interfaces__msg__BlockInfo__get_individual_type_description_source(NULL);
    sources[3] = *cobot_interfaces__srv__LocateBlocks_Request__get_individual_type_description_source(NULL);
    sources[4] = *cobot_interfaces__srv__LocateBlocks_Response__get_individual_type_description_source(NULL);
    sources[5] = *geometry_msgs__msg__Point__get_individual_type_description_source(NULL);
    sources[6] = *service_msgs__msg__ServiceEventInfo__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
