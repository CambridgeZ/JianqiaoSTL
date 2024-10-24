//file jianqiao/alloc.hpp

#ifndef __JIANQIAO_ALLOC_HPP__
#define __JIANQIAO_ALLOC_HPP__



#include "config.hpp"

#include <new>
#include <cstdlib>
#include <cstddef>
#include <climits>
#include <iostream>
#include "config.hpp"

#if USE_JIANQIAO_ALLOC

namespace Jianqiao{
    template <class T>
    inline T* _allocate(ptrdiff_t size, T*){
        // set_new_handler 函数是一个库函数，用来设置一个函数指针，当new操作失败时，系统会调用这个函数指针指向的函数    
        std::set_new_handler(0);
        T* tmp = (T*)(::operator new((size_t)(size * sizeof(T))));
        if(tmp == 0){
            std::cerr << "out of memory" << std::endl;
            exit(1);
        }

        return tmp;
    }

    template <class T>
    inline void _deallocate(T* buffer){
        ::operator delete(buffer);
    }

    template <class T1, class T2>
    inline void _construct(T1 *p, const T2& value){
        new(p) T1(value);// 用value 构造一个T1类型的独享
    }

    template <class T>
    inline void _destroy(T* ptr){
        ptr->~T();
    }    

    /**************************封装上面函数，并提供一个可用的全局函数***********************/
#ifdef JIANQIAO_SELF_MEMORY_CONTROL
    template <class T>
    inline T* allocate(ptrdiff_t size, T*){
        return _allocate(size, (T*)0);
    }

    template <class T>
    inline void deallocate(T* buffer){
        _deallocate(buffer);
    }

    template <class T1, class T2>
    inline void construct(T1 *p, const T2& value){
        _construct(p, value);
    }

    template <class T>
    inline void destroy(T* ptr){
        _destroy(ptr);
    }

    template <class T>
    inline void destroy(T* first, T* last){
        for(; first < last; ++first){
            destroy(first);
        }
    }
#endif // JIANQIAO_SELF_MEMORY_CONTROL
    /********************************************************************************/
    // template <class T>
    // class allocator{
    // public:
    //     typedef T value_type;
    //     typedef T* pointer;
    //     typedef const T* const_pointer;
    //     typedef T& reference;
    //     typedef const T& const_reference;
    //     typedef size_t size_type;   
    //     typedef ptrdiff_t difference_type;

    //     // 重新绑定内存分配器
    //     template <class U>
    //     struct rebind{
    //         typedef allocator<U> other;
    //     };

    //     // hint 用于指定内存分配器的行为，但是这个参数在C++标准中并没有明确规定
    //     static pointer allocate(size_type n, const void* hint = 0){
    //         return _allocate((difference_type)n, (pointer)0);
    //     }

    //     static void deallocate(pointer p, size_type n){
    //         _deallocate(p);
    //     }

    //     // 构造函数
    //     static void construct(pointer p, const T& value){
    //         _construct(p, value);
    //     }

    //     static void destroy(pointer p){
    //         _destroy(p);
    //     }

    //     pointer address(reference x){
    //         return (pointer)&x;
    //     }

    //     const_pointer const_address(const_reference x){
    //         return (const_pointer)&x;
    //     }
    // };

    template <class T>
    class allocator {
    public:
        typedef T value_type;
        typedef T* pointer;
        typedef const T* const_pointer;
        typedef T& reference;
        typedef const T& const_reference;
        typedef size_t size_type;
        typedef ptrdiff_t difference_type;

        // 重新绑定内存分配器
        template <class U>
        struct rebind {
            typedef allocator<U> other;
        };

        // hint 用于指定内存分配器的行为，但是这个参数在C++标准中并没有明确规定
        static pointer allocate(size_type n, const void* hint = 0) {
            return _allocate((difference_type)n, (pointer)0);
        }

        static void deallocate(pointer p, size_type n) {
            // 使用 std::remove_pointer 来消除多重指针问题
            using base_type = typename std::remove_pointer<pointer>::type;
            _deallocate(static_cast<base_type*>(p));
        }

        // 构造函数
        static void construct(pointer p, const T& value) {
            _construct(p, value);
        }

        static void destroy(pointer p) {
            _destroy(p);
        }

        pointer address(reference x) {
            return (pointer)&x;
        }

        const_pointer const_address(const_reference x) {
            return (const_pointer)&x;
        }
    };

    


    template<class _Tp, class _Alloc>
    class simple_alloc {
    public:
        static _Tp* allocate(size_t __n)
            { return 0 == __n ? 0 : (_Tp*) _Alloc::allocate(__n * sizeof (_Tp)); }
        static _Tp* allocate(void)
            { return (_Tp*) _Alloc::allocate(sizeof (_Tp)); }
        static void deallocate(_Tp* __p, size_t __n)
            { if (0 != __n) _Alloc::deallocate(__p, __n * sizeof (_Tp)); }
        static void deallocate(_Tp* __p)
            { _Alloc::deallocate(__p, sizeof (_Tp)); }
        static void destroy(_Tp* __p)
            { _Alloc::destroy(__p); }
        static void destroy(_Tp* __first, _Tp* __last)
            { for (; __first < __last; ++__first) _Alloc::destroy(__first); }    
        static void construct(_Tp* __p, const _Tp& __val)
            { _Alloc::construct(__p, __val); }
        static void construct(_Tp* __p)
            { _Alloc::construct(__p); }
    };
} // end of namespace Jianqiao

#endif // USE_JIANQIAO_ALLOC

#endif // __JIANQIAO_ALLOC_HPP__