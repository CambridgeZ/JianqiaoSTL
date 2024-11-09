//
// Created by Mac on 24-11-8.
//

#ifndef JIANQIAOSTL_JIANQIAO_PAIR_HPP
#define JIANQIAOSTL_JIANQIAO_PAIR_HPP

#include "config.hpp"
__JIANQIAO_BEGIN__

template <typename T1, typename T2>
struct pair{
    using first_type = T1;
    using second_type = T2;

    T1 first;
    T2 second;

    pair(): first(T1()), second(T2()){}
    pair(const T1& a, const T2& b): first(a), second(b){}
};

template <typename T1, typename T2>
pair<T1, T2> make_pair(const T1& a, const T2& b){
    return pair<T1, T2>(a, b);
}

__JIANQIAO_END__
#endif //JIANQIAOSTL_JIANQIAO_PAIR_HPP
