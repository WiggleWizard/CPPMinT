CPPMinT
-------
A minimal C++ project template.

## Why
I bounce around a lot, with new ideas and things to try out. I frequently spin up various projects locally and spend far
too much time constantly writing new `CMakeList.txt` from scratch; the majority of them all the same. So this repo will
serve as my main template for all my experimental projects.

### Why not other project templates/bootstrappers
I just wanted my own, in my own style, with my own customizations.

## How to use
```shell
git clone https://github.com/wigglewizard/CPPMinT <projectname>
cd <projectname>
```

Open `CMakeLists.txt` and rename the project. Now generate project files:

```shell
mkdir build
cd build
cmake ..
```

# What comes with CPPMinT
## Firstparty
- Application base class ([ApplicationBase.h](src/ApplicationBase.h)).
    - Provides initialization and transitive methods for ImGui.
- Easy to use [logging]() macros to easily create categorized logs: `LOGGER(logger, MyApplicationCategory)`.
- [SimpleBench](src/SimpleBench.h) for very simple code timings.
- EASTL [bootstrapping](src/EASTLMem.cpp) + `eastl::string` [formatters](src/Logging.h) for use with `fmt` and `spdlog`.
- Application filled with examples of how to use each library and CPPMinT features.
- [Common.h](src/Common.h) with shorthands for commonly typed namespaces (like `ea` = `eastl`).

## Thirdparty
Currently, there's no way to configure which ones will be compiled into
your project beyond editing `thirdparty/CMakeLists.txt` so all the following libs are compiled into your executable:
- [CPM.cmake](https://github.com/cpm-cmake/CPM.cmake) - CMake dependency manager.
- [EASTL](https://github.com/electronicarts/EASTL) - Fantastic standard library from EA. Contains everything from the STD library set and then some.
- [spdlog](https://github.com/gabime/spdlog) - Super easy to use, minimal logging tool: `spdlog::info("{} iterations", i);`
- [fmt](https://github.com/fmtlib/fmt) - String formatter. Used in spdlog.
- [SkeletonMinRes](https://github.com/WiggleWizard/SkeletonMinRes) - Minimal automatic resource (glsl, scripts, textures, etc) embedding tool.
- [argparse](https://github.com/p-ranav/argparse) - Argument parser for modern C++.
- [glfw](https://github.com/glfw/glfw) - Windowing.
- [imgui](https://github.com/ocornut/imgui) - Immediate mode GUI.