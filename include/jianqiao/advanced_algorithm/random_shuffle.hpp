//
// Created by Mac on 24-11-26.
//

#ifndef JIANQIAOSTL_RANDOM_SHUFFLE_HPP
#define JIANQIAOSTL_RANDOM_SHUFFLE_HPP

#include "../config.hpp"
#include "../jianqiao_algorithm_base.hpp"
#include "../jianqiao_iterator.hpp"
#include <cstdlib>

__JIANQIAO_BEGIN__

template <class RandomAccessIterator, class Distance>
void __random_shuffle(RandomAccessIterator first, RandomAccessIterator last, Distance*) {
    Distance n = last - first;
    if (n > 1) { // 如果元素个数大于1才进行下面的操作，否则不需要操作
        for (RandomAccessIterator i = first + 1; i != last; ++i) {
            RandomAccessIterator j = first + std::rand() % (i - first + 1);
            // 将每个元素和前面的某个随机的元素进行交换
            Jianqiao::iter_swap(i, j);
        }
    }
}

template <class RandomAccessIterator>
inline void random_shuffle(RandomAccessIterator first, RandomAccessIterator last ){
    __random_shuffle(first, last, Jianqiao::distance_type(first));
}

template <class RandomAccessIterator, class RandomNumberGenerator>
void random_shuffle(RandomAccessIterator first, RandomAccessIterator last, RandomNumberGenerator& rand) {
    if (first != last) {
        for (RandomAccessIterator i = first + 1; i != last; ++i) {
            RandomAccessIterator j = first + rand(i - first + 1);
            Jianqiao::iter_swap(i, j);
        }
    }
}

__JIANQIAO_END__

#endif //JIANQIAOSTL_RANDOM_SHUFFLE_HPP
