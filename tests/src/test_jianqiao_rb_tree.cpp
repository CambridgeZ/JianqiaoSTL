//
// Created by Mac on 24-11-7.
//

# include "../../include/jianqiao/jianqiao_rb_tree.hpp"
# include <iostream>
# include <cassert>
# include <vector>
# include <algorithm>
# include <random>

using Jianqiao::rb_tree;
using std::cout;
using std::endl;
using std::vector;

template<typename T>
struct identity{
    const T& operator()(const T& x) const{
        return x;
    }
};

void test1(){
    // 测试插入
    rb_tree< int, int, identity<int>, std::less<int> > rb;
    cout<<rb.size()<<endl;

    rb.insert_unique(10);
    rb.insert_unique(7);

    cout<<rb.size()<<endl;

    rb.insert_unique(8);
    rb.insert_unique(15);

    auto iter1 = rb.begin();
    auto iter2 = rb.end();


    if(iter1.node == nullptr){
        cout<<"empty"<<endl;
        return ;
    }

    for(; iter1 != iter2; ++iter1){
        cout<<*iter1<<" ";
    }

    cout<<"finish"<<endl;
}

void InOrder(rb_tree<int, int, identity<int>, std::less<int>>::base_ptr x) {
    if (x == nullptr) {
        return;
    }
    InOrder(x->left);
    // 强制类型转换
    auto *y = (rb_tree<int, int, identity<int>, std::less<int>>::link_type) x;
    cout << y->value_field << " ";
    InOrder(x->right);
}

//void test2(){
//    // 插入之后中序遍历rb_tree
//
//    rb_tree<int, int, identity<int>, std::less<int>> rb;
//    vector<int> v;
//    for(int i = 0; i < 3; ++i){
//        v.push_back(i);
//    }
//
//    for(auto &i : v){
//        cout<<i<<" "<<"inserted"<<endl;
//        rb.insert_unique(i);
//    }
//
//    cout<<dynamic_cast<rb_tree<int, int, std::identity, std::less<int>>::link_type>(rb.root())->value_field<<endl;
//
//    InOrder(rb.root());
//
//}

void test3(){
    // 插入测试3
    rb_tree<int, int, identity<int>, std::less<int>> rb;
    vector<int> v;

}

int main(){
    test1();
//    test2();
    return 0;
}
