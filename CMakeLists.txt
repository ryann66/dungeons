cmake_minimum_required(VERSION 3.31)
project(
    dungeons 
    VERSION 0.0 
    DESCRIPTION "2D Dungeon Crawler" 
    LANGUAGES C CXX)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

find_package(SDL3 REQUIRED)
find_package(SDL3_ttf REQUIRED)
find_package(SDL3_image REQUIRED)

add_subdirectory(common)
add_subdirectory(menu)
add_subdirectory(game)
add_subdirectory(loader)

file(COPY ${CMAKE_SOURCE_DIR}/resources/ DESTINATION ${CMAKE_BINARY_DIR}/build/)