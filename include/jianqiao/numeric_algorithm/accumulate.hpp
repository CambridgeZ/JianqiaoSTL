//
// Created by Mac on 24-11-12.
//

#ifndef JIANQIAOSTL_ACCUMULATE_HPP
#define JIANQIAOSTL_ACCUMULATE_HPP

#include "../config.hpp"

__JIANQIAO_BEGIN__

template <typename InputIterator, typename T>
T accumulate(InputIterator first, InputIterator last, T init){
    for(; first != last; ++first){
        init += *first;
    }
    return init;
}

template <typename InputIterator, typename T, typename BinaryOperation>
T accumulate(InputIterator first, InputIterator last, T init, BinaryOperation binary_op){
    /*
     * 其中BinaryOperation是一个函数对象，它的参数是两个，返回值是一个。
     * 在这里的accumulate函数中，binary_op是一个函数对象，它的作用是对两个参数进行运算，返回值是运算结果，相当于是在这里执行加法操作
     */
    for(; first != last; ++first){
        init = binary_op(init, *first);
    }
    return init;
}



__JIANQIAO_END__

#endif //JIANQIAOSTL_ACCUMULATE_HPP
