#ifndef __JIANQIAO_LIST_HPP__
#define __JIANQIAO_LIST_HPP__

#include <memory>

#include "config.hpp"
#include "jianqiao_list_base.hpp"
#include "alloc.hpp"

using Jianqiao::_construct;
using std::swap;


__JIANQIAO_BEGIN__

template <typename T, typename Alloc = allocator<T> >
class list {

protected:
    typedef __list_node<T> list_node;
    typedef simple_alloc<list_node, Alloc> data_allocator;
    using iterator = __list_iterator<T, T&, T*>;
    using reference = T&;
    using list_node_allocator = simple_alloc<list_node, Alloc>;
    using value_type = T;
    using pointer = T*;

    list_node* node;// 一个空节点，不存储数据，只是用来标识头尾,指向尾部
public:
    typedef list_node* link_type;
protected:
    link_type get_node(){
        return list_node_allocator::allocate();
    }
    void put_node(link_type p){
        Jianqiao::_deallocate(p);
    }

    // 初始化一个节点，并且用x来初始化
    link_type create_node(const T& x){
        link_type p = get_node();
        _construct(&p->data, x);
        return p;
    }

    void destroy_node(link_type p){
        Jianqiao::_destroy(&p->data);
        put_node(p);
    }

    void empty_initialize(){
        node = get_node();
        node->next = node;
        node->prev = node;
    }

public:
    iterator begin() const {
        return (link_type)((*node).next);
    }

    iterator end() const {
        return node;
    }

    bool empty() const {
        return (*node).next == node;
    }

    size_t size() const {
        size_t result = 0;
        distance(begin(), end(), result);
        return result;
    }

    reference front() {
        return *begin();
    }

    reference back() {
        return *(--end());
    }

    list(){
        empty_initialize();
    }

    iterator insert(iterator position, const T& x){
        link_type tmp = create_node(x);
        tmp->next = position.node;
        tmp->prev = position.node->prev;
        (link_type(position.node->prev))->next = tmp;
        position.node->prev = tmp;
        return tmp;
    }

    void push_back(const T& x){
        insert(end(), x);
    }

    void push_front(const T& x){
        insert(begin(), x);
    }

    iterator erase(iterator position){
        link_type next_node = link_type(position.node->next);
        link_type prev_node = link_type(position.node->prev);
        prev_node->next = next_node;
        next_node->prev = prev_node;
        destroy_node(position.node);
        return iterator(next_node);
    }

    void pop_front(){
        erase(begin());
    }

    void pop_back(){
        iterator tmp = end();
        erase(--tmp);
    }

    void clear(){
        link_type cur = (link_type)(*node).next;
        while(cur != node){
            link_type tmp = cur;
            cur = (link_type)(*cur).next;
            destroy_node(tmp);
        }
        (*node).next = node;
        (*node).prev = node;
    }

    ~list(){
        clear();
        put_node(node);
    }

    // 将数值为value的元素移除
    void remove(const T& value){
        iterator first = begin();
        iterator last = end();
        while(first != last){
            iterator next = first;
            ++next;
            if(*first == value){
                erase(first);
            }
            first = next;
        }
    }

    // 移除数值连续相同的元素
    void unique(){
        iterator first = begin();
        iterator last = end();
        if(first == last) return;
        iterator next = first;
        while(++next != last){
            if(*first == *next){
                erase(next);
            }else{
                first = next;
            }
            next = first;
        }
    }

protected:
    void transfer(iterator position, iterator first, iterator last){
        if(position != last){
            (*(link_type((*last.node).prev))).next = position.node;
            (*(link_type((*first.node).prev))).next = last.node;
            (*(link_type((*position.node).prev))).next = first.node;
            link_type tmp = link_type((*position.node).prev);
            (*position.node).prev = (*last.node).prev;
            (*last.node).prev = (*first.node).prev;
            (*first.node).prev = tmp;
        }
    }

public:
    // 将x合并到*this的position位置之前
    void splice(iterator position, list& x){
        if(!x.empty()){
            transfer(position, x.begin(), x.end());
        }
    }

    // 将i所指的元素合并到*this的position位置之前, i可以指向和position相同的list
    void splice(iterator position, list&, iterator i){
        iterator j = i;
        ++j;
        if(position == i || position == j) return;
        transfer(position, i, j);
    }

    // 将[first, last)合并到*this的position位置之前
    void splice(iterator position, list&, iterator first, iterator last){
        if(first != last){
            transfer(position, first, last);
        }
    }

    void merge(list& x){
        iterator first1 = begin();
        iterator last1 = end();
        iterator first2 = x.begin();
        iterator last2 = x.end();
        while(first1 != last1 && first2 != last2){
            if(*first2 < *first1){
                iterator next = first2;
                transfer(first1, first2, ++next);
                first2 = next;
            }else{
                ++first1;
            }
        }
        if(first2 != last2){
            transfer(last1, first2, last2);
        }
    }

    void reverse(){
        if((*node).next == node || link_type((*node).next)->next == node) return;
        iterator first = begin();
        ++first;
        while(first != end()){
            iterator old = first;
            ++first;
            transfer(begin(), old, first);
        }
    }

    // 由于不能采用STL的sort算法，这里实现自己的sort
    // 采用并归排序
    void sort(){
        // 如果链表为空或者只有一个元素，直接返回
        if((*node).next == node || link_type((*node).next)->next == node) 
            return;
        // 采用一些新的List 作为数据存储区域    
        list<T> carry;
        list<T> counter[64];
        int fill = 0;
        while(!empty()){
            // 将当前链表的第一个元素移动到carry中
            carry.splice(carry.begin(), *this, begin());
            int i = 0;
            while(i < fill && !counter[i].empty()){
                // 将carry和counter[i]合并，然后将合并后的结果放到counter[i]中
                counter[i].merge(carry);
                carry.swap(counter[i++]);
            }
            carry.swap(counter[i]);
            if(i == fill) ++fill;
        }
        for(int i = 1; i < fill; ++i){
            counter[i].merge(counter[i-1]);
        }
        swap(counter[fill-1]);
    }

public:
    //swap
    void swap(list& x){
        link_type tmp = node;
        node = x.node;
        x.node = tmp;
    }

};


__JIANQIAO_END__
#endif // __JIANQIAO_LIST_HPP__