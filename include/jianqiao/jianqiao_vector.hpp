#ifndef __JIANQIAO_VECTOR_HPP__
#define __JIANQIAO_VECTOR_HPP__

#include "config.hpp"
#include "jianqiao_iterator.hpp"
#include "alloc.hpp"

#include <memory>
#include <cstddef>
#include <algorithm>
#include <cmath>

using std::uninitialized_fill_n;
using std::uninitialized_copy;
using std::copy_backward;
using std::fill;
using std::fmax;
using std::copy;

__JIANQIAO_BEGIN__

template <typename T, typename Alloc = allocator<T> >
class vector {
public:
    typedef T value_type;
    typedef value_type* pointer;
    typedef value_type* iterator; // 用普通指针
    typedef value_type& reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef const value_type* const_pointer;
    typedef const value_type& const_reference;
    typedef const iterator const_iterator;

protected:
    typedef simple_alloc<value_type, Alloc> data_allocator;
    iterator start; // 表示目前使用空间的头
    iterator finish; // 表示目前使用空间的尾
    iterator end_of_storage; // 表示目前可用空间的尾

    void insert_aux(iterator position, const T& x);
    void deallocate(){
        if(start){
            data_allocator::deallocate(start, end_of_storage - start);
        }
    }

    void fill_initialize(size_type n, const T& value){
        start = allocate_and_fill(n, value);
        finish = start + n;
        end_of_storage = finish;
    }

    iterator allocate_and_fill(size_type n, const T& x){
        iterator result = data_allocator::allocate(n);
        uninitialized_fill_n(result, n, x);
        return result;
    }

    void destroy(iterator first, iterator last){
        for(iterator cur = first; cur != last; ++cur){
            data_allocator::destroy(cur);
        }
    }

    void destroy(iterator position){
        data_allocator::destroy(position);
    }

    void construct(iterator position, const T& x){
        data_allocator::construct(position, x);
    }

public:
    iterator begin(){
        return start;
    }

    iterator end(){
        return finish;
    }

    const_iterator begin() const {
        return start;
    }

    const_iterator end() const {
        return finish;
    }


    size_type size() const {
        return size_type(finish - start);
    }

    size_type capacity() const {
        return size_type(end_of_storage - begin());
    }

    bool empty() const {
        return begin() == end();
    }

    reference operator[](size_type n){
        return *(begin() + n);
    }

    const_reference operator[](size_type n) const {
        return *(begin() + n);
    }

    vector(): start(nullptr), finish(nullptr), end_of_storage(nullptr) {}
    vector(size_type n, const T& value){
        fill_initialize(n, value);
    }
    vector(int n, const T& value){
        fill_initialize(n, value);
    }
    vector(long n, const T& value){
        fill_initialize(n, value);
    }
    explicit vector(size_type n){
        fill_initialize(n, T());
    }
    ~vector(){
        destroy(start, finish);
        deallocate();
    }

    reference front(){
        return *begin();
    }

    const_reference front() const {
        return *begin();
    }

    reference back(){
        return *(end() - 1);
    }

    void push_back(const T& x){
        if(finish != end_of_storage){
            construct(finish, x);
            ++finish;
        }else{
            insert_aux(end(), x);
        }
    }

    void reserve(size_type n){
        if(capacity() < n){
            const size_type old_size = size();
            iterator tmp = allocate_and_fill(n, T());
            uninitialized_copy(start, finish, tmp);
            destroy(start, finish);
            deallocate();
            start = tmp;
            finish = tmp + old_size;
            end_of_storage = start + n;
        }
    }

    void pop_back(){
        --finish;
        destroy(finish);
    }

    iterator erase(iterator position){
        if(position + 1 != end()){
            copy(position + 1, finish, position);
        }
        --finish;
        destroy(finish);
        return position;
    }

    iterator erase(iterator first, iterator last){
        iterator i = copy(last, finish, first);
        destroy(i, finish);
        finish = finish - (last - first);
        return first;
    }

    void resize(size_type new_size, const T& x){
        if(new_size < size()){
            erase(begin() + new_size, end());
        }else{
            insert(end(), new_size - size(), x);
        }
    }

    void resize(size_type new_size){
        resize(new_size, T());
    }

    void clear(){
        erase(begin(), end());
    }

    void insert(iterator position, size_type n, const T& x);

    void swap(vector<T, Alloc>& x){
        std::swap(start, x.start);
        std::swap(finish, x.finish);
        std::swap(end_of_storage, x.end_of_storage);
    }

};


// insert_aux函数
template <typename T, typename Alloc>
void vector<T, Alloc>::insert_aux(iterator position, const T& x){
    if(finish != end_of_storage){
        // 分配的空间还有剩余，还可以在备用空间中构造一个元素

        // 在备用空间起始位置构建一个元素
        construct(finish, *(finish-1));
        ++finish;
        T x_copy = x;
        // 将position到finish-2的元素往后移动一个位置
        std::copy_backward(position, finish-2,finish-1);
        *position = x_copy;
    }
    else{
        const size_type old_size = size();
        const size_type len = old_size!=0 ? 2*old_size: 1;

        iterator new_start = data_allocator::allocate(len);
        iterator new_finish = new_start;

        try{
            // 将原来的vector 内容拷贝到新的vector当中
            new_finish = uninitialized_copy(start, position,new_start);

            construct(new_finish , x);
            ++new_finish;
            // 将安插点点原内容也拷贝过来
            new_finish = uninitialized_copy(position, finish, new_finish); 
        }
        catch(...){
            // 如果没有分配成功，或者当中出现了失败，将分配的之间的全部销毁掉然后回收内存
            destroy(new_start, new_finish);
            data_allocator::deallocate(new_start, len);
            throw;
        }

        // 确保没有问题之后开始对于老的vector的销毁工作
        destroy(begin(), end());
        deallocate();

        // 让迭代器指向新的内存当中的位置
        start = new_start;
        finish = new_finish;
        end_of_storage = new_start + len;
    }
}

template <class T, class Alloc>
void vector<T,Alloc> :: insert(iterator position, size_type n, const T& x){
    if(n != 0){
        if(size_type(end_of_storage - finish) >= n){
            // 备用空间的大小足够
            T x_copy = x;

            // 计算现在的插入点之后的元素有哪些
            const size_type elems_after = finish - position;
            iterator old_finish = finish;

            if(elems_after > n){
                // 插入点之后点现有的元素个数 大于 新增的元素个数
                uninitialized_copy(finish-n, finish, finish);
                finish += n;
                copy_backward(position, old_finish -n ,old_finish);
                fill(position, position+n, x_copy);
            }
            else {
                // 插入点之后点元素个数 小于 新增的元素的个数

                // 先插入进去，补足，让后面插入的元素和新增的元素相等
                uninitialized_fill_n(finish, n-elems_after, x_copy);
                finish += n-elems_after;
                uninitialized_copy(position, old_finish, finish);
                finish += elems_after;
                fill(position, old_finish, x_copy);
            }
        }
        else {
            // 备用空间的大小不够用了
            // 首先决定新的长度
            const size_type old_size = size();
            const size_type len = old_size + fmax(old_size, n);

            // 分配新的内存
            iterator new_start = data_allocator::allocate(len);
            iterator new_finish = new_start;

            try{
                // 将原来的vector 内容拷贝到新的vector当中
                new_finish = uninitialized_copy(start, position,new_start);

                new_finish = uninitialized_fill_n(new_finish, n, x);
                new_finish = uninitialized_copy(position, finish, new_finish);
            }
            catch(...){
                // 如果没有分配成功，或者当中出现了失败，将分配的之间的全部销毁掉然后回收内存
                destroy(new_start, new_finish);
                data_allocator::deallocate(new_start, len);
                throw;
            }

            // 确保没有问题之后开始对于老的vector的销毁工作
            destroy(begin(), end());
            deallocate();

            // 让迭代器指向新的内存当中的位置
            start = new_start;
            finish = new_finish;
            end_of_storage = new_start + len;
        }
    }

}


__JIANQIAO_END__

#endif // __JIANQIAO_VECTOR_HPP__