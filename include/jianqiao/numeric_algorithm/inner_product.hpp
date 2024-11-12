//
// Created by Mac on 24-11-12.
//

#ifndef JIANQIAOSTL_INNER_PRODUCT_HPP
#define JIANQIAOSTL_INNER_PRODUCT_HPP

#include "../config.hpp"

__JIANQIAO_BEGIN__

template <typename InputIterator1, typename InputIterator2, typename T>
T inner_product(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, T init){
    for(; first1 != last1; ++first1, ++first2){
        init = init + (*first1) * (*first2);
    }
    return init;
}

template <typename InputIterator1, typename InputIterator2, typename T, typename BinaryOperation1, typename BinaryOperation2>
T inner_product(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, T init, BinaryOperation1 binary_op1, BinaryOperation2 binary_op2){
    /*
     * 两个binary_op分别是两个函数对象，分别执行了积和和的操作
     */
    for(; first1 != last1; ++first1, ++first2){
        init = binary_op1(init, binary_op2(*first1, *first2));
    }
    return init;
}

__JIANQIAO_END__
#endif //JIANQIAOSTL_INNER_PRODUCT_HPP
