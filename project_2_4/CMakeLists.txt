cmake_minimum_required(VERSION 3.10)
project(light_controller)

set(CMAKE_CXX_STANDARD 17)

add_executable(light_controller light_controller.cpp)

add_custom_target(
  copy_resources_to_build
  ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/test_cases/ $<TARGET_FILE_DIR:light_controller>/test_cases
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/runner.sh $<TARGET_FILE_DIR:light_controller>/runner.sh
  DEPENDS ${CMAKE_SOURCE_DIR}/runner.sh
)
