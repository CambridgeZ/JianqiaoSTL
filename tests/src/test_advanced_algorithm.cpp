//
// Created by Mac on 24-11-26.
//

#include "../../include/jianqiao/jianqiao_algorithm.hpp"

#include <iostream>
#include <vector>

using std:: cout;
using std:: endl;
using std:: cin;
using std:: vector;

void test_lower_bound(){
    cout << "test1" << endl;
    vector<int> vec = {1, 2, 3, 4, 5};
    cout << "lower_bound: " << *Jianqiao::lower_bound(vec.begin(), vec.end(), 3) << endl;
    //comp版本测试
    cout << "lower_bound: " << *Jianqiao::lower_bound(vec.begin(), vec.end(), 3, Jianqiao::less<int>()) << endl;
//    cout << "upper_bound: " << *Jianqiao::upper_bound(vec.begin(), vec.end(), 3) << endl;
//    cout << "equal_range: " << *Jianqiao::equal_range(vec.begin(), vec.end(), 3).first << " " << *Jianqiao::equal_range(vec.begin(), vec.end(), 3).second << endl;
}

void test_upperbound(){
    cout << "test2" << endl;
    vector<int> vec = {1, 2, 3, 4, 5};
    cout << "upper_bound: " << *Jianqiao::upper_bound(vec.begin(), vec.end(), 3) << endl;
    //comp版本测试
    cout << "upper_bound: " << *Jianqiao::upper_bound(vec.begin(), vec.end(), 3, Jianqiao::less<int>()) << endl;

    auto second = Jianqiao::upper_bound(vec.begin(), vec.end(), 3, Jianqiao::less<int>());
    cout << "second: " << *second << endl;
    if(second == vec.end()){
        cout << "second is end" << endl;
    }
    cout<<second-vec.begin()<<endl;
}

int main(){
    test_upperbound();
    return 0;
}
