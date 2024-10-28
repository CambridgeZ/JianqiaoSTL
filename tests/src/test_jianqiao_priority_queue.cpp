//
// Created by Mac on 24-10-28.
//

#include "../../include/jianqiao/jianqiao_priority_queue.hpp"

void test_jianqiao_priority_queue(){
    Jianqiao::priority_queue<int> pq;
    pq.push(1);
    pq.push(2);
    pq.push(3);
    pq.push(4);
    pq.push(5);
    while(!pq.empty() ){
        std::cout<<pq.top()<<" ";

        pq.pop();
    }
    std::cout<<std::endl;
}

int main(){
    test_jianqiao_priority_queue();
    return 0;
}

