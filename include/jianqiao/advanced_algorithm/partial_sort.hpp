//
// Created by Mac on 24-12-8.
//

#ifndef JIANQIAOSTL_PARTIAL_SORT_HPP
#define JIANQIAOSTL_PARTIAL_SORT_HPP

#include "../config.hpp"
#include "../heap_base.hpp"
#include "../jianqiao_iterator_base.hpp"

__JIANQIAO_BEGIN__

template <typename RandomAccessIterator, typename T>
void __partial_sort(RandomAccessIterator first, RandomAccessIterator middle, RandomAccessIterator last, T*) {
    Jianqiao::make_heap(first, middle);
    for (RandomAccessIterator i = middle; i < last; ++i) {
        if (*i < *first) {
            Jianqiao::__pop_heap(first, middle, i, T(*i), distance_type(first));
        }
    }
    Jianqiao::sort_heap(first, middle);
}

template <typename RandomAccessIterator>
inline void partial_sort(RandomAccessIterator first, RandomAccessIterator middle, RandomAccessIterator last) {
    __partial_sort(first, middle, last, value_type(first));
}

template <typename RandomAccessIterator, typename T, typename Compare>
void __partial_sort(RandomAccessIterator first, RandomAccessIterator middle, RandomAccessIterator last, T*, Compare comp) {
    Jianqiao::make_heap(first, middle, comp);
    for (RandomAccessIterator i = middle; i < last; ++i) {
        if (comp(*i, *first)) {
            Jianqiao::__pop_heap(first, middle, i, T(*i), comp, distance_type(first));
        }
    }
    Jianqiao::sort_heap(first, middle, comp);
}

template <typename RandomAccessIterator, typename Compare>
inline void partial_sort(RandomAccessIterator first, RandomAccessIterator middle, RandomAccessIterator last, Compare comp) {
    __partial_sort(first, middle, last, value_type(first), comp);
}

__JIANQIAO_END__
#endif //JIANQIAOSTL_PARTIAL_SORT_HPP
