//
// Created by Mac on 24-12-8.
//

#ifndef JIANQIAOSTL_SORT_HPP
#define JIANQIAOSTL_SORT_HPP

#include "../config.hpp"
#include "./sort/insertion_sort.hpp"
#include "./sort/quick_sort.hpp"
#include "./partial_sort.hpp"

__JIANQIAO_BEGIN__

template <typename Size> Size __lg(Size n);
template <typename RandomAccessIterator, typename T, typename Size>
void __introsort_loop(RandomAccessIterator first,
                      RandomAccessIterator last,T*,
                      Size depth_limit);

template <typename RandomAccessIterator> void __final_insertion_sort(RandomAccessIterator first, RandomAccessIterator last);

template <typename RandomAccessIterator> void __unguarded_insertion_sort(RandomAccessIterator first, RandomAccessIterator last);

template <typename RandomAccessIterator>
inline void sort(
        RandomAccessIterator first, RandomAccessIterator last
        ){
    if(first != last){
        // 如果其中需要排序的元素的个数大于16， 则开始考虑使用插入排序进行排序
        __introsort_loop(first, last, value_type(first), __lg(last-first)*2);
        __final_insertion_sort(first, last);
    }
}

// 找到 2^k <=n 的最大值 k
template <typename  Size>
inline Size __lg(Size n){
    Size k;
    for(k =0; n>1 ; n>>=1) ++k;
    return k;
}

const int jianqiao_threshold = 16;

template <typename RandomAccessIterator, typename T, typename Size>
void __introsort_loop(RandomAccessIterator first,
                      RandomAccessIterator last, T*,
                      Size depth_limit){
    /*
     * introsort会检测quicksort是不是恶化了，也就是出现了最坏的情况
     * 这里的 depth_limit表示允许进行分割的最大次数，当超过了这个次数，
     */

    while(last - first > jianqiao_threshold){
        if(depth_limit == 0 ){
            // 是否依然有分割的次数，如果没有分割的次数，说明已经恶化了
            /*
             * 这个时候该用partial_sort当中提供的排序算法进行排序，这里面使用的是heap_sort算法
             * 在分割恶化的时候开始采用heap_sort
             */
            Jianqiao::partial_sort(first, last ,last);
            return ;
        }
        --depth_limit;

        /*
         * 还没有恶化的时候，采用 median-3 partition ，选择一个枢轴进行快速排序
         */

        RandomAccessIterator cut = __unguarded_partition(first, last,
                                                         T(__median(
                                                                 *first, *(first+ (last-first)/2), *last
                                                                 )));

        // 对于右半部分进行排序
        __introsort_loop(cut, last, value_type(first), depth_limit);

        // 这个时候再次进入while循环的时候，前面完成的是对于左半部分进行排序
        last = cut;
    }
}

template <class RandomAccessIterator>
void __final_insertion_sort(RandomAccessIterator first, RandomAccessIterator last){
    if(last - first > jianqiao_threshold){
        // 说明是经过前面的快速排序，然后分成了若干个长度小于16的有序子串

        // 对于前面的16个进行插入排序
        __insertion_sort(first, first+jianqiao_threshold);

        // 对于后面部分也是用插入排序
        __unguarded_insertion_sort(first + jianqiao_threshold, last);
        /*
         * 为什么会是用插入排序而不是冒泡排序：因为如果数列本身是有序的，那么插入排序的速度才是最快的
         * 为什么两次插入排序就一定能得到： 因为经过前面的划分之后，前面的一定都是比枢轴小的，后面的一定都是比枢轴大的，所以分别进行排序就可以了
         */
    }
    else{
        // 说明是长度太小了，不用进行快速排序，直接进行插入排序
        __insertion_sort(first, last);
    }
}

template <typename RandomAccessIterator, typename T>
void __unguarded_insertion_sort_aux(RandomAccessIterator first, RandomAccessIterator last, T*){
    for(RandomAccessIterator i = first ; i != last; ++i){
        __unguarded_linear_insert(i, T(*i));
    }
}

template <class RandomAccessIterator>
inline void __unguarded_insertion_sort(RandomAccessIterator first, RandomAccessIterator last){
    __unguarded_insertion_sort_aux(first, last, value_type(first));
}




__JIANQIAO_END__
#endif //JIANQIAOSTL_SORT_HPP
