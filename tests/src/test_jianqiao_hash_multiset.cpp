//
// Created by Mac on 24-11-11.
//

#include "../../include/jianqiao/jianqiao_hash_multiset.hpp"
#include <iostream>

using std::cout;
using std::endl;


void test(){
    Jianqiao::hash_multiset<int> s;
    s.insert(1);
    s.insert(1);
    s.insert(2);
    s.insert(3);
    s.insert(4);

    cout << "size: " << s.size() << endl;

    for(auto it = s.begin(); it != s.end(); ++it){
        cout << *it << " ";
    }

    s.erase(1);
    cout << endl;
    for(auto it = s.begin(); it != s.end(); ++it){
        cout << *it << " ";
    }
    cout << endl;
    cout << s.size() << endl;
}

int main(){
    test();
    return 0;
}

