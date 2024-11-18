//
// Created by Mac on 24-11-8.
//

#ifndef JIANQIAOSTL_JIANQIAO_ALGORITHM_HPP
#define JIANQIAOSTL_JIANQIAO_ALGORITHM_HPP

#include <iterator>
#include "config.hpp"
#include "jianqiao_iterator.hpp"
#include "type_traits.hpp"
#include "jianqiao_pair.hpp"
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

template <typename T>
struct less{
    bool operator()(const T& a, const T& b){
        return a < b;
    }
};

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





__JIANQIAO_END__
#endif //JIANQIAOSTL_JIANQIAO_ALGORITHM_HPP
