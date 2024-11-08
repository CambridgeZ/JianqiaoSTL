//
// Created by Mac on 24-11-8.
//

#ifndef JIANQIAOSTL_JIANQIAO_FUNCTION_HPP
#define JIANQIAOSTL_JIANQIAO_FUNCTION_HPP

#include "config.hpp"

__JIANQIAO_BEGIN__

template <class Arg, class Result>
struct unary_function {
    typedef Arg argument_type;
    typedef Result result_type;
};

template <class T>
struct identity : public unary_function<T, T> {
    const T &operator()(const T &x) const {
        return x;
    }
};



__JIANQIAO_END__

#endif //JIANQIAOSTL_JIANQIAO_FUNCTION_HPP
