cmake_minimum_required(VERSION 3.8)
project(leo_description)

find_package(ament_cmake REQUIRED)

install(
  DIRECTORY urdf launch models
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
