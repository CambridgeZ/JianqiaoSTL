//
// Created by Mac on 24-11-9.
//

#include "../../include/jianqiao/jianqiao_hashtable.hpp"
#include <iostream>
#include "../../include/jianqiao/jianqiao_function.hpp"

using Jianqiao::hashtable;
using Jianqiao::identity;
using Jianqiao::equal_to;
using std::cout;
using std::endl;

auto alloc = Jianqiao::simple_alloc<Jianqiao::__hashtable_node<int>, Jianqiao::allocator<Jianqiao::__hashtable_node<int>>>();

//hash
template<class T>
struct hash{
    size_t operator()(const T& x) const{
        return x;
    }
};

void test(){
    hashtable<int ,int , hash<int>, identity<int>, equal_to<int> >  iht(50, hash<int>(), equal_to<int>());

//    cout<<iht.size()<<endl;
//    cout<<iht.bucket_count()<<endl;
//
    iht.insert_unique(59);
    iht.insert_unique(63);
    iht.insert_unique(59);
    cout<<iht.size()<<endl;

    iht.insert_equal(59);

    for(auto iter = iht.begin(); iter != iht.end(); ++iter){
        cout<<*iter<<" ";
    }
    cout<<endl;

    cout<< *iht.find(59)<<endl;
    cout<< iht.count(59)<<endl;

}

int main(){
    test();
    return 0;
}