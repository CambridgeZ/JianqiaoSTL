//
// Created by Mac on 24-11-26.
//

#ifndef JIANQIAOSTL_NEXT_PERMUTATION_HPP
#define JIANQIAOSTL_NEXT_PERMUTATION_HPP

#include "../config.hpp"
#include "../jianqiao_algorithm_base.hpp"
#include "../jianqiao_iterator.hpp"

__JIANQIAO_BEGIN__

/*
 * next_permutation: 生成[first, last)的下一个排列
 */

template <class BidirectionalIterator>
bool next_permutation(BidirectionalIterator first, BidirectionalIterator last){
    if(first == last){
        return false;
    }
    BidirectionalIterator i = first;
    ++i;
    if(i == last){
        // 只有一个元素
        return false;
    }
    i = last; // i 指向尾端
    --i;        // i 指向最后一个元素

    for(;;){
        BidirectionalIterator ii = i;
        --i;
        if(*i < *ii){
            BidirectionalIterator j = last;
            while(!(*i < *--j));    // 从后向前找到第一个大于*i的元素
            Jianqiao::iter_swap(i, j);  // 交换
            Jianqiao::reverse(ii, last); // 将ii之后的元素逆序
            return true;
        }
        if(i == first){
            // 找不到这样的，说明已经是最后一个了
            Jianqiao::reverse(first, last);
            return false;
        }
    }
}

template <class BidirectionalIterator, class Compare>
bool next_permutation(BidirectionalIterator first, BidirectionalIterator last, Compare comp){
    if(first == last){
        return false;
    }
    BidirectionalIterator i = first;
    BidirectionalIterator ii = i;
    ++i;
    if(i == last){
        // 只有一个元素
        return false;
    }
    i = last; // i 指向尾端
    --i;        // i 指向最后一个元素

    for(;;){
        ii = i;
        --i;
        if(comp(*i, *ii)){
            BidirectionalIterator j = last;
            while(!comp(*i, *--j));    // 从后向前找到第一个大于*i的元素
            Jianqiao::iter_swap(i, j);  // 交换
            Jianqiao::reverse(ii, last); // 将ii之后的元素逆序
            return true;
        }
        if(i == first){
            // 找不到这样的，说明已经是最后一个了
            Jianqiao::reverse(first, last);
            return false;
        }
    }
}

__JIANQIAO_END__
#endif //JIANQIAOSTL_NEXT_PERMUTATION_HPP
