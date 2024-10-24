#include "../../include/jianqiao/heap_base.hpp"

#include <iostream>
#include <vector>
#include <algorithm>


using namespace Jianqiao;

void test_heap(){
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Jianqiao::make_heap(vec.begin(), vec.end());
    for(auto &elem : vec){
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    vec.push_back(10);
    Jianqiao::push_heap(vec.begin(), vec.end());
    for(auto &elem : vec){
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    Jianqiao :: pop_heap(vec.begin(), vec.end());
    vec.pop_back();
    for(auto &elem : vec){
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

int main(){
    test_heap();
    return 0;
}