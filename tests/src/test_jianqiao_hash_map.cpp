//
// Created by Mac on 24-11-11.
//

#include "../../include/jianqiao/jianqiao_hash_map.hpp"
#include <iostream>
#include <cstring>

struct eqstr{
    bool operator()(const char* s1, const char* s2) const {
        return strcmp(s1, s2) == 0;
    }
};

int main(){
    Jianqiao::hash_map<const char*, int, Jianqiao::hash<const char*>, eqstr> days;
    days["january"] = 31;
    days["february"] = 28;
    days["march"] = 31;
    days["april"] = 30;
    days["may"] = 31;
    days["june"] = 30;
    days["july"] = 31;
    days["august"] = 31;
    days["september"] = 30;
    days["october"] = 31;

    std::cout << "june -> " << days["june"] << std::endl;
    std::cout << "february -> " << days["february"] << std::endl;
    std::cout << "september -> " << days["september"] << std::endl;

    auto iter = days.find("september");
    if(iter != days.end()){
        std::cout << "find: " << iter->first << " " << iter->second << std::endl;
    }
    else{
        std::cout << "not found" << std::endl;
    }

    for(auto it = days.begin(); it != days.end(); ++it){
        std::cout << it->first << " " << it->second << std::endl;
    }



    return 0;
}