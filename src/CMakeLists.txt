embed_resources(PROJECT_RESOURCES
    Data.json)

set(PROJECT_SOURCE_FILES
    Main.cpp
    EASTLMem.cpp)

set(PROJECT_LINK_DIRS
    .)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_FILES} ${PROJECT_RESOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${PROJECT_LINK_DIRS} ${PROJECT_RESOURCES_INCLUDE_DIR})

target_link_libraries(${PROJECT_NAME}
    EASTL
    spdlog
    SkeletonMinRes
    argparse)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
add_custom_target(NatVis SOURCES ${EASTL_SOURCE_DIR}/doc/EASTL.natvis)