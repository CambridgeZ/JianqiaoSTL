#ifndef __JIANQIAO_LIST_BASE_HPP__
#define __JIANQIAO_LIST_BASE_HPP__

#include "config.hpp"
#include "jianqiao_iterator.hpp"
#include "jianqiao_iterator_base.hpp"

__JIANQIAO_BEGIN__

using Jianqiao::bidirectional_iterator_tag;

template <typename T>
struct __list_node {
    __list_node<T>* prev;
    __list_node<T>* next;
    T data;
};

template <typename T, typename Ref, typename Ptr>
struct __list_iterator{
    typedef __list_iterator<T, T&, T*> iterator;
    using self = __list_iterator<T, Ref, Ptr>;
    
    using iterator_category = bidirectional_iterator_tag;
    using value_type = T;
    using pointer = Ptr;
    using reference = Ref;
    using link_type = __list_node<T>*;
    using difference_type = ptrdiff_t;
    using size_type = size_t;

    link_type node; // 迭代器内部指向的节点

    __list_iterator(link_type x): node(x) {}
    __list_iterator() {}
    __list_iterator(const iterator& x): node(x.node) {}

    bool operator==(const self& x) const {
        return node == x.node;
    }

    bool operator!=(const self& x) const {
        return node != x.node;
    }

    reference operator*() const {
        return node->data;
    }

    pointer operator->() const {
        return &(operator*());
    }

    self& operator++(){
        node = (link_type)((*node).next);
        return *this;
    }

    self operator++(int){
        self tmp = *this;
        ++*this;
        return tmp;
    }

    self& operator--(){
        node = (link_type)((*node).prev);
        return *this;
    }

    self operator--(int){
        self tmp = *this;
        --*this;
        return tmp;
    }
};

__JIANQIAO_END__

#endif // __JIANQIAO_LIST_BASE_HPP__