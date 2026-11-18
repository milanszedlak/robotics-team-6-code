// generated from rosidl_generator_c/resource/idl__description.c.em
// with input from cobot_interfaces:msg/BlockInfo.idl
// generated code does not contain a copyright notice

#include "cobot_interfaces/msg/detail/block_info__functions.h"

ROSIDL_GENERATOR_C_PUBLIC_cobot_interfaces
const rosidl_type_hash_t *
cobot_interfaces__msg__BlockInfo__get_type_hash(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_type_hash_t hash = {1, {
      0xc9, 0xb2, 0xd3, 0x0f, 0xef, 0x33, 0x17, 0xeb,
      0xfc, 0x0a, 0x31, 0x73, 0xa4, 0x3c, 0x5c, 0x11,
      0xaa, 0x69, 0x50, 0x89, 0x69, 0xb0, 0xde, 0x17,
      0xc1, 0x21, 0xd2, 0x9e, 0xc8, 0xf1, 0xc4, 0x0c,
    }};
  return &hash;
}

#include <assert.h>
#include <string.h>

// Include directives for referenced types
#include "geometry_msgs/msg/detail/point__functions.h"

// Hashes for external referenced types
#ifndef NDEBUG
static const rosidl_type_hash_t geometry_msgs__msg__Point__EXPECTED_HASH = {1, {
    0x69, 0x63, 0x08, 0x48, 0x42, 0xa9, 0xb0, 0x44,
    0x94, 0xd6, 0xb2, 0x94, 0x1d, 0x11, 0x44, 0x47,
    0x08, 0xd8, 0x92, 0xda, 0x2f, 0x4b, 0x09, 0x84,
    0x3b, 0x9c, 0x43, 0xf4, 0x2a, 0x7f, 0x68, 0x81,
  }};
#endif

static char cobot_interfaces__msg__BlockInfo__TYPE_NAME[] = "cobot_interfaces/msg/BlockInfo";
static char geometry_msgs__msg__Point__TYPE_NAME[] = "geometry_msgs/msg/Point";

// Define type names, field names, and default values
static char cobot_interfaces__msg__BlockInfo__FIELD_NAME__color[] = "color";
static char cobot_interfaces__msg__BlockInfo__FIELD_NAME__confidence[] = "confidence";
static char cobot_interfaces__msg__BlockInfo__FIELD_NAME__graspable[] = "graspable";
static char cobot_interfaces__msg__BlockInfo__FIELD_NAME__position[] = "position";
static char cobot_interfaces__msg__BlockInfo__FIELD_NAME__grasp_yaw[] = "grasp_yaw";
static char cobot_interfaces__msg__BlockInfo__FIELD_NAME__width[] = "width";

static rosidl_runtime_c__type_description__Field cobot_interfaces__msg__BlockInfo__FIELDS[] = {
  {
    {cobot_interfaces__msg__BlockInfo__FIELD_NAME__color, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_STRING,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {cobot_interfaces__msg__BlockInfo__FIELD_NAME__confidence, 10, 10},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_FLOAT,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {cobot_interfaces__msg__BlockInfo__FIELD_NAME__graspable, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_BOOLEAN,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {cobot_interfaces__msg__BlockInfo__FIELD_NAME__position, 8, 8},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_NESTED_TYPE,
      0,
      0,
      {geometry_msgs__msg__Point__TYPE_NAME, 23, 23},
    },
    {NULL, 0, 0},
  },
  {
    {cobot_interfaces__msg__BlockInfo__FIELD_NAME__grasp_yaw, 9, 9},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
  {
    {cobot_interfaces__msg__BlockInfo__FIELD_NAME__width, 5, 5},
    {
      rosidl_runtime_c__type_description__FieldType__FIELD_TYPE_DOUBLE,
      0,
      0,
      {NULL, 0, 0},
    },
    {NULL, 0, 0},
  },
};

static rosidl_runtime_c__type_description__IndividualTypeDescription cobot_interfaces__msg__BlockInfo__REFERENCED_TYPE_DESCRIPTIONS[] = {
  {
    {geometry_msgs__msg__Point__TYPE_NAME, 23, 23},
    {NULL, 0, 0},
  },
};

const rosidl_runtime_c__type_description__TypeDescription *
cobot_interfaces__msg__BlockInfo__get_type_description(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static bool constructed = false;
  static const rosidl_runtime_c__type_description__TypeDescription description = {
    {
      {cobot_interfaces__msg__BlockInfo__TYPE_NAME, 30, 30},
      {cobot_interfaces__msg__BlockInfo__FIELDS, 6, 6},
    },
    {cobot_interfaces__msg__BlockInfo__REFERENCED_TYPE_DESCRIPTIONS, 1, 1},
  };
  if (!constructed) {
    assert(0 == memcmp(&geometry_msgs__msg__Point__EXPECTED_HASH, geometry_msgs__msg__Point__get_type_hash(NULL), sizeof(rosidl_type_hash_t)));
    description.referenced_type_descriptions.data[0].fields = geometry_msgs__msg__Point__get_type_description(NULL)->type_description.fields;
    constructed = true;
  }
  return &description;
}

static char toplevel_type_raw_source[] =
  "# One block as seen by the arm, already converted to the arm base frame (base_link).\n"
  "# Returned by the /arm/locate_blocks service.\n"
  "\n"
  "string color                    # lower-case colour name (\"red\", \"blue\", ...)\n"
  "float32 confidence              # 0.0 ~ 1.0, from the vision node\n"
  "bool graspable                  # vision says pick it, confidence is high enough, and it fits the gripper\n"
  "\n"
  "geometry_msgs/Point position    # centre of the block's TOP face in base_link [m]\n"
  "float64 grasp_yaw               # finger closing direction in the base XY plane [rad] (0 if no corners)\n"
  "float64 width                   # block width across the fingers [m] (0 if no corners)";

static char msg_encoding[] = "msg";

// Define all individual source functions

const rosidl_runtime_c__type_description__TypeSource *
cobot_interfaces__msg__BlockInfo__get_individual_type_description_source(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static const rosidl_runtime_c__type_description__TypeSource source = {
    {cobot_interfaces__msg__BlockInfo__TYPE_NAME, 30, 30},
    {msg_encoding, 3, 3},
    {toplevel_type_raw_source, 656, 656},
  };
  return &source;
}

const rosidl_runtime_c__type_description__TypeSource__Sequence *
cobot_interfaces__msg__BlockInfo__get_type_description_sources(
  const rosidl_message_type_support_t * type_support)
{
  (void)type_support;
  static rosidl_runtime_c__type_description__TypeSource sources[2];
  static const rosidl_runtime_c__type_description__TypeSource__Sequence source_sequence = {sources, 2, 2};
  static bool constructed = false;
  if (!constructed) {
    sources[0] = *cobot_interfaces__msg__BlockInfo__get_individual_type_description_source(NULL),
    sources[1] = *geometry_msgs__msg__Point__get_individual_type_description_source(NULL);
    constructed = true;
  }
  return &source_sequence;
}
