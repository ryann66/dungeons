aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)
add_library(loader ${SRC})

set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

target_link_libraries(loader PRIVATE Threads::Threads SDL3::SDL3 SDL3_image::SDL3_image)

target_include_directories(loader PUBLIC ${CMAKE_SOURCE_DIR}/include/loader)
target_include_directories(loader PRIVATE ${CMAKE_SOURCE_DIR}/include/common)
