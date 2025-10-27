cmake_minimum_required(VERSION 3.31)
project(dungeons)

find_package(SDL3 REQUIRED)
include_directories(${SDL3_INCLUDE_DIRS})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
add_executable(dungeons common/main.cc)
target_link_libraries(dungeons SDL3::SDL3)
