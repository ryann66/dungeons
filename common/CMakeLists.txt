aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC)
add_executable(dungeons ${SRC})
target_compile_definitions(dungeons PRIVATE PROGRAM_NAME=\"${CMAKE_PROJECT_NAME}\")

target_link_libraries(dungeons menu loader SDL3::SDL3 SDL3_ttf::SDL3_ttf)

target_include_directories(dungeons PRIVATE ${CMAKE_SOURCE_DIR}/include/common)