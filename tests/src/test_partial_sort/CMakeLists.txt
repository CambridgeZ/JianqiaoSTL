cmake_minimum_required(VERSION 3.12)

project(test_partial_sort)

set(CMAKE_CXX_STANDARD 17)

add_executable(test_partial_sort test_partial_sort.cpp)

add_subdirectory(../../googletest-1.15.2 gtest)

target_link_libraries(test_partial_sort gtest gtest_main)

target_include_directories(test_partial_sort PRIVATE
        ../../../include
        ../../../include/jianqiao
)