//
// Created by Mac on 24-11-8.
//

#include "../../include/jianqiao/jianqiao_set.hpp"
#include <iostream>

using std::cout;
using std::cin;
using std::endl;

void test1(){
    Jianqiao::set<int> s;
    cout << s.size() << endl;

    s.insert(10);
    s.insert(7);

    cout << s.size() << endl;

    s.insert(8);
    s.insert(15);

    auto iter1 = s.begin();
    auto iter2 = s.end();

    if(iter1.node == nullptr){
        cout << "empty" << endl;
        return;
    }

    for(; iter1 != iter2; ++iter1){
        cout << *iter1 << " ";
    }

    // erase
//    auto iter3 = s.find(8);
//    s.erase(iter3);
//    auto itbegin = s.begin();
//    auto itend = s.end();
//    s.erase(itbegin, itend);
    cout << endl;

    Jianqiao::set<int> s2;
    s2 = s;
    for(auto it = s2.begin(); it != s2.end(); ++it){
        cout << *it << " ";
    }
    cout << endl;


}

void test2(){
    // 测试构造函数
    Jianqiao::set<int> s;
    cout << s.size() << endl;

    s.insert(10);
    s.insert(7);

    //find
    auto iter = s.find(10);
    cout << *iter << endl;
}

int main(){
    test1();
    cout << endl;
    cout << "____________________________________" << endl;
    test2();
    return 0;
}

