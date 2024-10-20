// 对于jianqiao_iterator_base.hpp的测试
#include "../../include/jianqiao/jianqiao_iterator_base.hpp"

#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <algorithm>

using std::cout;
using std::endl;
using std::vector;
using std::list;


int main(){
    int ia[5] = {0,1,2,3,4};
    vector<int> iv(ia,ia+5);

    cout<<Jianqiao::distance(iv.begin(),iv.end())<<endl;

    list<int> il(ia,ia+5);
    cout<<Jianqiao::distance(il.begin(),il.end())<<endl;

    vector<int>::iterator ivit = iv.begin();
    Jianqiao::advance(ivit,3);
    cout<<*ivit<<endl;

    list<int>::iterator ilit = il.begin();
    Jianqiao::advance(ilit,3);
    cout<<*ilit<<endl;

    return 0;
}


