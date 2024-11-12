//
// Created by Mac on 24-11-12.
//
#include "../../include/jianqiao/jianqiao_numeric.hpp"

#include <iostream>

using std::endl;
using std::cout;

void testaccumulate(){
    int a[] = {1, 2, 3, 4, 5};
    int sum = Jianqiao::accumulate(a, a + 5, 0);
    cout << sum << endl;
}

void test_adjacent_difference(){
    int a[] = {3, 2, 3, 4, 5};
    int b[5];
    Jianqiao::adjacent_difference(a, a + 5, b);
    for(int i = 0; i < 5; ++i){
        cout << b[i] << " ";
    }
    cout << endl;
}

void test_inner_product(){
    int a[] = {1, 2, 3, 4, 5};
    int b[] = {1, 2, 3, 4, 5};
    int result = Jianqiao::inner_product(a, a + 5, b, 0);
    cout << result << endl;
}

void test_partial_sum(){
    int a[] = {1, 2, 3, 4, 5};
    int b[5];
    cout<<Jianqiao::partial_sum(a, a + 5, b)<<endl;
    for(int i = 0; i < 5; ++i){
        cout << b[i] << " ";
    }
    cout << endl;
}

void test_power(){
    cout<<Jianqiao::power(2, 10)<<endl;
}

int main(){
    test_power();

    return 0;
}