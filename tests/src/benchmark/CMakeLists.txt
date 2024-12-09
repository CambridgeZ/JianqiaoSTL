cmake_minimum_required(VERSION 3.12)

project(benchmark)

set(CMAKE_CXX_STANDARD 17)

add_executable(benchmark main.cpp)

target_link_libraries(benchmark PRIVATE benchmark::benchmark)

# 添加 include 路径，确保包含 jianqiao 的完整路径

target_include_directories(test_sort PRIVATE
        ../../../include
        ../../../include/jianqiao
)