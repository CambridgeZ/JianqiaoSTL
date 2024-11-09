//
// Created by Mac on 24-11-8.
//

#ifndef JIANQIAOSTL_JIANQIAO_MAP_HPP
#define JIANQIAOSTL_JIANQIAO_MAP_HPP

#include "config.hpp"
#include "jianqiao_pair.hpp"
#include "jianqiao_function.hpp"
#include "jianqiao_rb_tree.hpp"

__JIANQIAO_BEGIN__

template <typename Key, typename T, typename Compare = std::less<Key>,
        typename Alloc = allocator<__rb_tree_node<pair<Key, T> > > >
class map {
public:
    using key_type = Key;
    using data_type = T;
    using mapped_type = T;
    using value_type = pair<Key, T>; // 键值是不可以被修改的
    using key_compare = Compare;

    class value_compare : public binary_function<value_type, value_type, bool> {
        friend class map<Key, T, Compare, Alloc>;
    protected:
        Compare comp;
        value_compare(Compare c) : comp(c) {}
    public:
        bool operator()(const value_type &x, const value_type &y) const {
            return comp(x.first, y.first);
        }
    };

private:

    using rep_type = rb_tree<key_type, value_type, select1st<value_type>, key_compare, Alloc>;
    rep_type t;

public:
    using pointer = typename rep_type::pointer;
    using const_pointer = typename rep_type::const_pointer;
    using reference = typename rep_type::reference;
    using const_reference = typename rep_type::const_reference;
    using iterator = typename rep_type::iterator;
    using const_iterator = typename rep_type::const_iterator;
//    using reverse_iterator = typename rep_type::reverse_iterator;
//    using const_reverse_iterator = typename rep_type::const_reverse_iterator;
    using size_type = typename rep_type::size_type;
    using difference_type = typename rep_type::difference_type;

    // allocation/deallocation
    map() : t(Compare()) {}
    explicit map(const Compare &c, const Alloc &a = Alloc()) : t(c, a) {}

    template<class InputIterator>
    map(InputIterator first, InputIterator last) : t(Compare()) {
        for(; first != last; ++first){
            t.insert_unique(*first);
        }
    }

    template<class InputIterator>
    map(InputIterator first, InputIterator last, const Compare &c, const Alloc &a = Alloc()) : t(c, a) {
       for(; first != last; ++first){
           t.insert_unique(*first);
       }
    }

    map(const map<Key, T, Compare, Alloc> &x) : t(x.t) {}

    map<Key, T, Compare, Alloc>& operator=(const map<Key, T, Compare, Alloc> &x){
        t = x.t;
        return *this;
    }

    //accessor
    key_compare key_comp() const { return t.key_comp(); }
    value_compare value_comp() const { return value_compare(t.key_comp()); }
    iterator begin() { return t.begin(); }
    const_iterator begin() const { return t.begin(); }
    iterator end() { return t.end(); }
    const_iterator end() const { return t.end(); }
//    reverse_iterator rbegin() { return t.rbegin(); }
//    reverse_iterator rend() { return t.rend(); }
    bool empty() const { return t.empty(); }
    size_type size() const { return t.size(); }
    size_type max_size() const { return t.max_size(); }

    T& operator[](const key_type &k) {
        return (*((insert(value_type(k, T()))).first)).second;
    }

    void swap(map<Key, T, Compare, Alloc> &x) { t.swap(x.t); }

    // insert/erase
    pair<iterator, bool> insert(const value_type &x) {
        return t.insert_unique(x);
    }

    iterator insert(iterator position, const value_type &x) {
        return t.insert_unique(position, x);
    }

    template <class InputIterator>
    void insert(InputIterator first, InputIterator last) {
        for(; first != last; ++first){
            t.insert_unique(*first);
        }
    }

    void erase(iterator position) {
        t.erase(position);
    }

    size_type erase(const key_type &x) {
        return t.erase(x);
    }

    void erase(iterator first, iterator last) {
        t.erase(first, last);
    }

    void clear(){
        t.clear();
    }

    iterator find(const key_type &x) { return t.find(x); }
    const_iterator find(const key_type &x) const { return t.find(x); }

    size_type count(const key_type &x) const { return t.count(x); }

    iterator lower_bound(const key_type &x) { return t.lower_bound(x); }
    const_iterator lower_bound(const key_type &x) const { return t.lower_bound(x); }
    iterator upper_bound(const key_type &x) { return t.upper_bound(x); }
    const_iterator upper_bound(const key_type& x) const {
        return t.upper_bound(x);
    }

    pair<iterator, iterator> equal_range(const key_type &x) { return t.equal_range(x); }
    pair<const_iterator, const_iterator> equal_range(const key_type &x) const { return t.equal_range(x); }

    // 重载运算符
    friend bool operator == (const map<Key, T, Compare, Alloc> &x, const map<Key, T, Compare, Alloc> &y){
        return x.t == y.t;
    }

    friend bool operator < (const map<Key, T, Compare, Alloc> &x, const map<Key, T, Compare, Alloc> &y){
        return x.t < y.t;
    }
};

//template <typename Key, typename T, typename Compare, typename Alloc>
//inline bool operator == (const map<Key, T, Compare, Alloc> &x, const map<Key, T, Compare, Alloc> &y) {
//    return x.t == y.t;
//}


__JIANQIAO_END__

#endif //JIANQIAOSTL_JIANQIAO_MAP_HPP
