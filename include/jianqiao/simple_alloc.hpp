//
// Created by Mac on 24-11-2.
//

#ifndef JIANQIAOSTL_SIMPLE_ALLOC_HPP
#define JIANQIAOSTL_SIMPLE_ALLOC_HPP

#include "config.hpp"

namespace Jianqiao {

    template <class T, class Alloc>
    class simple_alloc {
    public:
        static T* allocate(size_t n) {
            return 0 == n ? 0 : (T*) Alloc::allocate(n * sizeof(T));
        }

        static T* allocate(void) {
            return (T*) Alloc::allocate(sizeof(T));
        }

        static void deallocate(T* p) {
            Alloc::deallocate(p, sizeof(T));
        }

        static void deallocate(T* p, size_t n) {
            if (0 != n) Alloc::deallocate(p, n * sizeof(T));
        }

        static void destroy(T* p) {
            Alloc::destroy(p);
        }

        static void destroy(T* first, T* last) {
            for (; first < last; ++first) Alloc::destroy(first);
        }

        static void construct(T* p, const T& val) {
            Alloc::construct(p, val);
        }

        static void construct(T* p) {
            Alloc::construct(p);
        }

        static T* address(T& x) {
            return (T*) &x;
        }
    };


} // Jianqiao

#endif //JIANQIAOSTL_SIMPLE_ALLOC_HPP
