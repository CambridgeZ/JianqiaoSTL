//
// Created by Mac on 24-12-9.
//

#ifndef JIANQIAOSTL_EQUAL_RANGE_HPP
#define JIANQIAOSTL_EQUAL_RANGE_HPP

#include "lower_bound.hpp"
#include "upper_bound.hpp"
#include "../config.hpp"
#include "../jianqiao_pair.hpp"

__JIANQIAO_BEGIN__

template <typename ForwardIterator, typename T>
Jianqiao::pair<ForwardIterator, ForwardIterator> equal_range(ForwardIterator first, ForwardIterator last, const T& value) {
    return Jianqiao::make_pair(lower_bound(first, last, value), upper_bound(first, last, value));
}

__JIANQIAO_END__
#endif //JIANQIAOSTL_EQUAL_RANGE_HPP
