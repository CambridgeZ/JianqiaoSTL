//
// Created by Mac on 24-11-12.
//

#ifndef JIANQIAOSTL_IOTA_HPP
#define JIANQIAOSTL_IOTA_HPP

#include "../config.hpp"

__JIANQIAO_BEGIN__
/*
 * 从first开始，逐个赋值，直到last结束, 赋值的值从value开始，每次递增
 */

template <typename ForwardIterator, typename T>
void iota(ForwardIterator first, ForwardIterator last, T value){
    while(first != last){
        *first++ = value++;
    }
}

__JIANQIAO_END__
#endif //JIANQIAOSTL_IOTA_HPP
