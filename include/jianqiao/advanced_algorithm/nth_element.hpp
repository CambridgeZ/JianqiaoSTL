//
// Created by Mac on 24-12-9.
//

#ifndef JIANQIAOSTL_NTH_ELEMENT_HPP
#define JIANQIAOSTL_NTH_ELEMENT_HPP

#include "../jianqiao_algorithm_base.hpp"
#include "../config.hpp"
#include "sort.hpp"
#include "./sort/insertion_sort.hpp"

__JIANQIAO_BEGIN__

template <typename RandomAccessIterator, typename T>
void __nth_element(RandomAccessIterator first, RandomAccessIterator nth, RandomAccessIterator last, T*);

template <typename RandomAccesssIterator>
inline void nth_element(RandomAccesssIterator first, RandomAccesssIterator nth, RandomAccesssIterator last) {
    __nth_element(first, nth, last, value_type(first));
}

template <typename RandomAccessIterator, typename T>
void __nth_element(RandomAccessIterator first, RandomAccessIterator nth, RandomAccessIterator last, T*){
    while (last - first > 3) {
        RandomAccessIterator cut = __unguarded_partition(first, last, T(__median(*first, *(first + (last - first) / 2), *(last - 1))));
        if (cut <= nth) {
            // 如果nth在cut的右边，那么只需要对cut到last进行排序
            first = cut;
        } else {
            // 如果nth在cut的左边，那么只需要对first到cut进行排序
            last = cut;
        }
    }

    // 如果大小小于3，就直接做插入排序了
    __insertion_sort(first, last);
}


__JIANQIAO_END__

#endif //JIANQIAOSTL_NTH_ELEMENT_HPP
