#ifndef __JIANQIAO_ITERATOR_BASE_HPP__
#define __JIANQIAO_ITERATOR_BASE_HPP__

#include "config.hpp"
#include <iterator>
__JIANQIAO_BEGIN__


struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag: public forward_iterator_tag {};
struct random_access_iterator_tag: public bidirectional_iterator_tag {};


template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
struct iterator{
    typedef Category    iterator_category;
    typedef T           value_type;
    typedef Distance    difference_type;
    typedef Pointer     pointer;
    typedef Reference   reference;
};

template <class Iterator>
struct iterator_traits{
    typedef typename Iterator::iterator_category    iterator_category;
    typedef typename Iterator::value_type           value_type;
    typedef typename Iterator::difference_type      difference_type;
    typedef typename Iterator::pointer              pointer;
    typedef typename Iterator::reference            reference;
};


// 对于原生指针进行的特化版本
template <class T>
struct iterator_traits<T*>{
    typedef random_access_iterator_tag      iterator_category;
    typedef T                               value_type;
    typedef ptrdiff_t                       difference_type;
    typedef T*                              pointer;
    typedef T&                              reference;
};

// 对于原生常指针设计的特化
template <class T>
struct iterator_traits<const T*>{
    typedef random_access_iterator_tag      iterator_category;
    typedef T                               value_type;
    typedef ptrdiff_t                       difference_type;
    typedef const T*                        pointer;
    typedef const T&                        reference;
};

// 决定某个迭代器的类型
template <class Iterator>
inline typename iterator_traits<Iterator>::iterator_category
iterator_category(const Iterator&){
    typedef typename iterator_traits<Iterator>::iterator_category category;
    return category();
}

// 决定某个迭代器的distance_type
template <class Iterator>
inline typename iterator_traits<Iterator>::difference_type*
distance_type(const Iterator&){
    return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
}

// 决定某个迭代器的value_type
template <class Iterator>
inline typename iterator_traits<Iterator>::value_type*
value_type(const Iterator&){
    return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
}

// 计算distance 的一组函数

//计算InputIterator 的距离
template <class InputIterator>
inline typename iterator_traits<InputIterator>::difference_type
__distance(InputIterator first, InputIterator last, input_iterator_tag){
    typename iterator_traits<InputIterator>::difference_type n = 0;
    while(first != last){
        ++n;
        ++first;
    }
    return n;
}

//计算 RandomAccessIterator
template <class RandomAccessIterator>
inline typename iterator_traits<RandomAccessIterator>:: difference_type
__distance(RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag){
    return last - first;
}

template <class InputIterator>
inline typename iterator_traits<InputIterator>:: difference_type
distance(InputIterator begin, InputIterator end) {
    typedef typename iterator_traits<InputIterator>::iterator_category category;
    return __distance(begin,end, category());
    // return __distance(begin, end, iterator_category(begin));
}

// 关于advance 的实现
template <class InputIterator, class Distance>
inline void __advance(InputIterator& i, Distance n, input_iterator_tag){
    while(n--) ++i;
}

template <class RandomIterator, class Distance>
inline void __advance(RandomIterator& i,Distance n, random_access_iterator_tag){
    i +=n;
}

template <class BidirectionalIterator, class Distance>
inline void __advance(BidirectionalIterator& i, Distance n, bidirectional_iterator_tag){
    if(n > 0){
        while( n-- )
            ++i;
    }
    else {
        while(n++ )
            --i;
    }
}

template <class InputIterator, class Distance>
inline void advance(InputIterator& i, Distance n){
    __advance(i, n, iterator_category(i));
}








__JIANQIAO_END__
#endif // __JIANQIAO_ITERATOR_BASE_HPP__