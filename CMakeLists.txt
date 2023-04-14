cmake_minimum_required(VERSION 3.17)
project(benchmark_projects)

set(CMAKE_CXX_STANDARD 14)

add_library(trase STATIC IMPORTED)
set_target_properties(trase PROPERTIES
        IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/common/trase/lib/libtrase.a)
add_dependencies(trase benchmark_projects)

include_directories(common/trase/src)
include_directories(include)

add_executable(benchmark src/benchmark.cpp src/sockets.cpp 
include/sockets.h src/tests.cpp include/tests.h 
include/stat.h src/stat.cpp include/plotting.h src/plotting.cpp)

target_link_libraries( benchmark
        PRIVATE
        trase ws2_32 -static -static-libgcc -static-libstdc++
        )