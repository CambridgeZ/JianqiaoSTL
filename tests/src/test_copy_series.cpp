//
// Created by Mac on 24-11-17.
//

// 测试copy函数

#include <iostream>
#include <vector>
#include "../../include/jianqiao/jianqiao_list.hpp"
#include <string>
#include "../../include/jianqiao/jianqiao_vector.hpp"
#include "../../include/jianqiao/jianqiao_algorithm.hpp"


using Jianqiao::copy;
//using Jianqiao::vector;
using std::vector;
//using Jianqiao::list;
using std::string;
using std::cout;
using std::endl;

void test1(){
    cout << "test1" << endl;
    vector<int> vec1 = {1, 2, 3, 4, 5};
    vector<int> vec2(5);
    Jianqiao::copy(vec1.begin(), vec1.end(), vec2.begin());
    for(auto i : vec2){
        cout << i << " ";
    }
    cout << endl;
}

void test2(){
    cout << "test2" << endl;
    list<int> lst1 = {1, 2, 3, 4, 5};
    vector<int> vec1(5);
    Jianqiao::copy(lst1.begin(), lst1.end(), vec1.begin());
    for(auto i : vec1){
        cout << i << " ";
    }
    cout << endl;
}

void test3(){
    cout<< "test3" <<endl;
    char a[10] = "hello";
    char b[10];
    memset(b, 0, sizeof(b));
    Jianqiao::copy(a, a+5, b);

//    for(auto i : b){
//        cout << i << " ";
//    }

    char *p = b;
    while(*p != '\0'){
        cout<< p-b<< " ";
        cout << *p;
        cout<<endl;
        p++;
    }
    cout << endl;

}

void test4(){
    cout << "test4" << endl;
    string s1 = "hello";
    string s2(5, ' ');
    Jianqiao::copy(s1.begin(), s1.end(), s2.begin());
//    cout<<s2.size()<<endl;
    cout << s2 << endl;
}

#include <vector>

#include <list>


void test5(){
    cout << "test5" << endl;
    std::vector<int> vec1 = {1, 2, 3, 4, 5};
    std::vector<int> vec2(5);
    Jianqiao::copy(vec1.begin(), vec1.end(), vec2.begin());
    for(auto i : vec2){
        cout << i << " ";
    }
    cout << endl;
}

using std::list;
void test6(){
    cout << "test6" << endl;
    list<int> lst1 = {1, 2, 3, 4, 5};
    vector<int> vec1(5);
    Jianqiao::copy(lst1.begin(), lst1.end(), vec1.begin());
    for(auto i : vec1){
        cout << i << " ";
    }
    cout << endl;
}



int main(){
//    test1();
//    test2();
//    test3();
//    test4();
    test5();
    return 0;

}
