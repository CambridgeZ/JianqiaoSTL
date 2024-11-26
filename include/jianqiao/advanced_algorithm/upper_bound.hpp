//
// Created by Mac on 24-11-26.
//

#ifndef JIANQIAOSTL_UPPER_BOUND_HPP
#define JIANQIAOSTL_UPPER_BOUND_HPP

#include "../config.hpp"
#include "../jianqiao_iterator.hpp"
#include "../jianqiao_algorithm_base.hpp"

__JIANQIAO_BEGIN__
/*
 * upper_bound: 返回一个迭代器，指向在[first, last)中第一个大于·value的元素, 也就是说返回的迭代器可以视为插入value的最后一个位置
 */

template <typename ForwardIterator, typename T, typename Distance>
ForwardIterator __upper_bound(ForwardIterator first, ForwardIterator last, const T& value, Distance*, forward_iterator_tag);

template <typename ForwardIterator, typename T, typename Distance>
ForwardIterator __upper_bound(ForwardIterator first, ForwardIterator last, const T& value, Distance*, std::forward_iterator_tag);

template <typename ForwardIterator, typename T, typename Compare, typename Distance>
ForwardIterator __upper_bound(ForwardIterator first, ForwardIterator last, const T& value, Compare comp, Distance*, forward_iterator_tag);

template <typename ForwardIterator, typename T, typename Compare, typename Distance>
ForwardIterator __upper_bound(ForwardIterator first, ForwardIterator last, const T& value, Compare comp, Distance*, std::forward_iterator_tag);

template <typename ForwardIterator, typename T>
inline ForwardIterator upper_bound(ForwardIterator first, ForwardIterator last, const T& value){
    return __upper_bound(first, last, value, distance_type(first), iterator_category(first));
}

template <typename ForwardIterator, typename T, typename Compare>
inline ForwardIterator upper_bound(ForwardIterator first, ForwardIterator last, const T& value, Compare comp){
    return __upper_bound(first, last, value, comp, distance_type(first), iterator_category(first));
}

template <typename ForwardIterator, typename T, typename Distance>
ForwardIterator __upper_bound_forward(ForwardIterator first, ForwardIterator last, const T& value, Distance*){
    Distance len = 0;
    len = Jianqiao::distance(first, last);
    Distance half;
    ForwardIterator middle;
    while(len > 0){
        half = len >> 1;
        middle = first;
        Jianqiao::advance(middle, half);
        if(value< *middle){
            len = half;
        }else{
            first = middle;
            ++first;
            len = len - half - 1;
        }
    }
    return first;
}

template <typename ForwardIterator, typename T, typename Compare, typename Distance>
ForwardIterator __upper_bound_forward(ForwardIterator first, ForwardIterator last, const T& value, Compare comp, Distance*){
    Distance len = 0;
    len = Jianqiao::distance(first, last);
    Distance half;
    ForwardIterator middle;
    while(len > 0){
        half = len >> 1;
        middle = first;
        Jianqiao::advance(middle, half);
        if(comp(value, *middle)){
            len = half;
        }else{
            first = middle;
            ++first;
            len = len - half - 1;
        }
    }
    return first;
}





template <typename ForwardIterator, typename T, typename Distance>
ForwardIterator __upper_bound(ForwardIterator first, ForwardIterator last, const T& value, Distance*, forward_iterator_tag){
    return __upper_bound_forward(first, last, value, distance_type(first));
}

template <typename ForwardIterator, typename T, typename Distance>
ForwardIterator __upper_bound(ForwardIterator first, ForwardIterator last, const T& value, Distance*, std::forward_iterator_tag){
    return __upper_bound_forward(first, last, value, distance_type(first));
}

template <typename ForwardIterator, typename T, typename Compare, typename Distance>
ForwardIterator __upper_bound(ForwardIterator first, ForwardIterator last, const T& value, Compare comp, Distance*, forward_iterator_tag){
    return __upper_bound_forward(first, last, value, comp,distance_type(first));
}

template <typename ForwardIterator, typename T, typename Compare, typename Distance>
ForwardIterator __upper_bound(ForwardIterator first, ForwardIterator last, const T& value, Compare comp, Distance*, std::forward_iterator_tag){
    return __upper_bound_forward(first, last, value, comp, distance_type(first));
}




__JIANQIAO_END__
#endif //JIANQIAOSTL_UPPER_BOUND_HPP
