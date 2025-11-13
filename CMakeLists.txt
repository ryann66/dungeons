cmake_minimum_required(VERSION 3.31)
project(
    dungeons 
    VERSION 0.0 
    DESCRIPTION "2D Dungeon Crawler" 
    LANGUAGES C CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

find_package(SDL3 REQUIRED)
include_directories(${SDL3_INCLUDE_DIRS})

add_subdirectory(common)
add_subdirectory(menu)
