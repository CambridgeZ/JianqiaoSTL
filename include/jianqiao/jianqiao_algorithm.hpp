//
// Created by Mac on 24-11-26.
//

#ifndef JIANQIAOSTL_JIANQIAO_ALGORITHM_HPP
#define JIANQIAOSTL_JIANQIAO_ALGORITHM_HPP

#include "config.hpp"
#include "jianqiao_iterator.hpp"
#include "jianqiao_algorithm_base.hpp"
/*
 * 在本文件当中实现工作原理较为复杂的一些算法
 */

__JIANQIAO_BEGIN__

/*
 * lower_bound: 返回一个迭代器，指向键值大于等于k的第一个元素,也就是区间当中第一个不小于k的元素
 * 从插入的观点来看，返回的这个迭代器可以视为插入k的位置
 */
    template <typename ForwardIterator, typename T, typename Distance>
    ForwardIterator __lower_bound(ForwardIterator first, ForwardIterator last, const T& value, Distance*, forward_iterator_tag);

    template <typename ForwardIterator, typename T, typename Compare, typename Distance>
    ForwardIterator __lower_bound(ForwardIterator first, ForwardIterator last, const T& value, Compare comp, Distance*, forward_iterator_tag);

    template <typename ForwardIterator, typename T, typename Distance>
    ForwardIterator __lower_bound(ForwardIterator first, ForwardIterator last, const T& value, Distance*, std::forward_iterator_tag);

    template <typename ForwardIterator, typename T, typename Compare, typename Distance>
    ForwardIterator __lower_bound(ForwardIterator first, ForwardIterator last, const T& value, Compare comp, Distance*, std::forward_iterator_tag);

template <typename ForwardIterator, typename T>
inline ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last, const T& value){
    return __lower_bound(first, last, value, distance_type(first), iterator_category(first));
}

template <typename ForwardIterator, typename T, typename Compare>
inline ForwardIterator lower_bound(ForwardIterator first, ForwardIterator last, const T& value, Compare comp){
    return __lower_bound(first, last, value, comp, distance_type(first), iterator_category(first));
}

    template <typename ForwardIterator, typename T, typename Distance>
    ForwardIterator __lower_bound_forward(ForwardIterator first, ForwardIterator last, const T& value, Distance*);

template <typename ForwardIterator, typename T, typename Distance>
ForwardIterator __lower_bound(ForwardIterator first, ForwardIterator last, const T& value, Distance*, forward_iterator_tag){
    return __lower_bound_forward(first, last, value, distance_type(first));
}

template <typename ForwardIterator, typename T, typename Distance>
ForwardIterator __lower_bound(ForwardIterator first, ForwardIterator last, const T& value, Distance*, std::forward_iterator_tag){
    return __lower_bound_forward(first, last, value, distance_type(first));
}

template <typename ForwardIterator, typename T, typename Distance>
ForwardIterator __lower_bound_forward(ForwardIterator first, ForwardIterator last, const T& value, Distance*){
    Distance len = 0;
    len = Jianqiao::distance(first, last);
    Distance half;
    ForwardIterator middle;
    while(len > 0){
        half = len >> 1;
        middle = first;
        Jianqiao::advance(middle, half);
        if(*middle < value){
            first = middle;
            ++first;
            len = len - half - 1;
        }else{
            len = half;
        }
    }
    return first;
}

    template <typename ForwardIterator, typename T, typename Compare, typename Distance>
    ForwardIterator __lower_bound_forward(ForwardIterator first, ForwardIterator last, const T& value, Compare comp, Distance*);


template <typename ForwardIterator, typename T, typename Compare, typename Distance>
ForwardIterator __lower_bound(ForwardIterator first, ForwardIterator last, const T& value, Compare comp, Distance*, forward_iterator_tag){
    return __lower_bound_forward(first, last, value, comp, distance_type(first));
}

template <typename ForwardIterator, typename T, typename Compare, typename Distance>
ForwardIterator __lower_bound(ForwardIterator first, ForwardIterator last, const T& value, Compare comp, Distance*, std::forward_iterator_tag){
    return __lower_bound_forward(first, last, value, comp, distance_type(first));
}

template <typename ForwardIterator, typename T, typename Compare, typename Distance>
ForwardIterator __lower_bound_forward(ForwardIterator first, ForwardIterator last, const T& value, Compare comp, Distance*){
    Distance len = 0;
    len = Jianqiao::distance(first, last);
    Distance half;
    ForwardIterator middle;
    while(len > 0){
        half = len >> 1;
        middle = first;
        Jianqiao::advance(middle, half);
        if(comp(*middle, value)){
            first = middle;
            ++first;
            len = len - half - 1;
        }else{
            len = half;
        }
    }
    return first;
}


__JIANQIAO_END__
#endif //JIANQIAOSTL_JIANQIAO_ALGORITHM_HPP
