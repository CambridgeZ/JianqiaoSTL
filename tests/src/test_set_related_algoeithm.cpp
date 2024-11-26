//
// Created by Mac on 24-11-23.
//

// 测试和set相关的算法

#include "../../include/jianqiao/jianqiao_algorithm_base.hpp"
#include <iostream>
#include <set>

using std::set;

void test1(){
    set<int> S1 = {1, 2, 3, 4, 5};
    set<int> S2 = {3, 4, 5, 6, 7};

    set<int> S3;
    Jianqiao::set_union(S1.begin(), S1.end(), S2.begin(), S2.end(), inserter(S3, S3.begin()));

    for(auto i : S3){
        std::cout << i << " ";
    }

    std::cout << std::endl;

    set<int> S4;
    Jianqiao::set_intersection(S1.begin(), S1.end(), S2.begin(), S2.end(), inserter(S4, S4.begin()));

    for(auto i : S4){
        std::cout << i << " ";
    }
    std::cout<<std::endl;

    set<int> S5;
    Jianqiao::set_difference(S1.begin(), S1.end(), S2.begin(), S2.end(), inserter(S5, S5.begin()));

    for(auto i : S5){
        std::cout << i << " ";
    }
    std::cout<<std::endl;

    set<int> S6;
    Jianqiao::set_symmetric_difference(S1.begin(), S1.end(), S2.begin(), S2.end(), inserter(S6, S6.begin()));

    for(auto i : S6){
        std::cout << i << " ";
    }
    std::cout<<std::endl;


}

int main(){
//    test1();
    return 0;
}



