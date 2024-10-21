#include "../../include/jianqiao/jianqiao_vector.hpp"

#include <iostream>

using std::cout;
using std::endl;

void test1(){
    Jianqiao::vector<int> iv;
    for(int i = 0; i < 10; ++i){
        iv.push_back(i);
    }

    for(int i = 0; i < iv.size(); ++i){
        cout<<iv[i]<<" ";
    }
    cout<<endl;

    iv.insert(iv.begin() + 3, 10, 100);
    for(int i = 0; i < iv.size(); ++i){
        cout<<iv[i]<<" ";
    }
    cout<<endl;

    iv.erase(iv.begin() + 3);
    for(int i = 0; i < iv.size(); ++i){
        cout<<iv[i]<<" ";
    }
    cout<<endl;

    iv.resize(20, 200);
    for(int i = 0; i < iv.size(); ++i){
        cout<<iv[i]<<" ";
    }
    cout<<endl;

    iv.resize(5);
    for(int i = 0; i < iv.size(); ++i){
        cout<<iv[i]<<" ";
    }
    cout<<endl;

    iv.clear();
    for(int i = 0; i < iv.size(); ++i){
        cout<<iv[i]<<" ";
    }
    cout<<endl;
}

int main(){
    test1();
    cout<<endl;
    cout<<"____________________________________"<<endl;
    return 0;
}
