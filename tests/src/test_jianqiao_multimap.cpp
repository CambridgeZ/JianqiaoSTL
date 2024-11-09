//
// Created by Mac on 24-11-9.
//

#include "../../include/jianqiao/jianqiao_multimap.hpp"

#include <iostream>

using std::cout;
using std::endl;

void test(){

    Jianqiao::multimap<int, int> m;
    m.insert(Jianqiao::make_pair(1, 1));
    m.insert(Jianqiao::make_pair(2, 2));
    m.insert(Jianqiao::make_pair(1, 2));

    cout << "size: " << m.size() << endl;

    for(auto it = m.begin(); it != m.end(); ++it){
        cout << it->first << " " << it->second << endl;
    }
    cout<<endl;

    m.erase(1);

    for(auto it = m.begin(); it != m.end(); ++it){
        cout << it->first << " " << it->second << endl;
    }
    cout << endl;

    Jianqiao::multimap<int, int> m2;
    m2 = m;

    for(auto it = m2.begin(); it != m2.end(); ++it){
        cout << it->first << " " << it->second << endl;
    }

    cout << endl;

    if(m2 == m){
        cout << "m2 == m" << endl;
    }else{
        cout << "m2 != m" << endl;
    }

}

int main(){
    test();
    return 0;
}