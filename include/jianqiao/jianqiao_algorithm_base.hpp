//
// Created by Mac on 24-11-8.
//

#ifndef JIANQIAOSTL_JIANQIAO_ALGORITHM_BASE_HPP
#define JIANQIAOSTL_JIANQIAO_ALGORITHM_BASE_HPP

#include <iterator>
#include "config.hpp"
#include "jianqiao_iterator.hpp"
#include "type_traits.hpp"
#include "jianqiao_pair.hpp"
#include "heap_base.hpp"
#include "jianqiao_function.hpp"

__JIANQIAO_BEGIN__

// swap
template <class T>
void swap(T& a, T& b){
    T tmp = a;
    a = b;
    b = tmp;
}

// equal
template <class InputIterator1, class InputIterator2>
bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2){
    for(; first1 != last1; ++first1, ++first2){
        if(*first1 != *first2){
            return false;
        }
    }
    return true;
}

template <class InputIterator1, class InputIterator2, class BinaryPredicate>
bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate binary_pred){
    // 指定判断相等的操作
    for(; first1 != last1; ++first1, ++first2){
        if(!binary_pred(*first1, *first2)){
            return false;
        }
    }
    return true;
}

//fill
template <class ForwardIterator, class T>
void fill(ForwardIterator first, ForwardIterator last, const T& value){
    for(; first != last; ++first){
        *first = value;
    }
}

// fill_n
template <class OutputIterator, class Size, class T>
OutputIterator fill_n(OutputIterator first, Size n, const T& value){
    for(; n > 0; --n, ++first){
        *first = value;
    }
    return first;
}

// iter_swap
template <class ForwardIterator1, class ForwardIterator2, class T>
void __iter_swap(ForwardIterator1 a, ForwardIterator2 b, T*);

template <class ForwardIterator1, class ForwardIterator2>
void iter_swap(ForwardIterator1 a, ForwardIterator2 b){
    __iter_swap(a, b, value_type(a));
}

template <class ForwardIterator1, class ForwardIterator2, class T>
void __iter_swap(ForwardIterator1 a, ForwardIterator2 b, T*){
    T tmp = *a;
    *a = *b;
    *b = tmp;
}


// lexicographical_compare
// 用字典序比较两个序列
template <class InputIterator1, class InputIterator2>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2){
    for(; first1 != last1 && first2 != last2; ++first1, ++first2){
        if(*first1 < *first2){
            return true;
        }
        if(*first2 < *first1){
            return false;
        }
    }
    return first1 == last1 && first2 != last2;
}

template <class InputIterator1, class InputIterator2, class Compare>
bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp){
    for(; first1 != last1 && first2 != last2; ++first1, ++first2){
        if(comp(*first1, *first2)){
            return true;
        }
        if(comp(*first2, *first1)){
            return false;
        }
    }
    return first1 == last1 && first2 != last2;
}

// max
template <class T>
inline const T& max(const T& a, const T& b){
    return a < b ? b : a;
}

template <class T, class Compare>
inline const T& max(const T& a, const T& b, Compare comp){
    return comp(a, b) ? b : a;
}

// min
template <class T>
inline const T& min(const T&a, const T&b){
    return a<b ? a:b;
}

template <class T, class Compare>
inline const T& min(const T& a, const T& b, Compare comp){
    return comp(a, b) ? a : b;
}

// mismatch
// 比较两个序列，返回第一个不匹配的位置
template <class InputIterator1, class InputIterator2>
pair<InputIterator1, InputIterator2> mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2){
    while(first1 != last1 && *first1 == *first2){
        ++first1;
        ++first2;
    }
    return pair<InputIterator1, InputIterator2>(first1, first2);
}

template <class InputIterator1, class InputIterator2, class BinaryPredicate>
pair<InputIterator1, InputIterator2> mismatch(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate binary_pred){
    while(first1 != last1 && binary_pred(*first1, *first2)){
        ++first1;
        ++first2;
    }
    return pair<InputIterator1, InputIterator2>(first1, first2);
}

template <class InputIterator1, class InputIterator2> struct __copy_dispatch;

// copy

// 一系列后面会用到的前向声明
template <class InputIterator, class OutputIterator>
OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator result, input_iterator_tag);

template <class InputIterator, class OutputIterator>
OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator result, std::input_iterator_tag);

template <class RandomAccessIterator, class OutputIterator>
OutputIterator __copy(RandomAccessIterator first, RandomAccessIterator last, OutputIterator result, random_access_iterator_tag);

template <class RandomAccessIterator, class OutputIterator>
OutputIterator __copy(RandomAccessIterator first, RandomAccessIterator last, OutputIterator result, std::random_access_iterator_tag);

template <class InputIterator, class OutputIterator>
inline OutputIterator copy(InputIterator first, InputIterator last, OutputIterator result){
    return __copy_dispatch<InputIterator, OutputIterator>()(first, last, result);
}

// 特化版本1
inline char* copy(const char* first, const char* last, char* result){
    memmove(result, first, last - first);
    return result + (last - first);
}

// 特化版本2
inline wchar_t* copy(const wchar_t* first, const wchar_t* last, wchar_t* result){
    memmove(result, first, sizeof(wchar_t) * (last - first));
    return result + (last - first);
}



// 完全泛化版本的copy_dispatch
template <class InputIterator, class OutputIterator>
struct __copy_dispatch{
    OutputIterator operator()(InputIterator first, InputIterator last, OutputIterator result){
        return __copy(first, last, result, iterator_category(first));
    }
};

// __copy 的 InputIterator 版本
template <class InputIterator, class OutputIterator>
inline OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator result, input_iterator_tag){
    for(; first != last; ++first, ++result){
        *result = *first;
    }
    return result;
}

    template <class InputIterator, class OutputIterator>
    inline OutputIterator __copy(InputIterator first, InputIterator last, OutputIterator result, std::input_iterator_tag){
        for(; first != last; ++first, ++result){
            *result = *first;
        }
        return result;
    }

// __copy 的 RandomAccessIterator 版本
template <class RandomAccessIterator, class OutputIterator>
inline OutputIterator __copy(RandomAccessIterator first, RandomAccessIterator last, OutputIterator result, random_access_iterator_tag){
    return __copy_d(first, last, result, distance_type(first));
}

    template <class RandomAccessIterator, class OutputIterator, class Distance>
    inline OutputIterator __copy_d(RandomAccessIterator first, RandomAccessIterator last, OutputIterator result, Distance*);

// 适配std版本的 random_access_iterator
template <class RandomAccessIterator, class OutputIterator>
inline OutputIterator __copy(RandomAccessIterator first, RandomAccessIterator last, OutputIterator result, std::random_access_iterator_tag){
        return __copy_d(first, last, result, distance_type(first));
}

// __copy_d
template <class RandomAccessIterator, class OutputIterator, class Distance>
inline OutputIterator __copy_d(RandomAccessIterator first, RandomAccessIterator last, OutputIterator result, Distance*){
    for(Distance n = last - first; n > 0; --n, ++first, ++result){
        *result = *first;
    }
    return result;
}

// 两个都是指针T*的情况
template <class T>
struct __copy_dispatch<T*, T*>{
    T* operator()(T* first, T* last, T* result){
        typedef typename __type_traits<T>::has_trivial_assignment_operator t;
        return __copy_t(first, last, result, t());
    }
};

// 第一个参数为const T*, 第二个参数为T*的情况
template <class T>
struct __copy_dispatch<const T*, T*>{
    T* operator()(const T* first, const T* last, T* result){
        typedef typename __type_traits<T>::has_trivial_assignment_operator t;
        return __copy_t(first, last, result, t());
    }
};



//指针所指对象具备trivial assignment operator
template <class T>
inline T* __copy_t(const T* first, const T* last, T* result, __true_type){
    // 如果指针所指对象具备trivial assignment operator，直接调用memmove
    memmove(result, first, sizeof(T) * (last - first));
    return result + (last - first);
}

// 指针所指对象不具备trivial assignment operator
template <class T>
inline T* __copy_t(const T* first, const T* last, T* result, __false_type){
    // 逐个赋值
    return __copy_d(first, last, result, (ptrdiff_t*)0);
}


// set 相关算法

// set_union：并集操作
template <class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator set_union(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result){
    // 类似于链表合并的操作
    while(first1 != last1 && first2 != last2){
        if(*first1 < *first2){
            *result = *first1;
            ++first1;
        }else if(*first2 < *first1){
            *result = *first2;
            ++first2;
        }else{
            *result = *first1;
            ++first1;
            ++first2;
        }
        ++result;
    }
    return Jianqiao::copy(first2, last2, Jianqiao::copy(first1, last1, result));
}

// 使用自定义的比较方法版本
template <class InputIterator1, class InputIterator2, class OutputIterator, class Compare>
OutputIterator set_union(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result ,Compare comp){
    while(first1 != last1 && first2 != last2){
        if(comp(*first1, *first2)){
            *result = *first1;
            ++first1;
        }
        else if(comp(*first2, *first1)){
            *result = *first2;
            ++first2;
        }else{
            *result = *first1;
            ++first1;
            ++first2;
        }

        ++result;
    }
    return copy(first2, last2, copy(first1, last1, result));
}

// set_intersection：交集操作
template <class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator set_intersection(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result){
    while(first1 != last1 && first2 != last2){
        if(*first1 < *first2){
            ++first1;
        }else if(*first2 < *first1){
            ++first2;
        }else{
            *result = *first1;
            ++first1;
            ++first2;
            ++result;
        }
    }
    return result;
}

// 使用自定义的比较方法版本
template <class InputIterator1, class InputIterator2, class OutputIterator, class Compare>
OutputIterator set_intersection(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result, Compare comp){
    while(first1 != last1 && first2 != last2){
        if(comp(*first1, *first2)){
            ++first1;
        }else if(comp(*first2, *first1)){
            ++first2;
        }else{
            *result = *first1;
            ++first1;
            ++first2;
            ++result;
        }
    }
    return result;
}

// set_difference：差集操作
template <class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator set_difference(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result){
    while(first1 != last1 && first2 != last2){
        if(*first1 < *first2){
            *result = *first1;
            ++first1;
            ++result;
        }else if(*first2 < *first1){
            ++first2;
        }else{
            ++first1;
            ++first2;
        }
    }
    return Jianqiao::copy(first1, last1, result);
}

// 使用自定义的比较方法版本
template <class InputIterator1, class InputIterator2, class OutputIterator, class Compare>
OutputIterator set_difference(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result, Compare comp){
    while(first1 != last1 && first2 != last2){
        if(comp(*first1, *first2)){
            *result = *first1;
            ++first1;
            ++result;
        }else if(comp(*first2, *first1)){
            ++first2;
        }else{
            ++first1;
            ++first2;
        }
    }
    return copy(first1, last1, result);
}


// set_symmetric_difference：对称差集操作, 即两个集合的并集减去交集
    template <class InputIterator1, class InputIterator2, class OutputIterator>
    OutputIterator set_symmetric_difference(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result){
        while(first1 != last1 && first2 != last2){
            if(*first1 < *first2){
                *result = *first1;
                ++first1;
                ++result;
            }else if(*first2 < *first1){
                *result = *first2;
                ++first2;
                ++result;
            }else{
                ++first1;
                ++first2;
            }
        }
        return Jianqiao::copy(first2, last2, Jianqiao::copy(first1, last1, result));
    }

    // 使用自定义的比较方法版本
    template <class InputIterator1, class InputIterator2, class OutputIterator, class Compare>
    OutputIterator set_symmetric_difference(InputIterator1 first1, InputIterator1 last1,
                                            InputIterator2 first2, InputIterator2 last2, OutputIterator result, Compare comp){
        while(first1 != last1 && first2 != last2){
            if(comp(*first1, *first2)){
                *result = *first1;
                ++first1;
                ++result;
            }else if(comp(*first2, *first1)){
                *result = *first2;
                ++first2;
                ++result;
            }else{
                ++first1;
                ++first2;
            }
        }

        return copy(first1, last1, result);
    }

// adjacent_find
template <class ForwardIterator>
ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last){
    if(first == last){
        return last;
    }
    ForwardIterator next = first;
    while(++next != last){
        if(*first == *next){
            return first;
        }
        first = next;
    }
    return last;
}

template <class ForwardIterator, class BinaryPredicate>
ForwardIterator adjacent_find(ForwardIterator first, ForwardIterator last, BinaryPredicate binary_pred){
    if(first == last){
        return last;
    }
    ForwardIterator next = first;
    while(++next != last){
        if(binary_pred(*first, *next)){
            return first;
        }
        first = next;
    }
    return last;
}

// count
template <class InputIterator, class T>
typename iterator_traits<InputIterator>::difference_type count(InputIterator first, InputIterator last, const T& value){
    typename iterator_traits<InputIterator>::difference_type n = 0;
    for(; first != last; ++first){
        if(*first == value){
            ++n;
        }
    }
    return n;
}

// 自定义比较函数的count
template <class InputIterator, class Predicate>
typename iterator_traits<InputIterator>::difference_type count(InputIterator first, InputIterator last, Predicate pred){
    typename iterator_traits<InputIterator>::difference_type n = 0;
    for(; first != last; ++first){
        if(pred(*first)){
            ++n;
        }
    }
    return n;
}


// count_if
template <class InputIterator, class Predicate>
typename iterator_traits<InputIterator>::difference_type count_if(InputIterator first, InputIterator last, Predicate pred){
    typename iterator_traits<InputIterator>::difference_type n = 0;
    for(; first != last; ++first){
        if(pred(*first)){
            ++n;
        }
    }
    return n;
}

// count_if == 版本
template <class InputIterator, class T>
typename iterator_traits<InputIterator>::difference_type count_if(InputIterator first, InputIterator last, const T& value){
    typename iterator_traits<InputIterator>::difference_type n = 0;
    for(; first != last; ++first){
        if(*first == value){
            ++n;
        }
    }
    return n;
}

// find
template <class InputIterator, class T>
InputIterator find(InputIterator first, InputIterator last, const T& value){
    while(first != last && *first != value){
        ++first;
    }
    return first;
}

// find_if
template <class InputIterator, class Predicate>
InputIterator find_if(InputIterator first, InputIterator last, Predicate pred){
    while(first != last && !pred(*first)){
        ++first;
    }
    return first;
}

// find_end
template <class ForwardIterator1, class ForwardIterator2>
ForwardIterator1 __find_end(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2, forward_iterator_tag, forward_iterator_tag);

template <class ForwardIterator1, class ForwardIterator2, class BinaryPredicate>
ForwardIterator1 __find_end(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2, BinaryPredicate pred, forward_iterator_tag, forward_iterator_tag);


template <class ForwardIterator1, class ForwardIterator2>
inline ForwardIterator1 find_end(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2){
    using category1 = typename iterator_traits<ForwardIterator1>::iterator_category;
    using category2 = typename iterator_traits<ForwardIterator2>::iterator_category;

    return __find_end(first1, last1, first2, last2, category1(), category2());
}

template <class ForwardIterator1, class ForwardIterator2, class BinaryPredicate>
inline ForwardIterator1 find_end(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2, BinaryPredicate pred){
    using category1 = typename iterator_traits<ForwardIterator1>::iterator_category;
    using category2 = typename iterator_traits<ForwardIterator2>::iterator_category;

    return __find_end(first1, last1, first2, last2, pred, category1(), category2());
}

// __find_end
template <class ForwardIterator1, class ForwardIterator2>
ForwardIterator1 __find_end(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2, forward_iterator_tag, forward_iterator_tag){
    if(first2 == last2){
        return last1;
    }else{
        ForwardIterator1 result = last1;
        while(true){
            ForwardIterator1 new_result = search(first1, last1, first2, last2);
            if(new_result == last1){
                return result;
            }else{
                result = new_result;
                first1 = new_result;
                ++first1;
            }
        }
    }
}

template <class ForwardIterator1, class ForwardIterator2, class BinaryPredicate>
ForwardIterator1 __find_end(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2, BinaryPredicate pred, forward_iterator_tag, forward_iterator_tag){
    if(first2 == last2){
        return last1;
    }else{
        ForwardIterator1 result = last1;
        while(true){
            ForwardIterator1 new_result = search(first1, last1, first2, last2, pred);
            if(new_result == last1){
                return result;
            }else{
                result = new_result;
                first1 = new_result;
                ++first1;
            }
        }
    }
}

// find_first_of
template <class InputIterator, class ForwardIterator>
InputIterator find_first_of(InputIterator first1, InputIterator last1, ForwardIterator first2, ForwardIterator last2){

    for(; first1 != last1; ++first1){
        for(ForwardIterator iter = first2; iter != last2; ++iter){
            if(*first1 == *iter){
                return first1;
            }
        }
    }
    return last1;
}

template <class InputIterator, class ForwardIterator, class BinaryPredicate>
InputIterator find_first_of(InputIterator first1, InputIterator last1, ForwardIterator first2, ForwardIterator last2, BinaryPredicate pred){
    for(; first1 != last1; ++first1){
        for(ForwardIterator iter = first2; iter != last2; ++iter){
            if(pred(*first1, *iter)){
                return first1;
            }
        }
    }
    return last1;
}

// for_each
template <class InputIterator, class Function>
Function for_each(InputIterator first, InputIterator last, Function f){
    for(; first != last; ++first){
        f(*first);
    }
    return f;
}

// search: 在序列1中查找序列2, 使用的不是kmp算法
template <class ForwardIterator1, class ForwardIterator2>
ForwardIterator1 search(ForwardIterator1 first1, ForwardIterator1 last1, ForwardIterator2 first2, ForwardIterator2 last2){
    if(first2 == last2){
        return first1;
    }
    while(first1 != last1){
        ForwardIterator1 iter1 = first1;
        ForwardIterator2 iter2 = first2;
        while(*iter1 == *iter2){
            ++iter1;
            ++iter2;
            if(iter2 == last2){
                return first1;
            }
            if(iter1 == last1){
                return last1;
            }
        }
        ++first1;
    }
    return last1;
}

// generate
template <class ForwardIterator, class Generator>
void generate(ForwardIterator first, ForwardIterator last, Generator gen){
    for(; first != last; ++first){
        *first = gen();
    }
}

// generate_n
template <class OutputIterator, class Size, class Generator>
OutputIterator generate_n(OutputIterator first, Size n, Generator gen){
    for(; n > 0; --n, ++first){
        *first = gen();
    }
    return first;
}

// max_element
template <class ForwardIterator>
ForwardIterator max_element(ForwardIterator first, ForwardIterator last){
    if(first == last){
        return first;
    }
    ForwardIterator result = first;
    while(++first != last){
        if(*result < *first){
            result = first;
        }
    }
    return result;
}

template <class ForwardIterator, class Compare>
ForwardIterator max_element(ForwardIterator first, ForwardIterator last, Compare comp){
    if(first == last){
        return first;
    }
    ForwardIterator result = first;
    while(++first != last){
        if(comp(*result, *first)){
            result = first;
        }
    }
    return result;
}

// min_element
template <class ForwardIterator>
ForwardIterator min_element(ForwardIterator first, ForwardIterator last){
    if(first == last){
        return first;
    }
    ForwardIterator result = first;
    while(++first != last){
        if(*first < *result){
            result = first;
        }
    }
    return result;
}

template <class ForwardIterator, class Compare>
ForwardIterator min_element(ForwardIterator first, ForwardIterator last, Compare comp){
    if(first == last){
        return first;
    }
    ForwardIterator result = first;
    while(++first != last){
        if(comp(*first, *result)){
            result = first;
        }
    }
    return result;
}

// merge
template <class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator merge(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result){
    while(first1 != last1 && first2 != last2){
        if(*first2 < *first1){
            *result = *first2;
            ++first2;
        }else{
            *result = *first1;
            ++first1;
        }
        ++result;
    }
    return Jianqiao::copy(first2, last2, Jianqiao::copy(first1, last1, result));
}

template <class InputIterator1, class InputIterator2, class OutputIterator, class Compare>
OutputIterator merge(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, OutputIterator result, Compare comp){
    while(first1 != last1 && first2 != last2){
        if(comp(*first2, *first1)){
            *result = *first2;
            ++first2;
        }else{
            *result = *first1;
            ++first1;
        }
        ++result;
    }
    return Jianqiao::copy(first2, last2, Jianqiao::copy(first1, last1, result));
}

// remove

template <class InputIterator, class OutputIterator, class T>
OutputIterator remove_copy(InputIterator first, InputIterator last, OutputIterator result, const T& value);
template <class InputIterator, class OutputIterator, class Predicate>
OutputIterator remove_copy_if(InputIterator first, InputIterator last, OutputIterator result, Predicate pred);

template <class ForwardIterator, class T>
ForwardIterator remove(ForwardIterator first, ForwardIterator last, const T& value){
    // 找到第一个等于value的元素
    first = Jianqiao::find(first, last, value);

    // 第一个不是value的元素
    ForwardIterator next = first;

    // 递归，将后面不等于的像前面移动了
    return first == last ? first : Jianqiao::remove_copy(++next, last, first, value);
}

// remove_if
template <class ForwardIterator, class Predicate>
ForwardIterator remove_if(ForwardIterator first, ForwardIterator last, Predicate pred){
    first = Jianqiao::find_if(first, last, pred);
    ForwardIterator next = first;
    return first == last ? first : Jianqiao::remove_copy_if(++next, last, first, pred);
}

// remove_copy: 将[first, last)中不等于value的元素拷贝到result中
template <class InputIterator, class OutputIterator, class T>
OutputIterator remove_copy(InputIterator first, InputIterator last, OutputIterator result, const T& value){
    for(; first != last; ++first){
        if(*first != value){
            *result = *first;
            ++result;
        }
    }
    return result;
}

// remove_copy_if: 将[first, last)中不满足pred的元素拷贝到result中
template <class InputIterator, class OutputIterator, class Predicate>
OutputIterator remove_copy_if(InputIterator first, InputIterator last, OutputIterator result, Predicate pred){
    for(; first != last; ++first){
        if(!pred(*first)){
            *result = *first;
            ++result;
        }
    }
    return result;
}

// replace: 将[first, last) 之间所有等于old_value的元素替换为new_value
template <class ForwardIterator, class T>
void replace(ForwardIterator first, ForwardIterator last, const T& old_value, const T& new_value){
    for(; first != last; ++first){
        if(*first == old_value){
            *first = new_value;
        }
    }
}

// replace_if: 将[first, last) 之间所有满足pred的元素替换为new_value
template <class ForwardIterator, class Predicate, class T>
void replace_if(ForwardIterator first, ForwardIterator last, Predicate pred, const T& new_value){
    for(; first != last; first++){
        if(pred(*first)){
            *first = new_value;
        }
    }
}

// replace_copy: 将[first, last) 之间所有等于old_value的元素替换为new_value, 并拷贝到result中
template <class InputIterator, class OutputIterator, class T>
OutputIterator replace_copy(InputIterator first, InputIterator last, OutputIterator result, const T& old_value, const T& new_value){
    for(; first != last; ++first, ++result){
        *result = *first == old_value ? new_value : *first;
    }
    return result;
}

// replace_copy_if: 将[first, last) 之间所有满足pred的元素替换为new_value, 并拷贝到result中
template <class InputIterator, class OutputIterator, class Predicate, class T>
OutputIterator replace_copy_if(InputIterator first, InputIterator last, OutputIterator result, Predicate pred, const T& new_value){
    for(; first != last; ++first, ++result){
        *result = pred(*first) ? new_value : *first;
    }
    return result;
}

// reverse
template <class BidirectionalIterator>
void reverse(BidirectionalIterator first, BidirectionalIterator last){
    while(true){
        if(first == last || first == --last){
            // 在比较的同时完成了对于last的移动，写的非常简洁
            return;
        }else{
            Jianqiao::iter_swap(first++, last);
        }
    }
}

// reverse_copy
template <class BidirectionalIterator, class OutputIterator>
OutputIterator reverse_copy(BidirectionalIterator first, BidirectionalIterator last, OutputIterator result){
    while(first != last){
        --last;
        *result = *last;
        ++result;
    }
    return result;
}

// rotate
template <class ForwardIterator, class Distance>
void __rotate(ForwardIterator first, ForwardIterator middle, ForwardIterator last, Distance*, forward_iterator_tag){
    for(ForwardIterator i = middle; ;){
        Jianqiao::iter_swap(first, i);
        ++first;
        ++i;
        if(first == middle){
            if(i == last){
                return;
            }
            middle = i;
        }else if(i == last){
            i = middle;
        }
    }
}

template <class BidirectionalIterator, class Distance>
void __rotate(BidirectionalIterator first, BidirectionalIterator middle, BidirectionalIterator last, Distance*, bidirectional_iterator_tag){
    Jianqiao::reverse(first, middle);
    Jianqiao::reverse(middle, last);
    Jianqiao::reverse(first, last);
}

    template <class ForwardIterator, class Distance>
    void __rotate(ForwardIterator first, ForwardIterator middle, ForwardIterator last, Distance*, std::forward_iterator_tag){
        for(ForwardIterator i = middle; ;){
            Jianqiao::iter_swap(first, i);
            ++first;
            ++i;
            if(first == middle){
                if(i == last){
                    return;
                }
                middle = i;
            }else if(i == last){
                i = middle;
            }
        }
    }

    template <class BidirectionalIterator, class Distance>
    void __rotate(BidirectionalIterator first, BidirectionalIterator middle, BidirectionalIterator last, Distance*, std::bidirectional_iterator_tag){
        Jianqiao::reverse(first, middle);
        Jianqiao::reverse(middle, last);
        Jianqiao::reverse(first, last);
    }




template <class ForwardIterator>
inline void rotate(ForwardIterator first, ForwardIterator middle, ForwardIterator last){
    if(first == middle || middle == last){
        return;
    }
    __rotate(first, middle, last, distance_type(first), iterator_category(first));
}

// rotate_copy
template <class ForwardIterator, class OutputIterator>
OutputIterator rotate_copy(ForwardIterator first, ForwardIterator middle, ForwardIterator last, OutputIterator result){
    // 先把后面部分的拷贝到前面的部分，再把前面的部分拷贝到后面，使用了递归的写法
    return Jianqiao::copy(first, middle, Jianqiao::copy(middle, last, result));
}



// partition
// 为实现快速排序做准备的partition操作
template <class BidirectionalIterator, class Predicate>
BidirectionalIterator partition(BidirectionalIterator first , BidirectionalIterator last, Predicate pred){
    while(true){
        while(true){
            if(first == last){
                return first;
            }else if(pred(*first)){
                ++first;
            }else{
                break;
            }
        }
        --last;
        while(true){
            if(first == last){
                return first;
            }else if(!pred(*last)){
                --last;
            }else{
                break;
            }
        }
        Jianqiao::iter_swap(first, last);
        ++first;
    }
}

// unique

    // 相关declaration
    template <class InputIterator, class OutputIterator>
    OutputIterator unique_copy(InputIterator first, InputIterator last, OutputIterator result);

template <class ForwardIterator>
ForwardIterator unique(ForwardIterator first, ForwardIterator last){
    first = Jianqiao::adjacent_find(first, last);
    return Jianqiao::unique_copy(first, last, first);
}

// unique_copy
    template <class InputIterator, class OutputIterator>
    OutputIterator __unique_copy(InputIterator first, InputIterator last, OutputIterator result, input_iterator_tag);

    template <class InputIterator, class OutputIterator>
    inline OutputIterator __unique_copy(InputIterator first, InputIterator last, OutputIterator result, std::input_iterator_tag);

template <class InputIterator, class OutputIterator>
OutputIterator unique_copy(InputIterator first, InputIterator last, OutputIterator result){
    if(first == last){
        return result;
    }
    return __unique_copy(first, last, result, iterator_category(first));
}

template <class InputIterator, class OutputIterator>
inline OutputIterator __unique_copy(InputIterator first, InputIterator last, OutputIterator result, input_iterator_tag){
    return __unique_copy_inputiterator(first, last, result);
}

    template <class InputIterator, class OutputIterator>
    inline OutputIterator __unique_copy(InputIterator first, InputIterator last, OutputIterator result, std::input_iterator_tag){
        return __unique_copy_inputiterator(first, last, result);
    }

    template <class InputIterator, class OutputIterator>
    OutputIterator __unique_copy_inputiterator(InputIterator first, InputIterator last, OutputIterator result){
        *result = *first;
        while(++first != last){
            if(*result != *first){
                *++result = *first;
            }
        }
        return ++result;
    }


    // copy_backward
    template <class BidirectionalIterator1, class BidirectionalIterator2>
    BidirectionalIterator2 copy_backward(BidirectionalIterator1 first, BidirectionalIterator1 last, BidirectionalIterator2 result){
        while(first != last){
            *--result = *--last;
        }
        return result;
    }

    // uninitialized_copy
    template <class InputIterator, class ForwardIterator>
    ForwardIterator uninitialized_copy(InputIterator first, InputIterator last, ForwardIterator result){
        ForwardIterator cur = result;
        try{
            for(; first != last; ++first, ++cur){
                construct(&*cur, *first);
            }
            return cur;
        }catch(...){
            destroy(result, cur);
            throw;
        }
    }




__JIANQIAO_END__
#endif //JIANQIAOSTL_JIANQIAO_ALGORITHM_BASE_HPP
