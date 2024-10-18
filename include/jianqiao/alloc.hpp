//file jianqiao/alloc.hpp

#ifndef __JIANQIAO_ALLOC_HPP__
#define __JIANQIAO_ALLOC_HPP__

#include <new>
#include <cstdlib>
#include <cstddef>
#include <climits>
#include <iostream>

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

    template <class T>
    class allocator{
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
        struct rebind{
            typedef allocator<U> other;
        };

        // hint 用于指定内存分配器的行为，但是这个参数在C++标准中并没有明确规定
        pointer allocate(size_type n, const void* hint = 0){
            return _allocate((difference_type)n, (pointer)0);
        }

        void deallocate(pointer p, size_type n){
            _deallocate(p);
        }

        // 构造函数
        void construct(pointer p, const T& value){
            _construct(p, value);
        }

        void destroy(pointer p){
            _destroy(p);
        }

        pointer address(reference x){
            return (pointer)&x;
        }

        const_pointer const_address(const_reference x){
            return (const_pointer)&x;
        }
    };
} // end of namespace Jianqiao


#endif // __JIANQIAO_ALLOC_HPP__