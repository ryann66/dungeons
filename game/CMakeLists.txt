aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)
add_library(game ${SRC})

target_include_directories(game PUBLIC ${CMAKE_SOURCE_DIR}/include/game)
target_include_directories(game PRIVATE ${CMAKE_SOURCE_DIR}/include/common)
target_include_directories(game PRIVATE ${CMAKE_SOURCE_DIR}/include/loader)