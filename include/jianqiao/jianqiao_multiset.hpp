//
// Created by Mac on 24-11-9.
//

#ifndef JIANQIAOSTL_JIANQIAO_MULTISET_HPP
#define JIANQIAOSTL_JIANQIAO_MULTISET_HPP

#include "config.hpp"
#include "jianqiao_rb_tree.hpp"
#include "jianqiao_algorithm_base.hpp"
#include "jianqiao_function.hpp"

__JIANQIAO_BEGIN__
template<class Key, class Compare = less<Key>, class Alloc = allocator<__rb_tree_node<Key> > >
class multiset {
public:
    using key_value = Key;
    using key_type = Key;
    using value_type = Key;
    using key_compare = Compare;
    using value_compare = Compare;
private:
    using rep_type = rb_tree<key_value, key_value, identity<key_value>, key_compare, Alloc>;
    rep_type t;
public:
    using pointer = typename rep_type::const_pointer;
    using const_pointer = typename rep_type::const_pointer;

    using reference = typename rep_type::const_reference;
    using const_reference = typename rep_type::const_reference;

    using iterator = typename rep_type::const_iterator;
    using const_iterator = typename rep_type::const_iterator;

    using size_type = typename rep_type::size_type;
    using difference_type = typename rep_type::difference_type;

    multiset() : t(Compare()) {}
    explicit multiset(const Compare& comp) : t(comp) {}

    template<class InputIterator>
    multiset(InputIterator first, InputIterator last) : t(Compare()) {
        t.insert_equal(first, last);
    }

    template<class InputIterator>
    multiset(InputIterator first, InputIterator last, const Compare& comp) : t(comp) {
        t.insert_equal(first, last);
    }

    multiset(const multiset<Key, Compare, Alloc>& x) : t(x.t) {}

    multiset<Key, Compare, Alloc>& operator=(const multiset<Key, Compare, Alloc>& x){
        t = x.t;
        return *this;
    }

    // 对于multiset的操作，其实都是在操作rb_tree
    key_compare key_comp() const { return t.key_comp(); }
    value_compare value_comp() const { return t.key_comp(); }
    iterator begin() const {return t.begin();}
    iterator end() const {return t.end();}
    bool empty() const {return t.empty();}
    size_type size() const {return t.size();}
    size_type max_size() const {return t.max_size();}

    void swap(multiset<Key, Compare, Alloc>& x) {t.swap(x.t);}

    // insert / erase
    iterator insert(const value_type& x) {
        return t.insert_equal(x);
    }

    iterator insert(iterator position, const value_type& x) {
        using rep_iterator = typename rep_type::iterator;
        return t.insert_equal((rep_iterator&)position, x);
    }

    template<class InputIterator>
    void insert(InputIterator first, InputIterator last) {
        for(; first != last; ++first){
            t.insert_equal(*first);
        }
    }

    void erase(iterator position) {
        t.erase(position);
    }

    size_type erase(const key_type& x) {
        return t.erase(x);
    }

    void erase(iterator first, iterator last) {
        t.erase(first, last);
    }

    void clear() {
        t.clear();
    }

    iterator find(const key_type& x) const {
        return t.find(x);
    }

    size_type count(const key_type& x) const {
        return t.count(x);
    }

    iterator lower_bound(const key_type& x) const {
        return t.lower_bound(x);
    }

    iterator upper_bound(const key_type& x) const {
        return t.upper_bound(x);
    }

    pair<iterator , iterator > equal_range(const key_type& x) const {
        return t.equal_range(x);
    }

    // 重载运算符
    template<class Key1, class Compare1, class Alloc1>
    friend bool operator==(const multiset<Key1, Compare1, Alloc1>& x, const multiset<Key1, Compare1, Alloc1>& y);

    template<class Key1, class Compare1, class Alloc1>
            friend bool operator<(const multiset<Key1, Compare1, Alloc1>& x, const multiset<Key1, Compare1, Alloc1>& y);

};

template<class Key, class Compare, class Alloc>
bool operator==(const multiset<Key, Compare, Alloc>& x, const multiset<Key, Compare, Alloc>& y){
    return x.t == y.t;
}

template<class Key, class Compare, class Alloc>
bool operator!=(const multiset<Key, Compare, Alloc>& x, const multiset<Key, Compare, Alloc>& y){
    return !(x == y);
}

template<class Key, class Compare, class Alloc>
bool operator<(const multiset<Key, Compare, Alloc>& x, const multiset<Key, Compare, Alloc>& y){
    return x.t < y.t;
}

template<class Key, class Compare, class Alloc>
bool operator>(const multiset<Key, Compare, Alloc>& x, const multiset<Key, Compare, Alloc>& y){
    return y < x;
}

__JIANQIAO_END__
#endif //JIANQIAOSTL_JIANQIAO_MULTISET_HPP
