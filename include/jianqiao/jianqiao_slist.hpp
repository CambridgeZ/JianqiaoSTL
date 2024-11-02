//
// Created by Mac on 24-10-28.
//

#ifndef JIANQIAOSTL_JIANQIAO_SLIST_HPP
#define JIANQIAOSTL_JIANQIAO_SLIST_HPP

#include "config.hpp"
#include "alloc.hpp"
#include "jianqiao_iterator_base.hpp"
#include <memory>

__JIANQIAO_BEGIN__

struct __slist_node_base{
    __slist_node_base* next;
    bool operator ==(const __slist_node_base& x) const {
        return next == x.next;
    }

    bool operator !=(const __slist_node_base& x) const {
        return next != x.next;
    }
};

template <typename T>
struct __slist_node : public __slist_node_base{
    T data;
};

inline __slist_node_base* __slist_make_link(__slist_node_base* prev_node, __slist_node_base* new_node){
    new_node->next = prev_node->next;
    prev_node->next = new_node;
    return new_node;
}

inline size_t __slist_size(__slist_node_base* node){
    size_t result = 0;
    for(; node != nullptr; node = node->next){
        ++result;
    }
    return result;
}

struct __slist_iterator_base{
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using iterator_category = forword_iterator_tag; // 单向的迭代器

    __slist_node_base* node; // 用于指向节点的基本结构
    __slist_iterator_base(__slist_node_base* x): node(x) {} // 构造函数

    void incr(){
        node = node->next;
    }

    bool operator== (const __slist_iterator_base& rhs) const{
        return this->node == rhs.node;
    }

    bool operator!= (const __slist_iterator_base& rhs) const{
        return this->node != rhs.node;
    }
};

template<typename T, typename Ref, typename Ptr>
struct __slist_iterator: public  __slist_iterator_base{
    using iterator = __slist_iterator<T,T&,T*>;
    using const_iterator = __slist_iterator<T, const T&, const T*>;
    using self = __slist_iterator<T,Ref,Ptr>;

    using value_type = T;
    using pointer = Ptr;
    using reference = Ref;
    using list_node = __slist_node<T>;

    // 构造函数
    __slist_iterator(list_node* x): __slist_iterator_base(x) {}
    //默认构造函数
    __slist_iterator(): __slist_iterator_base(0) {}
    // 拷贝构造函数
    __slist_iterator(const iterator& x): __slist_iterator_base(x.node){}

    reference operator*() const {
        return (((list_node*) node)->data);
    }

    pointer operator->() const {
        return &(operator*());
    }

    self& operator++(){
        incr();
        return *this;
    }

    self operator++(int){
        // 这个不能传引用，这个必须传值
        self old = *this;
        incr();
        return old;
    }

    // 不可以实现operator -- ，因为这个是单向的迭代器
};


// 下面开始对于Slist的实现

template<class T, class Alloc = allocator<__slist_node<T>> >
class slist{
public:
    using value_type = T;
    using pointer = value_type*;
    using reference = value_type&;
    using const_reference = const value_type&;
    using size_type = size_t;
    using difference_type = ptrdiff_t;

    using iterator = __slist_iterator<T, T&, T*>;
    using const_iterator = __slist_iterator<T, const T&, const T*>;

private:
    using list_node = __slist_node<T>;
    using list_node_base = __slist_node_base;
    using iterator_base = __slist_node_base;
    using list_node_allocator = simple_alloc<list_node, Alloc>;

    static list_node* create_node(const value_type& x){
        // 创建一个节点
        list_node* node = list_node_allocator::allocate();
        try{
            construct(&node->data, x);
            node->next = 0;
        }
        catch(...){
            list_node_allocator::deallocate(node);
        }

        return node;
    }

    static void destroy_node(list_node* node){
        destroy(node);
        list_node_allocator::deallocate(node);
    }

private:
    list_node_base head; // 头部，不是指针，是实物
public:
    slist(){
        head.next = nullptr;
    }

    ~slist(){
        clear();
    }
private:
    void clear(){
        list_node* cur = (list_node*) head.next;
        while(cur != nullptr){
            list_node* tmp = cur;
            cur = (list_node*) cur->next;
            destroy_node(tmp);
        }
        head.next = nullptr;
    }
public:
    iterator begin(){
        return iterator((list_node*) head.next);
    }

    iterator end(){
        return iterator(nullptr);
    }

    size_type size() const {
        return __slist_size(head.next);
    }

    bool empty() const {
        return head.next == nullptr;
    }

    void swap(slist& x){
        list_node_base* tmp = head.next;
        head.next = x.head.next;
        x.head.next = tmp;
    }

    reference front(){
        return ((list_node*) head.next)->data;
    }

    void push_front(const value_type& x){
        __slist_make_link(&head, create_node(x));
    }

    void pop_front(){
        list_node* node = (list_node*) head.next;
        head.next = node->next;
        destroy_node(node);
    }

    iterator previous(const_iterator pos){
        return iterator((list_node*) __slist_previous(&head, pos.node));
    }

    iterator insert_after(iterator pos, const value_type& x){
        return iterator((list_node*) __slist_make_link(pos.node, create_node(x)));
    }

    iterator erase_after(iterator pos){
        list_node* node = (list_node*) __slist_erase_after(pos.node);
        destroy_node(node);
        return iterator(node);
    }

    void remove(const value_type& x){
        list_node_base* cur = &head;
        while(cur->next != nullptr){
            list_node* node = (list_node*) cur->next;
            if(node->data == x){
                list_node_base* next_node = node->next;
                destroy_node(node);
                cur->next = next_node;
            }
            else{
                cur = cur->next;
            }
        }
    }

    void unique(){
        list_node_base* cur = head.next;
        if(cur != nullptr){
            while(cur->next != nullptr){
                list_node* next_node = (list_node*) cur->next;
                if(((list_node*) cur)->data == next_node->data){
                    list_node_base* next_next_node = next_node->next;
                    destroy_node(next_node);
                    cur->next = next_next_node;
                }
                else{
                    cur = cur->next;
                }
            }
        }
    }

    void splice_after(iterator pos, slist& x){
        if(x.head.next != nullptr){
            __slist_splice_after(pos.node, &x.head);
        }
    }
};

__JIANQIAO_END__

#endif //JIANQIAOSTL_JIANQIAO_SLIST_HPP
