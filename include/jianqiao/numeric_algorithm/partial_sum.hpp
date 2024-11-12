//
// Created by Mac on 24-11-12.
//

#ifndef JIANQIAOSTL_PARTIAL_SUM_HPP
#define JIANQIAOSTL_PARTIAL_SUM_HPP

#include "../config.hpp"
__JIANQIAO_BEGIN__

template <typename InputIterator, typename OutputIterator>
OutputIterator partial_sum(InputIterator first, InputIterator last, OutputIterator result){
    if(first == last) return result;
    *result = *first;
    auto value = *first;
    while(++first != last){
        value += *first;
        *++result = value;
    }
    return ++result;
}

template <typename InputIterator, typename OutputIterator, typename BinaryOperation>
OutputIterator partial_sum(InputIterator first, InputIterator last, OutputIterator result, BinaryOperation binary_op){
    if(first == last) return result;
    *result = *first;
    auto value = *first;
    while(++first != last){
        value = binary_op(value, *first);
        *++result = value;
    }
    return ++result;
}

__JIANQIAO_END__
#endif //JIANQIAOSTL_PARTIAL_SUM_HPP
