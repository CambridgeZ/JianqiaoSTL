//
// Created by Mac on 24-11-10.
//

#ifndef JIANQIAOSTL_JIANQIAO_HASH_FUN_HPP
#define JIANQIAOSTL_JIANQIAO_HASH_FUN_HPP

#include "config.hpp"

__JIANQIAO_BEGIN__
template <class Key> struct hash {};

inline size_t __stl_hash_string(const char* s) {
    unsigned long h = 0;
    for (; *s; ++s) {
        h = 5 * h + *s;
    }
    return size_t(h);
}

template <>
struct hash<char*> {
    size_t operator()(const char* s) const { return __stl_hash_string(s); }
};

template <>
struct hash<const char*>
{
    size_t operator()(const char* s) const { return __stl_hash_string(s); }
};

template <>
struct hash<char> {
    size_t operator()(char x) const { return x; }
};

template <>
struct hash<unsigned char> {
    size_t operator()(unsigned char x) const { return x; }
};

template <>
struct hash<signed char> {
    size_t operator()(unsigned char x) const { return x; }
};

template <>
struct hash<short> {
    size_t operator()(short x) const { return x; }
};

template <>
struct hash<unsigned short> {
    size_t operator()(unsigned short x) const { return x; }
};

template <>
struct hash<int> {
    size_t operator()(int x) const { return x; }
};

template <>
struct hash<unsigned int> {
    size_t operator()(unsigned int x) const { return x; }
};

template <>
struct hash<long> {
    size_t operator()(long x) const { return x; }
};

template <>
struct hash<unsigned long> {
    size_t operator()(unsigned long x) const { return x; }
};



__JIANQIAO_END__

#endif //JIANQIAOSTL_JIANQIAO_HASH_FUN_HPP
