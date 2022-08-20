# EABase
set(EABASE_BUILD_TESTS OFF CACHE BOOL "")
add_subdirectory(EABase/repo)

# EASTL
set(EASTL_BUILD_BENCHMARK OFF CACHE BOOL "")
set(EASTL_BUILD_TESTS OFF CACHE BOOL "")
add_subdirectory(EASTL/repo)

# spdlog
add_subdirectory(spdlog/repo)