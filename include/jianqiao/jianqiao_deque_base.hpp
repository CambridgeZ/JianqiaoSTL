#ifndef __JIANGQIAO_DEQUE_BASE_HPP__
#define __JIANGQIAO_DEQUE_BASE_HPP__

#include "config.hpp"
#include "jianqiao_iterator.hpp"
#include "alloc.hpp"
__JIANQIAO_BEGIN__

inline size_t __deque_buf_size(size_t n, size_t sz) {
        return n != 0 ? n : (sz < 512 ? size_t(512 / sz) : size_t(1));
}

template < class T, class Ref, class Ptr, size_t BufSiz >
struct __deque_iterator {
    typedef T value_type;
    typedef Ptr pointer;
    typedef Ref reference;
    using iterator = __deque_iterator<T, T&, T*, BufSiz>;
    using const_iterator = __deque_iterator<T, const T&, const T*, BufSiz>;
    static size_t buffer_size() { return __deque_buf_size(BufSiz, sizeof(T)); }
    

    using iterator_category = random_access_iterator_tag;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using map_pointer = pointer*;

    using self = __deque_iterator<T, Ref, Ptr, BufSiz>;
    
    // 保持与容器的联系
    T* cur;     // 当前缓冲区的当前元素
    T* first;   // 当前缓冲区的头
    T* last;    // 当前缓冲区的尾
    map_pointer node; // 指向管控中心

    void set_node(map_pointer new_node) {
        // 切换节点
        node = new_node;
        first = *node;
        last = first + difference_type(buffer_size());
    }

    reference operator*() const { return *cur; }
    pointer operator->() const { return &(operator*()); }
    difference_type operator-(const self& x) const {
        // 计算两个迭代器之间的距离
        return difference_type(buffer_size()) * (node - x.node - 1) + (cur - first) + (x.last - x.cur);
    }

    // 重载++ --
    self& operator++() {
        ++cur;
        if (cur == last) {
            set_node(node + 1);
            cur = first;
        }
        return *this;
    }

    self operator++(int) {
        self tmp = *this;
        ++*this;
        return tmp;
    }

    self& operator--() {
        if (cur == first) {
            set_node(node - 1);
            cur = last;
        }
        --cur;
        return *this;
    }

    self operator--(int) {
        self tmp = *this;
        --*this;
        return tmp;
    }

    // 实现随机访问
    self& operator += (difference_type n){
        difference_type offset = n+ (cur - first);
        if(offset >= 0 && offset < difference_type(buffer_size())){
            // 在同一个缓冲区当中
            cur +=n;
        }
        else {
            difference_type node_offset ;
            if(offset > 0){
                node_offset = offset/difference_type(buffer_size());
            }
            else {
                node_offset = -difference_type((-offset-1)/buffer_size()) -1;
            }
            // 切换到正确的节点
            set_node(node+node_offset);
            // 切换到正确的元素
            cur = first + (offset - node_offset * difference_type(buffer_size()));
        }

        return *this;
    }

    self operator + (difference_type n) const {
        self tmp = *this;
        return tmp +=n;
    }

    self operator -= (difference_type n){
        return *this += -n;
    }

    self operator - (difference_type n) const {
        self tmp = *this;
        return tmp-=n;
    }

    reference operator[](difference_type n) const {
        return *(*this + n);
    }

    bool operator == (const self& x) const {
        return cur == x.cur;
    }

    bool operator != (const self& x) const {
        return !(*this == x);
    }

    bool operator < (const self& x) const {
        return (node == x.node) ? (cur < x.cur) : (node < x.node);
    }
};

__JIANQIAO_END__
#endif // __JIANGQIAO_DEQUE_BASE_HPP__