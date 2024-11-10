//
// Created by Mac on 24-11-9.
//

#ifndef JIANQIAOSTL_JIANQIAO_HASHTABLE_SUPPORT_HPP
#define JIANQIAOSTL_JIANQIAO_HASHTABLE_SUPPORT_HPP

#include "config.hpp"
#include "jianqiao_iterator_base.hpp"

__JIANQIAO_BEGIN__

template <class Value>
struct __hashtable_node {
    __hashtable_node* next;
    Value val;
};

template <class Value, class Key, class HashFcn, class ExtractKey, class EqualKey, class Alloc> class hashtable;
template <class Value, class Key, class HashFcn, class ExtractKey, class EqualKey, class Alloc> struct __hashtable_const_iterator;

template <class Value, class Key, class HashFcn, class ExtractKey, class EqualKey, class Alloc>
struct __hashtable_iterator{
    using hashtable = hashtable<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>;
    using iterator = __hashtable_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>;
    using node = __hashtable_node<Value>;
    using const_iterator = __hashtable_const_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>;

    using iterator_category = forward_iterator_tag;
    using value_type = Value;
    using difference_type = ptrdiff_t;
    using size_type = size_t;
    using reference = Value&;
    using pointer = Value*;

    node* cur; // 迭代器指向的当前节点
    hashtable* ht; // 保持对容器的连结，因为可能需要调整

    __hashtable_iterator(node* n, hashtable *tab): cur(n), ht(tab) {}
    __hashtable_iterator() {}
    reference operator*() const { return cur->val; }
    pointer operator->() const { return &(operator*()); }
    iterator& operator++();
    iterator operator++(int){
        iterator tmp = *this;
        ++*this;
        return tmp;
    }
    bool operator==(const iterator& it) const { return cur == it.cur; }
    bool operator!=(const iterator& it) const { return cur != it.cur; }

};

template <class Value, class Key, class HashFcn, class ExtractKey, class EqualKey, class Alloc>
__hashtable_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>&
        __hashtable_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>::operator++() {
            const node* old = cur;
            cur = cur->next;
            if(!cur){// 已经到了当前链表的最后一个
                size_type bucket = ht->bkt_num(old->val);

                while(!cur && ++bucket < ht->buckets.size()){
                    // 找到下面一个有元素的链表
                    cur = ht->buckets[bucket];
                }
            }

            return *this;
        }

        // hashtable 的const_iterator
template <class Value, class Key, class HashFcn, class ExtractKey, class EqualKey, class Alloc>
struct __hashtable_const_iterator{
    using hashtable = hashtable<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>;
    using iterator = __hashtable_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>;
    using node = __hashtable_node<Value>;
    using const_iterator = __hashtable_const_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>;

    using iterator_category = forward_iterator_tag;
    using value_type = Value;
    using difference_type = ptrdiff_t;
    using size_type = size_t;
    using reference = const Value&;
    using pointer = const Value*;

    const node* cur;
    const hashtable* ht;

    __hashtable_const_iterator(const node* n, const hashtable* tab): cur(n), ht(tab) {}
    __hashtable_const_iterator() {}
    reference operator*() const { return cur->val; }
    pointer operator->() const { return &(operator*()); }
    const_iterator& operator++();
    const_iterator operator++(int){
        const_iterator tmp = *this;
        ++*this;
        return tmp;
    }
    bool operator==(const const_iterator& it) const { return cur == it.cur; }
    bool operator!=(const const_iterator& it) const { return cur != it.cur; }

    __hashtable_const_iterator(const iterator& it): cur(it.cur), ht(it.ht) {}

};

// hashtable 的const_iterator 的operator++
template <class Value, class Key, class HashFcn, class ExtractKey, class EqualKey, class Alloc>
__hashtable_const_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>&
        __hashtable_const_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>::operator++() {
            const node* old = cur;
            cur = cur->next;
            if(!cur){// 已经到了当前链表的最后一个
                size_type bucket = ht->bkt_num(old->val);

                while(!cur && ++bucket < ht->buckets.size()){
                    // 找到下面一个有元素的链表
                    cur = ht->buckets[bucket];
                }
            }

            return *this;
        }





__JIANQIAO_END__

#endif //JIANQIAOSTL_JIANQIAO_HASHTABLE_SUPPORT_HPP
