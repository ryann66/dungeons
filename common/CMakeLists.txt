aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)
add_executable(dungeons ${SRC})
target_compile_definitions(dungeons PUBLIC "PROGRAM_NAME=\"${PROGRAM_NAME}\"")

target_include_directories(dungeons PRIVATE ../include/common)

target_link_libraries(dungeons menu SDL3)