//
// Created by Mac on 24-11-8.
//

#ifndef JIANQIAOSTL_JIANQIAO_SET_HPP
#define JIANQIAOSTL_JIANQIAO_SET_HPP

#include "jianqiao_rb_tree.hpp"
#include <algorithm>
#include "jianqiao_function.hpp"

using std::less;

namespace Jianqiao {

    template<class Key, class Compare = less<Key>, class Alloc = allocator<__rb_tree_node<Key> > >
    class set {
    public:
        using key_type = Key;
        using value_type = Key;
        using key_compare = Compare;
        using value_compare = Compare;
    private:
        using rep_type = rb_tree<key_type, value_type, identity<value_type>, key_compare, Alloc>;
        rep_type t;
    public:
        // 不可以利用迭代器等对于set当中的元素进行修改，因为会造成对于数据结构的损失
        using pointer = typename rep_type::const_pointer;
        using const_pointer = typename rep_type::const_pointer;

        using reference = typename rep_type::const_reference;
        using const_reference = typename rep_type::const_reference;

        using iterator = typename rep_type::const_iterator;
        using const_iterator = typename rep_type::const_iterator;

//        using reverse_iterator = typename rep_type::const_reverse_iterator;
//        using const_reverse_iterator = typename rep_type::const_reverse_iterator;

        using size_type = typename rep_type::size_type;
        using difference_type = typename rep_type::difference_type;

        // 构造函数
        set() : t(Compare()) {}
        explicit set(const Compare& comp) : t(comp) {}

        template<class InputIterator>
        set(InputIterator first, InputIterator last) : t(Compare()) {
            t.insert_unique(first, last);
        }

        template<class InputIterator>
        set(InputIterator first, InputIterator last, const Compare& comp) : t(comp) {
            t.insert_unique(first, last);
        }

        set(const set<Key, Compare, Alloc>& x) : t(x.t) {}

        // 操作符重载
        set<Key, Compare, Alloc>& operator = (const set<Key, Compare, Alloc>& x) {
            t = x.t;
            return *this;
        }

        // set 的操作，其实都是在操作rb_tree

        key_compare key_comp() const { return t.key_comp(); }
        value_compare value_comp() const { return t.key_comp(); }
        iterator begin() const {return t.begin();}
        iterator end() const {return t.end();}
//        reverse_iterator rbegin() const {return t.rbegin();}
//        reverse_iterator rend() const {return t.rend();}
        bool empty() const {return t.empty();}
        size_type size() const {return t.size();}
        size_type max_size() const {return t.max_size();}

        void swap(set<Key, Compare, Alloc>& x) {t.swap(x.t);}

        //insert / erase

        using pair_iterator_bool = pair<iterator, bool>;
        pair_iterator_bool insert(const value_type& x) {
            pair<typename rep_type::iterator, bool> p = t.insert_unique(x);
            return pair_iterator_bool(p.first, p.second);
        }

        iterator insert(iterator position, const value_type& x) {
            using rep_iterator = typename rep_type::iterator;
            return t.insert_unique((rep_iterator&)position, x);
        }

        template<class InputIterator>
        void insert(InputIterator first, InputIterator last) {
            for(; first != last; ++first){
                t.insert_unique(*first);
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

        pair<iterator, iterator> equal_range(const key_type& x) const {
            return t.equal_range(x);
        }

        // 重载操作符

        template<class Key1, class Compare1, class Alloc1>
        friend bool operator == (const set<Key1, Compare1, Alloc1>&, const set<Key1, Compare1, Alloc1>&);

        template<class Key1, class Compare1, class Alloc1>
        friend bool operator < (const set<Key1, Compare1, Alloc1>&, const set<Key1, Compare1, Alloc1>&);

    };// end of set

    template <class Key, class Compare, class Alloc>
    inline bool operator == (const Jianqiao::set<Key, Compare, Alloc>& x, const Jianqiao::set<Key, Compare, Alloc>& y) {
        return x.t == y.t;
    }

    template <class Key, class Compare, class Alloc>
    inline bool operator < (const Jianqiao::set<Key, Compare, Alloc>& x, const Jianqiao::set<Key, Compare, Alloc>& y) {
        return x.t < y.t;
    }

} // Jianqiao






#endif //JIANQIAOSTL_JIANQIAO_SET_HPP
