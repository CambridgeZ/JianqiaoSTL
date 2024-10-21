#ifndef __JIANQIAO_DEQUE_HPP__
#define __JIANQIAO_DEQUE_HPP__



#include "config.hpp"
#include "alloc.hpp"
#include "jianqiao_deque_base.hpp"
#include <cmath>
#include <memory>

using std::max;
using std::uninitialized_fill;
using std::copy_backward;
using std::copy;
// using std:: allocator;

#if USE_DEQUE

// 分配器在对于指针进行处理的时候出现问题

__JIANQIAO_BEGIN__

template <typename T, class Alloc = allocator<T>, size_t BufSiz = 0 >
class deque{
public:
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using size_type = size_t;
    using difference_type = ptrdiff_t;  
    using iterator = __deque_iterator<T, T&, T*, BufSiz>;
    using const_iterator = __deque_iterator<T, const T&, const T*, BufSiz>;

protected:
    using map_pointer = pointer*;
    map_pointer map;
    size_type map_size; // map内可以容纳的指针大小
    iterator start;
    iterator finish;

public:
    iterator begin(){
        return start;
    }
    iterator end(){
        return finish;
    }

    reference operator[](size_type n){
        return start[difference_type(n)];
    }

    reference front(){
        return *start;
    }

    reference back(){
        iterator tmp = finish;
        --tmp;
        return *tmp;
    }

    size_type size() const {
        return finish - start;
    }

    size_type max_size() const {
        return size_type(-1);
    }

    bool empty() const {
        return finish == start;
    }

    deque() : start(), finish(), map(0), map_size(0){
        create_map_and_nodes(0);
    }

protected:
    // 配置元素
    typedef simple_alloc<value_type, Alloc> data_allocator;

    // 配置指针
    typedef simple_alloc<pointer, Alloc> map_allocator;

public:
    deque(int n, const value_type& value){
        fill_initialize(n, value);
    }
protected:
    size_type buffer_size() const {
        return __deque_buf_size(BufSiz, sizeof(value_type));
    }

    void fill_initialize(size_type n, const value_type& value){
        create_map_and_nodes(n);
        map_pointer cur;
        try{
            for(cur = start.node; cur < finish.node; ++cur){
                uninitialized_fill(*cur, *cur + buffer_size(), value);
            }
            uninitialized_fill(finish.first, finish.cur, value);
        }
        catch(...){
            // commit or rollback
        }
    }

    pointer allocate_node(){
        return data_allocator::allocate(buffer_size());
    }

    void create_map_and_nodes(size_type num_elements){
        // 需要的节点数
        size_type num_nodes = num_elements / buffer_size() + 1;

        // 一个map最少要有8个指针, 一个指针指向一个buffer, 最多有num_nodes + 2个指针
        map_size = max((size_type)8, num_nodes + 2);
        map = map_allocator::allocate(map_size);

        // 使map的起始位置指向中间位置
        map_pointer nstart = map + (map_size - num_nodes) / 2;
        map_pointer nfinish = nstart + num_nodes - 1;

        map_pointer cur;
        try{
            // 为map中的每个指针分配内存
            for(cur = nstart; cur <= nfinish; ++cur){
                *cur = allocate_node();
            }
        }
        catch(...){
            // commit or rollback
        }
        start.set_node(nstart);
        finish.set_node(nfinish);
        start.cur = start.first;
        finish.cur = finish.first + num_elements % buffer_size();
    }
public:
    void push_back(const value_type& t){
        if(finish.cur != finish.last - 1){
            construct(finish.cur, t);
            ++finish.cur;
        }
        else{
            push_back_aux(t);
        }
    }

protected: 
    void reserve_map_at_back(size_type nodes_to_add = 1){
        if(nodes_to_add + 1 > map_size - (finish.node - map)){
            // 如果map的空间不够, 重新分配
            reallocate_map(nodes_to_add, false);
        }
    }

    // 重新分配map
    void reallocate_map(size_type nodes_to_add, bool add_at_front){
        size_type old_num_nodes = finish.node - start.node + 1; // 原来的节点数
        size_type new_num_nodes = old_num_nodes + nodes_to_add; // 新的节点数

        map_pointer new_nstart;
        // 如果map的空间足够, 直接调整map中指针的位置
        if (map_size > 2 * new_num_nodes) {
            // new_nstart 位于 map 的中间位置
            new_nstart = map + (map_size - new_num_nodes) / 2 + (add_at_front ? nodes_to_add : 0); // 新的start的位置
            // 如果在前面插入, 将原来的元素向后移动
            if (new_nstart < start.node)
                std::copy(start.node, finish.node + 1, new_nstart);
            else
            // 如果在后面插入, 将原来的元素向前移动
                std::copy_backward(start.node, finish.node + 1, new_nstart + old_num_nodes);
        } else {
            // 如果map的空间不够, 重新分配
            size_type new_map_size = map_size + max(map_size, nodes_to_add) + 2;
            map_pointer new_map = map_allocator::allocate(new_map_size);
            // new_nstart 位于 map 的中间位置
            new_nstart = new_map + (new_map_size - new_num_nodes) / 2 + (add_at_front ? nodes_to_add : 0);
            std::copy(start.node, finish.node + 1, new_nstart);
            map_allocator::deallocate(map, map_size);
            // map_allocator::deallocate(reinterpret_cast<int*>(map), map_size * sizeof(pointer));
            map = new_map;
            map_size = new_map_size;
        }

        start.set_node(new_nstart);
        finish.set_node(new_nstart + old_num_nodes - 1);
    }


    void push_back_aux(const value_type& t){
        value_type t_copy = t;
        reserve_map_at_back();  // 如果map的空间不够, 重新分配
        *(finish.node + 1) = allocate_node();  // 为map中的新指针分配内存
        try{
            construct(finish.cur, t_copy);      // 在新的buffer中构造元素
            finish.set_node(finish.node + 1); // 调整finish的位置, 指向新的buffer
            finish.cur = finish.first;      // 调整finish的位置, 指向新的buffer的第一个元素
        }
        catch(...){
            // commit or rollback
            // rollback
            data_allocator::deallocate(*(finish.node + 1), buffer_size());
            *(finish.node + 1) = 0;

            throw;
        }
    }

public: 
    void push_front(const value_type& t){
        if(start.cur != start.first){
            construct(start.cur - 1, t);
            --start.cur;
        }
        else{
            push_front_aux(t);
        }
    }

protected:
    void reserve_map_at_front(size_type nodes_to_add = 1){
        if(nodes_to_add > start.node - map){
            reallocate_map(nodes_to_add, true);
        }
    }

    void push_front_aux(const value_type& t){
        value_type t_copy = t;
        reserve_map_at_front();
        *(start.node - 1) = allocate_node();
        try{
            start.set_node(start.node - 1);
            start.cur = start.last - 1;
            construct(start.cur, t_copy);
        }
        catch(...){
            // commit or rollback
            ++start;
            data_allocator::deallocate(*(start.node - 1), buffer_size());
            *(start.node - 1) = 0;
            throw;
        }
    }

public:
    void pop_back(){
        if(finish.cur != finish.first){
            // 不是当前缓冲区的最后一个元素
            --finish.cur;
            destroy(finish.cur);
        }
        else{
            pop_back_aux();
        }
    }

protected:
    void pop_back_aux(){
        data_allocator::deallocate(finish.first, buffer_size());
        finish.set_node(finish.node - 1);
        finish.cur = finish.last - 1;
        destroy(finish.cur);
    }

public:
    void pop_front(){
        if(start.cur != start.last - 1){
            destroy(start.cur);
            ++start.cur;
        }
        else{
            pop_front_aux();
        }
    }

protected:
    void pop_front_aux(){
        destroy(start.cur);
        data_allocator::deallocate(start.first, buffer_size());
        start.set_node(start.node + 1);
        start.cur = start.first;
    }

public:
    void clear(){
        // 释放出了头尾元素之外的每一个缓冲区，这些缓冲区都一定是满的
        for(map_pointer node = start.node + 1; node < finish.node; ++node){
            destroy(*node, *node + buffer_size());
            data_allocator::deallocate(*node, buffer_size());
        }

        if(start.node != finish.node){ // 不只有一个缓冲区的情况
            destroy(start.cur, start.last);
            destroy(finish.first, finish.cur);
            data_allocator::deallocate(finish.first, buffer_size());
        }
        else{
            destroy(start.cur, finish.cur);
        }

        finish = start;
    }

    iterator erase(iterator pos){
        iterator next = pos;
        ++next;
        difference_type index = pos - start;
        if(index < (size() >> 1)){
            // 如果删除点之前的元素比较少, 就移动删除点之前的元素
            copy_backward(start, pos, next);    // 将删除点之前的元素向前移动
            pop_front();                        // 删除第一个元素
        }
        else{
            // 如果删除点之后的元素比较少, 就移动删除点之后的元素
            copy(next, finish, pos);
            pop_back();
        }
        return start + index;
    }

    iterator erase(iterator first, iterator last){
        if(first == start && last == finish){
            clear();
            return finish;
        }
        else{
            difference_type n = last - first;
            difference_type elems_before = first - start;
            if(elems_before < (size() - n) / 2){
                copy_backward(start, first, last);
                iterator new_start = start + n;
                destroy(start, new_start);
                for(map_pointer cur = start.node; cur < new_start.node; ++cur){
                    data_allocator::deallocate(*cur, buffer_size());
                }
                start = new_start;
            }
            else{
                copy(last, finish, first);
                iterator new_finish = finish - n;
                destroy(new_finish, finish);
                for(map_pointer cur = new_finish.node + 1; cur <= finish.node; ++cur){
                    data_allocator::deallocate(*cur, buffer_size());
                }
                finish = new_finish;
            }
            return start + elems_before;
        }
    }

    iterator insert(iterator pos, const value_type& x){
        if(pos.cur == start.cur){
            push_front(x);
            return start;
        }
        else if(pos.cur == finish.cur){
            push_back(x);
            iterator tmp = finish;
            --tmp;
            return tmp;
        }
        else{
            return insert_aux(pos, x);
        }
    }

    iterator insert_aux(iterator pos, const value_type& x){
        difference_type index = pos - start; // 插入点前面的元素个数
        value_type x_copy = x;
        if(index < size() / 2){
            push_front(front());
            iterator front1 = start;
            ++front1;   // front1指向第二个元素，即原来的第一个元素
            iterator front2 = front1;
            ++front2;   // front2指向第三个元素，即原来的第二个元素
            pos = start + index;
            iterator pos1 = pos;
            ++pos1;
            copy(front2, pos1, front1);
        }
        else{
            push_back(back());
            iterator back1 = finish;
            --back1;
            iterator back2 = back1;
            --back2;
            pos = start + index;
            copy_backward(pos, back2, back1);
        }
        *pos = x_copy;
        return pos;
    }

    ~deque(){
        clear();
        // data_allocator::deallocate(*start.node, buffer_size());
        // map_allocator::deallocate(map, map_size);
    }

};



__JIANQIAO_END__
#endif // USE_DEQUE
#endif // __JIANQIAO_DEQUE_HPP__