//
// Created by Mac on 24-11-11.
//

#ifndef JIANQIAOSTL_JIANQIAO_HASH_MULTISET_HPP
#define JIANQIAOSTL_JIANQIAO_HASH_MULTISET_HPP

#include "config.hpp"
#include "jianqiao_hashtable.hpp"
#include "jianqiao_function.hpp"
#include "jianqiao_hash_fun.hpp"

__JIANQIAO_BEGIN__

template <class Value, class HashFcn = hash<Value>, class EqualKey = equal_to<Value>, class Alloc = allocator<__hashtable_node<Value> > >
class hash_multiset {
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
    // construct

    hash_multiset() : rep(100, hasher(), key_equal()) {}

    explicit hash_multiset(size_type n) : rep(n, hasher(), key_equal()) {}

    hash_multiset(size_type n, const hasher& hf) : rep(n, hf, key_equal()) {}

    hash_multiset(size_type n, const hasher& hf, const key_equal& eql) : rep(n, hf, eql) {}

    template <class InputIterator>
    hash_multiset(InputIterator f, InputIterator l) : rep(100, hasher(), key_equal()) { rep.insert_equal(f, l); }

    template<class InputIterator>
    hash_multiset(InputIterator f, InputIterator l, size_type n) : rep(n, hasher(), key_equal()) { rep.insert_equal(f, l); }

    template<class InputIterator>
    hash_multiset(InputIterator f, InputIterator l, size_type n, const hasher& hf) : rep(n, hf, key_equal()) { rep.insert_equal(f, l); }

    template<class InputIterator>
    hash_multiset(InputIterator f, InputIterator l, size_type n, const hasher& hf, const key_equal& eql) : rep(n, hf, eql) { rep.insert_equal(f, l); }

public:
    // 接口，主要是直接调用hashtable的接口

    size_type size() const { return rep.size(); }

    size_type max_size() const { return rep.max_size(); }

    bool empty() const { return rep.empty(); }

    void swap(hash_multiset& hs) { rep.swap(hs.rep); }

    iterator begin() { return rep.begin(); }

    iterator end() { return rep.end(); }

    const_iterator begin() const { return rep.begin(); }

    const_iterator end() const { return rep.end(); }

    iterator insert(const value_type& obj) { return rep.insert_equal(obj); }

    template <class InputIterator>
    void insert(InputIterator f, InputIterator l) { rep.insert_equal(f, l); }

    void erase(const key_type& key) { return rep.erase(key); }

    void erase(iterator it) { rep.erase(it); }

    void erase(iterator f, iterator l) { rep.erase(f, l); }

    void clear() { rep.clear(); }

    iterator find(const key_type& key) { return rep.find(key); }

    size_type count(const key_type& key) { return rep.count(key); }

    pair<iterator, iterator> equal_range(const key_type& key) { return rep.equal_range(key); }

    bool operator==(const hash_multiset& hs) const { return rep == hs.rep; }

    bool operator!=(const hash_multiset& hs) const { return rep != hs.rep; }

    void resize(size_type hint) { rep.resize(hint); }

    size_type bucket_count() const { return rep.bucket_count(); }

    size_type max_bucket_count() const { return rep.max_bucket_count(); }

    size_type elems_in_bucket(size_type n) const { return rep.elems_in_bucket(n); }
};

// operator == and operator !=
template <class Value, class HashFcn, class EqualKey, class Alloc>
bool operator==(const hash_multiset<Value, HashFcn, EqualKey, Alloc>& hs1, const hash_multiset<Value, HashFcn, EqualKey, Alloc>& hs2) {
    return hs1.rep == hs2.rep;
}

template <class Value, class HashFcn, class EqualKey, class Alloc>
bool operator!=(const hash_multiset<Value, HashFcn, EqualKey, Alloc>& hs1, const hash_multiset<Value, HashFcn, EqualKey, Alloc>& hs2) {
    return !(hs1 == hs2);
}


__JIANQIAO_END__
#endif //JIANQIAOSTL_JIANQIAO_HASH_MULTISET_HPP
