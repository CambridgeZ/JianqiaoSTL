//
// Created by Mac on 24-11-5.
//

#ifndef JIANQIAOSTL_JIANQIAO_RB_TREE_HPP
#define JIANQIAOSTL_JIANQIAO_RB_TREE_HPP

#include "jianqiao_rb_tree_support.hpp"
#include "jianqiao_algorithm.hpp"
#include <iostream>

using std::cout;
using std::endl;

__JIANQIAO_BEGIN__

template<typename Key, typename Value, class KeyOfValue,
        class Compare, class Alloc = allocator<__rb_tree_node<Value> > >
class rb_tree {
protected:
    using void_pointer = void*;

    using rb_tree_node = __rb_tree_node<Value>;
    using rb_tree_node_allocator = simple_alloc<rb_tree_node, Alloc>;
    using color_type = __rb_tree_color_type;

public:
    using key_type = Key;
    using value_type = Value;
    using pointer = value_type* ;
    using const_pointer = const value_type* ;
    using reference = value_type&;
    using const_reference = const value_type&;
    using link_type = rb_tree_node* ;
    using size_type = size_t;
    using difference_type = ptrdiff_t;
    using base_ptr = __rb_tree_node_base*;

protected:
    link_type get_node(){
        // 分配一个节点
        return rb_tree_node_allocator::allocate();
    }

    void put_node(link_type p){
        // 释放一个节点
        rb_tree_node_allocator::deallocate(p);
    }

    link_type create_node(const value_type& x){
        // 创建一个节点
        link_type tmp = get_node();
        try{
            construct(&tmp->value_field, x);
        }
        catch(...){
            put_node(tmp);
        }
        return tmp;
    }

    link_type clone_node(link_type x){  // 复制一个节点
        link_type tmp = create_node(x->value_field);
        tmp->color = x->color;
        tmp->left = nullptr;
        tmp->right = nullptr;
        return tmp;
    }

    void destroy_node(link_type p){
        destroy(&p->value_field);
        put_node(p);
    }

protected:
    size_type node_count;
    link_type header;
    Compare key_compare;

    // 以下三个函数用来方便取得header的成员
    /*
     * header 的 parent 指向 root
     * header 的 left 指向最小值
     * header 的 right 指向最大值
     */
#ifdef __JIANQIAO_DEBUG_RB_TREE__
public:
#endif

    link_type& root() const {
        return (link_type&) header->parent;
    }

    link_type& leftmost() const {
        return (link_type&) header->left;
    }

    link_type& rightmost() const {
        return (link_type&) header->right;
    }

    // 以下六个函数用来方便取得节点x的成员
    static link_type& left(link_type x){
        return (link_type&) (x->left);
    }

    static link_type& right(link_type x){
        return (link_type&) (x->right);
    }

    static link_type& parent(link_type x){
        return (link_type&) (x->parent);
    }

    static reference value(link_type x){
        return x->value_field;
    }

    static const Key& key(link_type x){
        return KeyOfValue()(value(x));
    }

    static color_type& color(link_type x){
        return (color_type&) (x->color);
    }

    // 以下六个函数用来方便取得节点x的成员
    static link_type& left(base_ptr x){
        return (link_type&) (x->left);
    }

    static link_type& right(base_ptr x){
        return (link_type&) (x->right);
    }

    static link_type& parent(base_ptr x){
        return (link_type&) (x->parent);
    }

    static reference value(base_ptr x){
        return ((link_type)x)->value_field;
    }

    static const Key& key(base_ptr x){
        return KeyOfValue()(value(link_type(x)));
    }

    static color_type& color(base_ptr x){
        return (color_type&) (link_type(x)->color);
    }

    // 求取极小值  和 极大值
    static link_type minimum(link_type x){
        return (link_type) __rb_tree_node_base::minimum(x);
    }

    static link_type maximum(link_type x){
        return (link_type) __rb_tree_node_base::maximum(x);
    }

public:
    using iterator = __rb_tree_iterator<Value, Value&, Value*>;
    using const_iterator = __rb_tree_iterator<Value, const Value&, const Value*>;

private:
    iterator __insert(base_ptr x, base_ptr y, const value_type& v);
    link_type __copy(link_type x, link_type p){
        link_type top = clone_node(x);
        top->parent = p;
        try{
            if(right(x)){
                top->right = __copy(right(x), top);
            }
            p = top;
            x = left(x);
            while(x != nullptr){
                link_type y = clone_node(x);
                p->left = y;
                y->parent = p;
                if(right(x)){
                    y->right = __copy(right(x), y);
                }
                p = y;
                x = left(x);
            }
        }
        catch(...){
            __erase(top);
        }
        return top;
    }
    void __erase(link_type x){
        while(x != nullptr){
            // 递归删除左子树
            __erase(right(x));
            link_type y = left(x);
            destroy_node(x);
            x = y;
        }
    }
    void init(){
        header = get_node();            // 产生一个节点空间，令header指向它
        color(header) = __rb_tree_red;  // 令header为红色，用来区分header
        root() = nullptr;
        leftmost() = header;
        rightmost() = header;
    }

public:
    rb_tree(const Compare& comp = Compare())
        :node_count(0), key_compare(comp){
        init();
    }

    ~rb_tree(){
        clear();
        put_node(header);
    }

private:
    void clear(){
        if(node_count != 0){
            __erase(root());
            leftmost() = header;
            root() = nullptr;
            rightmost() = header;
            node_count = 0;
        }
    }

public:
    rb_tree<Key, Value, KeyOfValue, Compare, Alloc>
    &operator=(const rb_tree<Key, Value, KeyOfValue, Compare, Alloc>& x){
        if(this != &x){
            clear();
            node_count = 0;
            key_compare = x.key_compare;
            if(x.root() == nullptr){
                root() = nullptr;
                leftmost() = header;
                rightmost() = header;
            }
            else{
                root() = __copy(x.root(), header);
                leftmost() = minimum(root());
                rightmost() = maximum(root());
                node_count = x.node_count;
            }
        }
        return *this;
    }
    Compare key_comp() const {return key_compare;}
    iterator begin() {return leftmost();}
    const_iterator begin() const {return leftmost();}
    iterator end() {return header;}
    const_iterator end() const {return header;}
    iterator rbegin() {return rightmost();}
    iterator rend() {return header;}
    bool empty() const {return node_count == 0;}
    size_type size() const {return node_count;}
    size_type max_size() const {return size_type(-1);}

    // 交换
    void swap( rb_tree<Key, Value, KeyOfValue, Compare, Alloc>& t){
        Jianqiao::swap(header, t.header);
        Jianqiao::swap(node_count, t.node_count);
        Jianqiao::swap(key_compare, t.key_compare);
    }

public:
    pair<iterator, bool> insert_unique(const value_type& x);
    iterator insert_equal(const value_type& x);
    iterator insert_equal(iterator position, const value_type &v);
    template<class InputIterator>
    iterator insert_equal(InputIterator first, InputIterator last);
    iterator find(const Key& k);
    const_iterator find(const Key& k) const;

    // erase 相关操作
    size_type erase(const Key& k);
    void erase(iterator position);
    void erase(const_iterator position);
    void erase(iterator first, iterator last);
    void erase(const_iterator first, const_iterator last);

    iterator lower_bound(const Key& k);
    iterator upper_bound(const Key& k);
    // 返回一个pair, 第一个元素为lower_bound, 第二个元素为upper_bound, 也就是一个闭区间，不是左闭右开区间
    pair<iterator, iterator> equal_range(const Key& k);
    size_type count(const Key& k) const;

    // 运算符重载
    bool operator==(const rb_tree<Key, Value, KeyOfValue, Compare, Alloc>& x){
        return node_count == x.node_count && Jianqiao::equal(begin(), end(), x.begin());
    }

    bool operator!=(const rb_tree<Key, Value, KeyOfValue, Compare, Alloc>& x){
        return !(*this == x);
    }

    bool operator<(const rb_tree<Key, Value, KeyOfValue, Compare, Alloc>& x){
        return Jianqiao::lexicographical_compare(begin(), end(), x.begin(), x.end());
    }

    bool operator>(const rb_tree<Key, Value, KeyOfValue, Compare, Alloc>& x){
        return x < *this;
    }
};

template<typename Key, typename Value, class KeyOfValue, class Compare, class Alloc>
typename rb_tree<Key,Value,KeyOfValue,Compare,Alloc>::size_type
    rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::count(const Key &k) const {
        pair<const_iterator, const_iterator> p = equal_range(k);
        size_type n = 0;
        distance(p.first, p.second, n);
        return n;
    }

// insert_equal
template<typename Key, typename Value, class KeyOfValue,
        class Compare, class Alloc>
typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::insert_equal(const value_type &v) {
    link_type y = header;
    link_type x = root();
    while(x != nullptr){
        // 从根节点开始比较，如果遇到大的则向左进行比较，否则向右进行比较
        y = x;
        x = key_compare(KeyOfValue()(v), key(x)) ? left(x) : right(x);
    }
    return __insert(x, y, v);
}

template<typename Key, typename Value, class KeyOfValue, class Compare, class Alloc>
typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::insert_equal(iterator position, const value_type &v) {
    if(position.node == header->left){
        if(size() > 0 && key_compare(KeyOfValue()(v), key(position.node))){
            return __insert(position.node, position.node, v);
        }
        else{
            return insert_equal(v);
        }
    }
    else if(position.node == header){
        if(key_compare(key(rightmost()), KeyOfValue()(v))){
            return __insert(nullptr, rightmost(), v);
        }
        else{
            return insert_equal(v);
        }
    }
    else{
        iterator before = position;
        --before;
        if(key_compare(key(before.node), KeyOfValue()(v)) && key_compare(KeyOfValue()(v), key(position.node))){
            if(right(before.node) == nullptr){
                return __insert(nullptr, before.node, v);
            }
            else{
                return __insert(position.node, position.node, v);
            }
        }
        else{
            return insert_equal(v);
        }
    }
}

template<typename Key, typename Value, class KeyOfValue, class Compare, class Alloc>
template<class InputIterator>
typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::insert_equal(InputIterator first, InputIterator last) {
    for(; first != last; ++first){
        insert_equal(*first);
    }
    return iterator(header->parent);
}

// insert_unique
// 插入新的值，不允许重复，如果重复则插入无效
// 返回值为一个pair, 第一个元素为一个RB_tree的迭代器，第二个元素为一个bool值，表示是否插入成功

template<typename Key, typename Value, class KeyOfValue, typename Compare, class Alloc>
pair<typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator, bool>
rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::insert_unique(const value_type &v) {
    link_type y = header;
    link_type x = root();
    bool comp = true;
    while(x != nullptr){    // 从根节点向下寻找适当的插入点
        y = x;
        comp = key_compare(KeyOfValue()(v), key(x));    // v是否小于x
        x = comp ? left(x) : right(x);                  // 如果小于则向左，否则向右
    }
    iterator j = iterator(y);                    // j为插入点的父节点
    if(comp){
        if(j == begin()){   // 如果插入点为最左边
            // 这个时候说明插入点的最左边一定是最小值，一定是小于v的
            return pair<iterator, bool>(__insert(x, y, v), true);
        }
        else{   // 否则插入点不为最左边
            --j; // 调整j, 等待回头进行测试
        }
    }
    if(key_compare(key(j.node), KeyOfValue()(v))){
        // 新的键的值不等于任何键值，插入成功
        return pair<iterator, bool>(__insert(x, y, v), true);
    }

    // 如果到这里说明键值已经存在，插入失败
    return pair<iterator, bool>(j, false);
}

// __insert: 真正执行了插入操作的函数
template<typename Key, typename Value, class KeyOfValue, typename Compare, class Alloc>
typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>:: iterator
rb_tree<Key, Value, KeyOfValue, Compare, Alloc> ::
__insert(base_ptr x_, base_ptr y_, const Value& v){
    // x_ 为插入点， y_ 为插入点的父节点
    // v 为插入的值
    link_type x = (link_type) x_;
    link_type y = (link_type) y_;
    link_type z;

    // key_compare 用于比较键值大小，为一个function object
    if(y == header || x != nullptr || key_compare(KeyOfValue()(v), key(y))){
        // 如果插入点为header 或者 x不为空 或者 v小于y

        z = create_node(v);

        if(z == nullptr){
            cout<< "create_node error" << endl;
        }

        left(y) = z;

        // 如果插入点为header
        // 也就是说这个节点就是这个树插入进去的第一个节点
        if(y == header){
            // 节点就是root节点
            root() = z;
            rightmost() = z;
        }
        else if(y == leftmost()){
            // 插入的节点在最左边的左边
            leftmost() = z;
        }
    }
    else{
        // 应该插入的节点在y节点的右边的位置
        z = create_node(v);

        if(z == nullptr){
            cout<< "create_node error" << endl;
        }

        right(y) = z;
        if(y == rightmost()){
            rightmost() = z;
        }
    }

    // 调整信节点应该指向的位置
    parent(z) = y;      // 新节点的父节点指向y
    left(z) = nullptr;  // 新节点的左子节点为空
    right(z) = nullptr; // 新节点的右子节点为空

    // 前面完成的相当于仅仅是二叉排序树的插入操作
    // 完成插入之后对于颜色的调整操作

    // 以下开始调整红黑树
    __rb_tree_rebalance(z, header->parent);
    ++node_count;
    return iterator(z);
}


template<typename Key, typename Value, class KeyOfValue, typename Compare, class Alloc>
typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::find(const Key &k) {
    link_type y = header;   // 最后一个不小于k的节点
    link_type x = root();   // 当前节点
    while(x != nullptr){
        if(!key_compare(key(x), k)){
            y = x;
            x = left(x);
        }
        else{
            x = right(x);
        }
    }
    iterator j = iterator(y);
    return (j == end() || key_compare(k, key(j.node))) ? end() : j;
}

//const 版的 find
template<typename Key, typename Value, class KeyOfValue, typename Compare, class Alloc>
typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::const_iterator
rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::find(const Key &k) const {
    link_type y = header;   // 最后一个不小于k的节点
    link_type x = root();   // 当前节点
    while(x != nullptr){
        if(!key_compare(key(x), k)){
            y = x;
            x = left(x);
        }
        else{
            x = right(x);
        }
    }
    const_iterator j = const_iterator(y);
    return (j == end() || key_compare(k, key(j.node))) ? end() : j;
}

//erase 相关操作
template<typename Key, typename Value, class KeyOfValue, typename Compare, class Alloc>
typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::size_type
rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::erase(const Key &k) {
    pair<iterator, iterator> p = equal_range(k);
    size_type n = distance(p.first, p.second);

//    cout << "n: " << n << endl;
    // 判断是否找到了k

    // 输出第二个节点的值
//    cout << "p.second: " << *p.second << endl;

    erase(p.first, p.second);
    return n+1;
}

template<typename Key, typename Value, class KeyOfValue, typename Compare, class Alloc>
void rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::erase(iterator position) {
    link_type y = (link_type) __rb_tree_rebalance_for_erase(position.node, header->parent, header->left, header->right);
    destroy_node(y);
    --node_count;
}

template<typename Key, typename Value, class KeyOfValue, typename Compare, class Alloc>
void rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::erase(const_iterator position) {
    link_type y = (link_type) __rb_tree_rebalance_for_erase(position.node, header->parent, header->left, header->right);
    destroy_node(y);
    --node_count;
}



template<typename Key, typename Value, class KeyOfValue, typename Compare, class Alloc>
void rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::erase(iterator first, iterator last) {
    if(first == begin() && last == end()){
        clear();
    }
    else{
        while(first != last){
            erase(first++);
        }
    }
}

template<typename Key, typename Value, class KeyOfValue, typename Compare, class Alloc>
void rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::erase(const_iterator first, const_iterator last) {
    if(first == begin() && last == end()){
        clear();
    }
    else{
        while(first != last){
            erase(first++);
        }
    }
}


// lower_bound

template<typename Key, typename Value, class KeyOfValue, typename Compare, class Alloc>
typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::lower_bound(const Key &k) {
    // 找到第一个不小于k的节点
    link_type y = header;   // 最后一个不小于k的节点
    link_type x = root();   // 当前节点
    while(x != nullptr){
        if(!key_compare(key(x), k)){
            // x的键值大于等于k
            y = x;
            x = left(x);
        }
        else{
            x = right(x);
        }
    }
    return iterator(y);
}

// upper_bound

template<typename Key, typename Value, class KeyOfValue, typename Compare, class Alloc>
typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator
rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::upper_bound(const Key &k) {
    // 找到第一个大于k的节点

    link_type y = header;   // 最后一个不小于k的节点
    link_type x = root();   // 当前节点
    while(x != nullptr){
        if(key_compare(k, key(x))){
            // x的键值大于k
            y = x;
            x = left(x);
        }
        else{
            x = right(x);
        }
    }
    return iterator(y);
}

// equal_range
template <typename Key, typename Value, class KeyOfValue, typename Compare, class Alloc>
pair<typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator,
        typename rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::iterator>
rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::equal_range(const Key &k) {
    return pair<iterator, iterator>(lower_bound(k), upper_bound(k));
}


__JIANQIAO_END__
#endif //JIANQIAOSTL_JIANQIAO_RB_TREE_HPP
