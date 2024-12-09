//
// Created by Mac on 24-12-9.
//

#ifndef JIANQIAOSTL_INPLACE_MERGE_HPP
#define JIANQIAOSTL_INPLACE_MERGE_HPP

#include "../config.hpp"
#include "../jianqiao_iterator_base.hpp"
#include "../jianqiao_algorithm_base.hpp"

__JIANQIAO_BEGIN__

template <typename BidirectionalIterator, typename Distance, typename T>
inline void __inplace_merge_aux(BidirectionalIterator first, BidirectionalIterator middle, BidirectionalIterator last, Distance*, T*){
    Distance len1 = 0;
    distance(first, middle, len1);
    Distance len2 = 0;
    distance(middle, last, len2);

    T* buffer = new T[len1];
    // 前面一个拷贝下来
    uninitialized_copy(first, middle, buffer);

    BidirectionalIterator first1 = buffer;
    BidirectionalIterator last1 = buffer + len1;
    BidirectionalIterator first2 = middle;
    BidirectionalIterator last2 = last;

    BidirectionalIterator result = first;
    while(first1 != last1 && first2 != last2){
        if(*first2 < *first1){
            *result = *first2;
            ++first2;
        }else{
            *result = *first1;
            ++first1;
        }
        ++result;
    }

    if(first1 != last1){
        result = copy(first1, last1, result);
    }

    delete[] buffer;
}

template <typename BidirectionalIterator>
inline void inplace_merge(
        BidirectionalIterator first, BidirectionalIterator middle, BidirectionalIterator last
        ){
    if(first == middle || middle == last) return;
    __inplace_merge_aux(first, middle, last, distance_type(first), value_type(first));
}


__JIANQIAO_END__
#endif //JIANQIAOSTL_INPLACE_MERGE_HPP
