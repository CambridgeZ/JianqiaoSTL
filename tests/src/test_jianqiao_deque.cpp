#include "../../include/jianqiao/jianqiao_deque.hpp"

#include <iostream>

using std::cout;
using std::endl;

void test1(){
    Jianqiao::deque<int> ideq;
    for(int i = 0; i < 10; ++i){
        ideq.push_back(i);
    }

    for(int i = 0; i < ideq.size(); ++i){
        cout<<ideq[i]<<" ";
    }
    cout<<endl;

    ideq.insert(ideq.begin() + 3, 10);
    ideq.push_front(100);
    for(int i = 0; i < ideq.size(); ++i){
        cout<<ideq[i]<<" ";
    }
    cout<<endl;

    ideq.erase(ideq.begin() + 3);
    for(int i = 0; i < ideq.size(); ++i){
        cout<<ideq[i]<<" ";
    }
    cout<<endl;

    ideq.clear();
    for(int i = 0; i < ideq.size(); ++i){
        cout<<ideq[i]<<" ";
    }
    cout<<endl;
}

int main(){
    test1();
    cout<<endl;
    return 0;
}