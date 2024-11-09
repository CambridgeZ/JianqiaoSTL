//
// Created by Mac on 24-11-8.
//

#ifndef JIANQIAOSTL_JIANQIAO_ALGORITHM_HPP
#define JIANQIAOSTL_JIANQIAO_ALGORITHM_HPP

#include "config.hpp"
__JIANQIAO_BEGIN__

template <class T>
void swap(T& a, T& b){
    T tmp = a;
    a = b;
    b = tmp;
}

// equal
template <class InputIterator1, class InputIterator2>
bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2){
    for(; first1 != last1; ++first1, ++first2){
        if(*first1 != *first2){
            return false;
        }
    }
    return true;
}

// lexicographical_compare
template <class InputIterator1, class InputIterator2>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2){
    for(; first1 != last1 && first2 != last2; ++first1, ++first2){
        if(*first1 < *first2){
            return true;
        }
        if(*first2 < *first1){
            return false;
        }
    }
    return first1 == last1 && first2 != last2;
}

template <typename T>
struct less{
    bool operator()(const T& a, const T& b){
        return a < b;
    }
};




__JIANQIAO_END__
#endif //JIANQIAOSTL_JIANQIAO_ALGORITHM_HPP
