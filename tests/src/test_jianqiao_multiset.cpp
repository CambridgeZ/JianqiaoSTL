//
// Created by Mac on 24-11-9.
//

#include "../../include/jianqiao/jianqiao_multiset.hpp"
#include <iostream>
#include "../../include/jianqiao/jianqiao_pair.hpp"

using std::cout;
using std::endl;

void test(){
    Jianqiao::multiset<int> s;
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
}

int main(){
    test();
    return 0;
}
