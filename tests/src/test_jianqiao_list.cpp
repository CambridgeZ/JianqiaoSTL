#include "../../include/jianqiao/jianqiao_list.hpp"

#include <iostream>

using std::cout;
using std::endl;

void test1(){
    Jianqiao::list<int> il;
    cout<<endl;

    il.push_back(1);
    il.push_back(2);
    il.push_back(3);

    cout<<*il.begin()<<endl;
    cout<<*(--il.end())<<endl;
    cout<<il.empty()<<endl;
}

void test2(){
    Jianqiao::list<int> il;
    cout<<endl;

    il.push_back(1);
    il.push_back(2);
    il.push_back(3);
    il.push_back(-1);

    il.sort();

    for(auto it = il.begin(); it != il.end(); ++it){
        cout<<*it<<" ";
    }
    cout<<endl;

    cout<<*il.begin()<<endl;
    cout<<*(--il.end())<<endl;
    cout<<il.empty()<<endl;

    il.pop_back();
    cout<<*il.begin()<<endl;
    cout<<*(--il.end())<<endl;
    cout<<il.empty()<<endl;

    // insert
    il.insert(il.begin(), 0);
    for(auto it = il.begin(); it != il.end(); ++it){
        cout<<*it<<" ";
    }
    cout<<endl;
}

int main(){
    test1();
    cout<<"____________________________________"<<endl;
    test2();
    return 0;
}