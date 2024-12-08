cmake_minimum_required(VERSION 3.12)

project(test_random_shuffle)

set(CMAKE_CXX_STANDARD 17)

add_executable(test_random_shuffle test_random_shuffle.cpp)

# 添加 gtest 子目录
add_subdirectory(../../googletest-1.15.2 gtest)

# 添加 gtest 链接库
target_link_libraries(test_random_shuffle gtest gtest_main)

# 添加 include 路径，确保包含 jianqiao 的完整路径
target_include_directories(test_random_shuffle PRIVATE
        ../../../include
        ../../../include/jianqiao
)


