add_executable(${PROJECT_NAME}
    Main.cpp
    EASTLMem.cpp)

target_link_directories(${PROJECT_NAME}
    PRIVATE
        .)

target_link_libraries(${PROJECT_NAME}
    EASTL
    spdlog)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
add_custom_target(NatVis SOURCES ${EASTL_SOURCE_DIR}/doc/EASTL.natvis)