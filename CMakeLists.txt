cmake_minimum_required(VERSION 3.17)
project(benchmark)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
add_executable(benchmark src/benchmark.cpp src/sockets.cpp include/sockets.h)