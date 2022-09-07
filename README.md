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

Open `CMakeLists.txt` and rename the project.

```shell
mkdir build
cd build
cmake ..
```

## What comes with CPPMinT
The project contains a main entry point with some example code that demonstrates EASTL's `string` class and `spdlog`
printing. There is a very simple benchmarking class called `SimpleBench` rolled into the project as well, which is also
demonstrated in the entry point.

Beyond the above, you can view the library list below.

## Library List
Here's a list of libraries that can be picked from. Currently, there's no way to configure which ones will be compiled into
your project beyond editing `thirdparty/CMakeLists.txt` so all the following libs are compiled into your executable:
- [EASTL](https://github.com/electronicarts/EASTL) - Fantastic standard library from EA. Contains everything from the STD library set and then some.
- [spdlog](https://github.com/gabime/spdlog) - Super easy to use, minimal logging tool: `spdlog::info("{} iterations", i);`
- [fmt](https://github.com/fmtlib/fmt) - String formatter. Used in spdlog.
- [SkeletonMinRes](https://github.com/WiggleWizard/SkeletonMinRes) - Minimal automatic resource (glsl, scripts, textures, etc) embedding tool.
- [argparse](https://github.com/p-ranav/argparse) - Argument parser for modern C++.