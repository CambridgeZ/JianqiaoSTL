//
// Created by Mac on 24-11-12.
//

#ifndef JIANQIAOSTL_ADJACENT_DIFFERENCE_HPP
#define JIANQIAOSTL_ADJACENT_DIFFERENCE_HPP

#include "../config.hpp"

__JIANQIAO_BEGIN__
/*
 * adjacent_difference: 计算相邻元素的差值
 */

template <typename InputIterator, typename OutputIterator>
OutputIterator adjacent_difference(InputIterator first, InputIterator last, OutputIterator result){
    if(first == last)
        return result;
    *result = *first;
    auto value = *first;
    while(++first != last){
        auto tmp = *first;
        *++result = tmp - value;
        value = tmp;
    }
    return ++result;
}

template <typename InputIterator, typename OutputIterator, typename BinaryOperation>
OutputIterator adjacent_difference(InputIterator first, InputIterator last, OutputIterator result, BinaryOperation binary_op){
    if(first == last)
        return result;
    *result = *first;
    auto value = *first;
    while(++first != last){
        auto tmp = *first;
        *++result = binary_op(tmp, value);
        value = tmp;
    }
    return ++result;
}

__JIANQIAO_END__
#endif //JIANQIAOSTL_ADJACENT_DIFFERENCE_HPP
