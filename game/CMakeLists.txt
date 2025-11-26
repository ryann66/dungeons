aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)
add_library(game ${SRC})

target_include_directories(game PUBLIC ../include/game)
target_include_directories(game PRIVATE ../include/common)
target_include_directories(game PRIVATE ../include/loader)