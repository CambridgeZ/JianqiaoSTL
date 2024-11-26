//
// Created by Mac on 24-11-11.
//

#ifndef JIANQIAOSTL_JIANQIAO_HASH_MAP_HPP
#define JIANQIAOSTL_JIANQIAO_HASH_MAP_HPP

#include "config.hpp"
#include "jianqiao_hashtable.hpp"
#include "jianqiao_pair.hpp"
#include "jianqiao_function.hpp"
#include "jianqiao_hash_fun.hpp"

__JIANQIAO_BEGIN__

template<
        typename Key, typename T, typename HashFcn = hash<Key>,
        typename EqualKey = equal_to<Key>, typename Alloc = allocator<Jianqiao::__hashtable_node<pair<const Key, T> > >
        >
class hash_map{
private:
    using ht = hashtable<pair<const Key, T>, Key, HashFcn, select1st<pair<const Key, T> >, EqualKey, Alloc>;
    ht rep;
public:
    using key_type = typename ht::key_type;
    using data_type = T;
    using mapped_type = T;
    using value_type = typename ht::value_type;
    using hasher = typename ht::hasher;
    using key_equal = typename ht::key_equal;

    using size_type = typename ht::size_type;
    using difference_type = typename ht::difference_type;
    using pointer = typename ht::pointer;
    using const_pointer = typename ht::const_pointer;
    using reference = typename ht::reference;
    using const_reference = typename ht::const_reference;
    using iterator = typename ht::iterator;
    using const_iterator = typename ht::const_iterator;

    hasher hash_funct() const { return rep.hash_funct(); }
    key_equal key_eq() const { return rep.key_eq(); }

public:
    hash_map(): rep(100, hasher(), key_equal()) {}
    explicit hash_map(size_type n): rep(n, hasher(), key_equal()) {}
    hash_map(size_type n, const hasher& hf): rep(n, hf, key_equal()) {}
    hash_map(size_type n, const hasher& hf, const key_equal& eql): rep(n, hf, eql) {}

    template <class InputIterator>
            hash_map(InputIterator f, InputIterator l): rep(100, hasher(), key_equal()) { rep.insert_unique(f, l); }

    template <class InputIterator>
            hash_map(InputIterator f, InputIterator l, size_type n): rep(n, hasher(), key_equal()) { rep.insert_unique(f, l); }

    template <class InputIterator>
            hash_map(InputIterator f, InputIterator l, size_type n, const hasher& hf): rep(n, hf, key_equal()) { rep.insert_unique(f, l); }

    template<class InputIterator>
    hash_map(InputIterator f, InputIterator l, size_type n, const hasher& hf, const key_equal& eql): rep(n, hf, eql) { rep.insert_unique(f, l); }

public:
    size_type size() const { return rep.size(); }
    size_type max_size() const { return rep.max_size(); }
    bool empty() const { return rep.empty(); }
    void swap(hash_map& hs) { rep.swap(hs.rep); }
    friend bool operator==(const hash_map&, const hash_map&);
    friend bool operator!=(const hash_map&, const hash_map&);

    iterator begin() {
        return rep.begin();
    }

    iterator end() {
        return rep.end();
    }

    const_iterator begin() const {
        return rep.begin();
    }

    const_iterator end() const {
        return rep.end();
    }

    pair<iterator, bool> insert(const value_type& obj){
        return rep.insert_unique(obj);
    }

    template <class InputIterator>
    void insert(InputIterator f, InputIterator l){
        rep.insert_unique(f, l);
    }

    // 存在问题，回头debug
    T& operator[](const key_type& key){
        return rep.find_or_insert(value_type(key, T())).second;
    }

    size_type count(const key_type& key) const {
        return rep.count(key);
    }

    pair<iterator, iterator> equal_range(const key_type& key){
        return rep.equal_range(key);
    }

    pair<const_iterator, const_iterator> equal_range(const key_type& key) const {
        return rep.equal_range(key);
    }

    size_type erase(const key_type& key){
        return rep.erase(key);
    }

    void erase(iterator it){
        rep.erase(it);
    }

    void erase(iterator f, iterator l){
        rep.erase(f, l);
    }

    void clear(){
        rep.clear();
    }

    iterator find(const key_type& key){
        return rep.find(key);
    }

    const_iterator find(const key_type& key) const {
        return rep.find(key);
    }

    void resize(size_type hint){
        rep.resize(hint);
    }

    void resize(size_type hint, const hasher& hf){
        rep.resize(hint, hf);
    }

    size_type bucket_count() const {
        return rep.bucket_count();
    }

    size_type max_bucket_count() const {
        return rep.max_bucket_count();
    }

    size_type elems_in_bucket(size_type n) const {
        return rep.elems_in_bucket(n);
    }
};

template <typename Key, typename T, typename HashFcn, typename EqualKey, typename Alloc>
bool operator==(const hash_map<Key, T, HashFcn, EqualKey, Alloc>& hm1, const hash_map<Key, T, HashFcn, EqualKey, Alloc>& hm2){
    return hm1.rep == hm2.rep;
}

template <typename Key, typename T, typename HashFcn, typename EqualKey, typename Alloc>
bool operator!=(const hash_map<Key, T, HashFcn, EqualKey, Alloc>& hm1, const hash_map<Key, T, HashFcn, EqualKey, Alloc>& hm2){
    return !(hm1 == hm2);
}

__JIANQIAO_END__

#endif //JIANQIAOSTL_JIANQIAO_HASH_MAP_HPP