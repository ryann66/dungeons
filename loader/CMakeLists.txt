aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)
add_library(loader ${SRC})

target_include_directories(loader PUBLIC ../include/loader)