//
// Created by Mac on 24-11-10.
//

#include "../../include/jianqiao/jianqiao_hash_set.hpp"
#include <iostream>
#include "../../include/jianqiao/jianqiao_hash_fun.hpp"
#include "../../include/jianqiao/jianqiao_function.hpp"

using std::cout;
using std::endl;

using Jianqiao::hash_set;
using Jianqiao::hash;
using Jianqiao::equal_to;

void test1() {
    hash_set<int, hash<int>,equal_to<int> > hs;
    cout << hs.size() << endl;

    hs.insert(10);
    hs.insert(7);

    cout << hs.size() << endl;

    hs.insert(8);
    hs.insert(15);

    auto iter1 = hs.begin();
    auto iter2 = hs.end();

    if (iter1.cur == nullptr) {
        cout << "empty" << endl;
        return;
    }

    for (; iter1 != iter2; ++iter1) {
        cout << *iter1 << " ";
    }
}

int main(){
    test1();
    cout << endl;
    cout << "____________________________________" << endl;
    return 0;
}
