//
// Created by Mac on 24-12-8.
//

#ifndef JIANQIAOSTL_QUICK_SORT_HPP
#define JIANQIAOSTL_QUICK_SORT_HPP

#include "../../config.hpp"
#include "../../jianqiao_iterator_base.hpp"
#include "../../jianqiao_algorithm_base.hpp"
#include "insertion_sort.hpp"

__JIANQIAO_BEGIN__

template <typename T>
inline const T& __median(const T& a, const T& b, const T& c){
    // 返回 a b c当中中间大小的
    if(a < b){
        if(b < c){
            return b;
        }else if(a < c){
            return c;
        }else{
            return a;
        }
    }else if(a < c){
        return a;
    }
    else if(b < c) {
        return c;
    }
}

template <typename T, typename Comp>
inline const T& __median(const T& a, const T& b, const T& c, Comp comp){
    // 返回 a b c当中中间大小的
    if(comp(a, b)){
        if(comp(b, c)){
            return b;
        }else if(comp(a, c)){
            return c;
        }else{
            return a;
        }
    }else if(comp(a, c)){
        return a;
    }
    else if(comp(b, c)){
        return c;
    }
    return b;
}


template <typename RandomAccessIterator, typename T>
RandomAccessIterator __unguarded_partition(
        RandomAccessIterator first, RandomAccessIterator last, T pivot
        ){
    while(true){
        while(*first < pivot){
            // 在前面的比枢轴小的时候向后移动first指针
            ++first;
        }

        // last 原来应该指向的是最后一个元素下面的一个元素
        --last;

        while(pivot < *last){
            // 找到后面第一个不大雨pivot的
            --last;
        }

        // 两个指针已经交叉了
        if(!(first < last))
            return first;

        Jianqiao::iter_swap(first, last); // 交换

        ++first;
    }
}

template <typename RandomIterator>
void __quick_sort(
        RandomIterator first, RandomIterator last
        ){
    // 递归的快速排序
    if(last - first < 10){
        // 如果元素个数小于10，使用插入排序
        Jianqiao::__insertion_sort(first, last);
    }else{
        // 选取枢轴
        RandomIterator mid = first + (last - first) / 2;
        RandomIterator pivot = __median(*first, *mid, *(last - 1));

        // 交换到最后
        Jianqiao::iter_swap(pivot, last - 1);

        // 分割
        RandomIterator cut = __unguarded_partition(first, last, *(last - 1));

        // 交换回来
        Jianqiao::iter_swap(cut, last - 1);

        // 递归
        __quick_sort(first, cut);
        __quick_sort(cut + 1, last);
    }
}


__JIANQIAO_END__
#endif //JIANQIAOSTL_QUICK_SORT_HPP
