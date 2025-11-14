aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)
add_executable(dungeons ${SRC})
target_compile_definitions(dungeons PRIVATE PROGRAM_NAME=\"${CMAKE_PROJECT_NAME}\")

target_include_directories(dungeons PRIVATE ../include/common)

target_link_libraries(dungeons menu SDL3)