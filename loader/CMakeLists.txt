aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)
add_library(loader ${SRC})

set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads)
target_link_libraries(loader PRIVATE Threads::Threads)

target_include_directories(loader PUBLIC ../include/loader)
target_include_directories(loader PRIVATE ../include/common)