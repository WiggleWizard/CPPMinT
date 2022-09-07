cmake_minimum_required(VERSION 3.2)
project(imgui)

CPMAddPackage(
    NAME imgui
    GITHUB_REPOSITORY ocornut/imgui
    VERSION 1.88)

set(IMGUI_SOURCES
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
    ${imgui_SOURCE_DIR}/imgui_demo.cpp

    ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp 
    ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

# build as a static library
add_library(imgui STATIC ${IMGUI_SOURCES})

# compile options
#target_compile_options(imgui PRIVATE -w)

# include libraries
target_include_directories(imgui PUBLIC ${imgui_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        glfw) # Mainly for auto include dirs