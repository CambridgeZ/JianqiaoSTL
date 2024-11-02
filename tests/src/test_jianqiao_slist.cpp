//
// Created by Mac on 24-11-2.
//

#include "../../include/jianqiao/jianqiao_slist.hpp"

using Jianqiao::slist;

void test1(){
    slist<int> single_list;
    single_list.push_front(1);
    single_list.push_front(2);
    single_list.push_front(3);
    single_list.push_front(4);


    slist<int>::iterator it = single_list.begin();
    for(; it != single_list.end(); ++it){
        std::cout<<*it<<" ";
    }
    std::cout<<std::endl;
}

void test2(){
    slist<int> single_list;
    single_list.push_front(1);
    single_list.push_front(2);
    single_list.push_front(3);
    single_list.push_front(4);

    single_list.pop_front();
    single_list.pop_front();
    single_list.pop_front();
    single_list.pop_front();

    slist<int>::iterator it = single_list.begin();
    for(; it != single_list.end(); ++it){
        std::cout<<*it<<" ";
    }
    std::cout<<std::endl;
}

int main(){
    test1();
    test2();
    return 0;
}
