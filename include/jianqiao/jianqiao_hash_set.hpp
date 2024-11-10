//
// Created by Mac on 24-11-10.
//

#ifndef JIANQIAOSTL_JIANQIAO_HASH_SET_HPP
#define JIANQIAOSTL_JIANQIAO_HASH_SET_HPP

#include "config.hpp"
#include "jianqiao_hashtable.hpp"
#include "jianqiao_function.hpp"

__JIANQIAO_BEGIN__

template <class Value, class HashFcn, class EqualKey, class Alloc = allocator<__hashtable_node<Value> > >
class hash_set{
    friend struct __hashtable_iterator<Value, Value, HashFcn, identity<Value>, EqualKey, Alloc>;
private:
    using ht = hashtable<Value, Value, HashFcn, identity<Value>, EqualKey, Alloc>;
    ht rep;
public:
    using key_type = typename ht::key_type;
    using value_type = typename ht::value_type;
    using hasher = typename ht::hasher;
    using key_equal = typename ht::key_equal;

    using size_type = typename ht::size_type;
    using difference_type = typename ht::difference_type;
    using const_pointer = typename ht::const_pointer;
    using const_reference = typename ht::const_reference;
    using const_iterator = typename ht::const_iterator;
    using pointer = typename ht::const_pointer;
    using reference = typename ht::const_reference;
    using iterator = typename ht::const_iterator;

    hasher hash_funct() const { return rep.hash_funct(); }
    key_equal key_eq() const { return rep.key_eq(); }

public:
    // 构造函数

    // 缺省使用大小为100的表格，在里面会调整为最接近且大于n的质数
    // hash函数为hasher(),键值比较函数为key_equal()
    hash_set() : rep(100, hasher(), key_equal()) {}

    // 使用大小为n的表格（实际上也会被调整成为大玉n的质数）
    explicit hash_set(size_type n) : rep(n, hasher(), key_equal()) {}

    // 指定了大小n还有hash函数
    hash_set(size_type n, const hasher& hf) : rep(n, hf, key_equal()) {}

    // 指定了大小n，hash函数hf，键值比较函数eql
    hash_set(size_type n, const hasher& hf, const key_equal& eql) : rep(n, hf, eql) {}

    // 利用迭代器区间构造
    template <class InputIterator>
    hash_set(InputIterator f, InputIterator l) : rep(100, hasher(), key_equal()) { rep.insert_unique(f, l); }
    template <class InputIterator>
    hash_set(InputIterator f, InputIterator l, size_type n) : rep(n, hasher(), key_equal()) { rep.insert_unique(f, l); }
    template <class InputIterator>
    hash_set(InputIterator f, InputIterator l, size_type n, const hasher& hf) : rep(n, hf, key_equal()) { rep.insert_unique(f, l); }
    template <class InputIterator>
    hash_set(InputIterator f, InputIterator l, size_type n, const hasher& hf, const key_equal& eql) : rep(n, hf, eql) { rep.insert_unique(f, l); }

public:
    // 下面操作都是直接调用hash_table 提供的操作
    // size
    size_type size() const { return rep.size(); }
    size_type max_size() const { return rep.max_size(); }
    bool empty() const { return rep.empty(); }
    void swap(hash_set& hs) { rep.swap(hs.rep); }

    // 插入和删除操作
    pair<iterator, bool> insert(const value_type& obj){
        pair<typename ht::iterator, bool> p = rep.insert_unique(obj);
        return pair<iterator, bool>(p.first, p.second);
    }
    template <class InputIterator>
    void insert(InputIterator f, InputIterator l) { rep.insert_unique(f, l); }
    pair<iterator, bool> insert_noresize(const value_type& obj){
        pair<typename ht::iterator, bool> p = rep.insert_unique_noresize(obj);
        return pair<iterator, bool>(p.first, p.second);
    }

    size_type erase(const key_type& key) { return rep.erase(key); }
    void erase(iterator it) { rep.erase(it); }
    void erase(iterator f, iterator l) { rep.erase(f, l); }
    void clear() { rep.clear(); }

    // 查找操作
    iterator find(const key_type& key) { return rep.find(key); }
    size_type count(const key_type& key) { return rep.count(key); }
    pair<iterator, iterator> equal_range(const key_type& key) { return rep.equal_range(key); }

    // 比较操作
    bool operator==(const hash_set& hs) const { return rep == hs.rep; }
    bool operator!=(const hash_set& hs) const { return rep != hs.rep; }

    void resize(size_type hint) { rep.resize(hint); }
    size_type bucket_count() const { return rep.bucket_count(); }
    size_type max_bucket_count() const { return rep.max_bucket_count(); }
    size_type elems_in_bucket(size_type n) const { return rep.elems_in_bucket(n); }

    iterator begin(){
        return rep.begin();
    }

    iterator end(){
        return rep.end();
    }

    // 重载运算符
    friend bool operator==(const hash_set& hs1, const hash_set& hs2) { return hs1.rep == hs2.rep; }
    friend bool operator!=(const hash_set& hs1, const hash_set& hs2) { return hs1.rep != hs2.rep; }

};

__JIANQIAO_END__
#endif //JIANQIAOSTL_JIANQIAO_HASH_SET_HPP
