#include "../../include/jianqiao/alloc.hpp"
#include <vector>
#include <iostream>

using namespace std;

int main(){
    int ia[5] = {0,1,2,3,4};
    vector<int,Jianqiao::allocator<int> > iv(ia,ia+5);

    for(int i=0;i<iv.size();i++){
        cout<<iv[i]<<" ";
    }
    cout<<endl;

    return 0;
}

