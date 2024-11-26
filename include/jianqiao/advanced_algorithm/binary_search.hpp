//
// Created by Mac on 24-11-26.
//

#ifndef JIANQIAOSTL_BINARY_SEARCH_HPP
#define JIANQIAOSTL_BINARY_SEARCH_HPP

#include "../config.hpp"
#include "../jianqiao_iterator.hpp"
#include "../jianqiao_algorithm_base.hpp"
#include "lower_bound.hpp"

__JIANQIAO_BEGIN__

/*
 * binary_search: 在[first, last)中查找value, 返回是否找到
 */

template <typename ForwardIterator, typename T>
bool binary_search(ForwardIterator first, ForwardIterator last, const T& value){
    ForwardIterator it = Jianqiao::lower_bound(first, last, value);
    return it != last && *it == value;
}

template <typename ForwardIterator, typename T, typename Compare>
bool binary_search(ForwardIterator first, ForwardIterator last, const T& value, Compare comp){
    ForwardIterator it = Jianqiao::lower_bound(first, last, value, comp);
    return it != last && !comp(value, *it);
}

__JIANQIAO_END__

#endif //JIANQIAOSTL_BINARY_SEARCH_HPP
