//
// Created by Mac on 24-12-8.
//

#ifndef JIANQIAOSTL_INSERTION_SORT_HPP
#define JIANQIAOSTL_INSERTION_SORT_HPP

#include "../../config.hpp"
#include "../../jianqiao_iterator_base.hpp"
#include "../../jianqiao_algorithm_base.hpp"

__JIANQIAO_BEGIN__

template <typename RandomAccessIterator, typename T>
void __unguarded_linear_insert(RandomAccessIterator last, T value){

    // 从后往前遍历，找到合适的位置插入
    RandomAccessIterator next = last;
    --next;
    while(value < *next){
        *last = *next;
        last = next;
        --next;
    }
    *last = value;
}


template <typename RandomAccessIterator, typename T>
inline void __linear_insert(RandomAccessIterator first, RandomAccessIterator last, T*){
    T value = *last;
    if(value < *first){
        // 如果应该插入到最前面

        // 所有的元素整体后移
        Jianqiao::copy_backward(first, last, last + 1);

        // 元素插入到最前面
        *first = value;
    }else{
        // 插入前面的元素当中
        __unguarded_linear_insert(last, value);
    }
}

template <typename RandomAccessIterator>
void __insertion_sort(RandomAccessIterator first, RandomAccessIterator last){
    if(first == last){
        return ;
    }

    for(RandomAccessIterator i = first + 1; i != last; ++i){
        __linear_insert(first, i, value_type(first));
    }
}


__JIANQIAO_END__

#endif //JIANQIAOSTL_INSERTION_SORT_HPP
