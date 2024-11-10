//
// Created by Mac on 24-11-8.
//

#ifndef JIANQIAOSTL_JIANQIAO_FUNCTION_HPP
#define JIANQIAOSTL_JIANQIAO_FUNCTION_HPP

#include "config.hpp"

__JIANQIAO_BEGIN__

template <class Arg, class Result>
struct unary_function {
    /*
     * 一元函数
     * 用于创建拥有一个参数的函数对象和基类
     */
    typedef Arg argument_type;
    typedef Result result_type;
};

template <class T>
struct identity : public unary_function<T, T> {
    const T &operator()(const T &x) const {
        return x;
    }
};

template <class Arg1, class Arg2, class Result>
struct binary_function {
    /*
     * 二元函数
     * 用于创建拥有两个参数的函数对象和基类
     */
    typedef Arg1 first_argument_type;
    typedef Arg2 second_argument_type;
    typedef Result result_type;
};

template <class Pair>
struct select1st : public unary_function<Pair, typename Pair::first_type> {
    /*
     * 选择第一个元素
     * 用于创建拥有一个参数的函数对象和基类
     */
    const typename Pair::first_type &operator()(const Pair &x) const {
        return x.first;
    }
};

template<class T>
struct equal_to : public binary_function<T, T, bool> {
    bool operator()(const T& x, const T& y) const {
        return x == y;
    }
};





__JIANQIAO_END__

#endif //JIANQIAOSTL_JIANQIAO_FUNCTION_HPP
