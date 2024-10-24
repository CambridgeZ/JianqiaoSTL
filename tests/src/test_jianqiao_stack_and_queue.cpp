#include "../../include/jianqiao/jianqiao_stack.hpp"
#include "../../include/jianqiao/jianqiao_queue.hpp"

#include <iostream>
#include <deque>

using namespace Jianqiao;

void test_stack(){
    stack<int> ST;
    ST.push(1);
    ST.push(2);
    ST.push(3);
    ST.push(4);
    ST.push(5);

    while(!ST.empty()){
        std::cout << ST.top() << std::endl;
        ST.pop();
    }
}

void test_queue(){
    queue<int> Q;
    Q.push(1);
    Q.push(2);
    Q.push(3);
    Q.push(4);
    Q.push(5);

    while(!Q.empty()){
        std::cout << Q.front() << std::endl;
        Q.pop();
    }
}

int main(){
    test_stack();
    test_queue();
    return 0;
}