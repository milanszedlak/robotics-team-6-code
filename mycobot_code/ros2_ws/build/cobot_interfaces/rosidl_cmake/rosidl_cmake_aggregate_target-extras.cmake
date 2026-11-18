# generated from rosidl_cmake/cmake/rosidl_cmake_aggregate_target-extras.cmake.in

# Create a convenience aggregate target cobot_interfaces::cobot_interfaces
# that links all generated interface targets, so downstream packages can use
# a single modern CMake target name instead of ${cobot_interfaces_TARGETS}.
if(cobot_interfaces_TARGETS AND NOT TARGET cobot_interfaces::cobot_interfaces)
  add_library(cobot_interfaces::cobot_interfaces INTERFACE IMPORTED)
  set_target_properties(cobot_interfaces::cobot_interfaces PROPERTIES
    INTERFACE_LINK_LIBRARIES "${cobot_interfaces_TARGETS}")
endif()
