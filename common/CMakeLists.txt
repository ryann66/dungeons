add_executable(dungeons main.cc)
target_sources(dungeons PRIVATE sceneManager.cc)

target_include_directories(dungeons PUBLIC ../include/common)

target_link_libraries(dungeons menu SDL3)