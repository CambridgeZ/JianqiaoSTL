# JianqiaoSTL



## 1. Introduction

This is a simple STL implementation in C++. The main purpose of this project is to understand the basic principles of STL and to practice C++ programming.

## 2. Features

- [x] Vector
- [x] List
- [x] Stack
- [x] Queue
- [x] Priority Queue
- [ ] Deque
- [x] Map
- [x] Set
- [x] Multimap
- [x] Multiset
- [x] Unordered Map
- [x] Unordered Set
- [x] Unordered Multimap
- [x] Unordered Multiset
- [x] Iterator
- [ ] Reverse Iterator
- [x] Allocator
- [x] Function Object
- [x] Hash Function
- [x] Pair
- [ ] Tuple
- '...' means that the feature is not implemented yet.
- 'x' means that the feature is implemented.

## 3. How to use

1. Clone the repository.
2. Include the header file of the container you want to use. For example if you want to use vector, you should include the following line in your code.
```cpp
#include <jianqiao/jianqiao_vector.hpp>
```

3. add the following line in your cmake file.
```cmake
target_include_directories(your_target_name PRIVATE path_to_JianqiaoSTL)
```

for example in my test file you could find the following lines
```cmake
target_include_directories(test_sort PRIVATE
        ../../../include
)
```