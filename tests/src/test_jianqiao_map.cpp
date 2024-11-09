//
// Created by Mac on 24-11-8.
//

#include "../../include/jianqiao/jianqiao_map.hpp"
#include <iostream>
#include <string>

using std::string;

void test1(){
    Jianqiao::map<int, std::string> m;

//    m[1] = "a";

    m.insert(Jianqiao::make_pair(1, string("a")));
    m.insert(Jianqiao::make_pair(2, string("b")));
    m.insert(Jianqiao::make_pair(3, string("c")));
    m[4] = "d";


    for(auto iter = m.begin(); iter != m.end(); ++iter){
        std::cout << iter->first << " " << iter->second << std::endl;
    }

    auto iter = m.find(2);
    if(iter != m.end()){
        std::cout << "find: " << iter->first << " " << iter->second << std::endl;
    }
    else{
        std::cout << "not found" << std::endl;
    }

}

int main(){
    test1();
    return 0;
}
