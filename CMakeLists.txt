cmake_minimum_required(VERSION 3.31)
project(dungeons)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)
add_executable(dungeons common/main.cc)
