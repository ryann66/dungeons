aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)
add_library(menu ${SRC})

target_include_directories(menu PUBLIC ../include/menu)
target_include_directories(menu PRIVATE ../include/common)