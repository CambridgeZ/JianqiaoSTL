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

template <class T>
struct negate: public unary_function<T, T> {
    T operator()(const T &x) const {
        return -x;
    }
};

template <class Arg1, class Arg2, class Result>
struct binary_function {
    /*
     * 二元函数
     * 用于创建拥有两个参数的函数对象和基类
     */
    typedef Arg1 first_argument_type; // 第一个参数类型
    typedef Arg2 second_argument_type; // 第二个参数的类型
    typedef Result result_type;     // 返回值类型
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

template <class T>
struct not_equal_to: public binary_function<T,T,bool>{
    bool operator()(const T& x, const T& y) const {
        return x != y;
    }
};

template <class T>
struct greater: public binary_function<T,T,bool>{
    bool operator()(const T& x, const T& y) const {
        return x > y;
    }
};

template <class T> struct less: public binary_function<T,T,bool>{
    bool operator()(const T& x, const T& y) const {
        return x < y;
    }
};

template <class T>
struct greater_equal: public binary_function<T,T,bool>{
    bool operator()(const T& x, const T& y) const {
        return x >= y;
    }
};

template <class T>
struct less_equal: public binary_function<T,T,bool>{
    bool operator()(const T& x, const T& y) const {
        return x <= y;
    }
};

template<class T>
struct plus : public binary_function<T, T, T> {
    T operator()(const T& x, const T& y) const {
        return x + y;
    }
};

template <class T>
struct minus: public binary_function<T,T,T>{
    T operator()(const T& x, const T& y) const {
        return x - y;
    }
};

template<class T>
struct multiplies : public binary_function<T, T, T> {
    T operator()(const T& x, const T& y) const {
        return x * y;
    }
};

template <class T>
struct divides: public binary_function<T,T,T>{
    T operator()(const T& x, const T& y) const {
        return x / y;
    }
};

template <class T>
struct modulus: public binary_function<T,T,T>{
    T operator()(const T& x, const T& y) const {
        return x % y;
    }
};

template<class T>
struct logical_and : public binary_function<T, T, T> {
    T operator()(const T& x, const T& y) const {
        return x && y;
    }
};

template<class T>
struct logical_or : public binary_function<T, T, T> {
    T operator()(const T& x, const T& y) const {
        return x || y;
    }
};

template <class T>
struct logical_not : public unary_function<T, T> {
    T operator()(const T& x) const {
        return !x;
    }
};

//identity_element
// 证同元素： 返回一个和这个元素进行某种运算之后依然会得到自己的元素

template <class T>
inline T identity_element(plus<T>) {
    // +0 得到的依然是原数字
    return T(0);
}

template <class T>
inline T identity_element(multiplies<T>) {
    // *1 得到的依然是原数字
    return T(1);
}

template <class T>
inline T identity_element(logical_and<T>) {
    // &1 得到的依然是原数字
    return T(true);
}

template <class T>
inline T identity_element(logical_or<T>) {
    // |0 得到的依然是原数字
    return T(false);
}


__JIANQIAO_END__

#endif //JIANQIAOSTL_JIANQIAO_FUNCTION_HPP
