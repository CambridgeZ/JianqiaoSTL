//
// Created by Mac on 24-11-5.
//

#ifndef JIANQIAOSTL_JIANQIAO_RB_TREE_HPP
#define JIANQIAOSTL_JIANQIAO_RB_TREE_HPP

#include "config.hpp"
#include "jianqiao_iterator_base.hpp"
#include "alloc.hpp"

using std::pair;

__JIANQIAO_BEGIN__

using __rb_tree_color_type = bool;
const __rb_tree_color_type  __rb_tree_red = false;      //红色为0
const __rb_tree_color_type  __rb_tree_black = true;     // 黑色设置为1

struct __rb_tree_node_base{
    using color_type = __rb_tree_color_type;
    using base_ptr = __rb_tree_node_base*;

    color_type color;
    base_ptr parent;
    base_ptr left;
    base_ptr right;

    static base_ptr minimum(base_ptr x){
        while(x->left){
            x=x->left;
        }
        return x;
    }

    static base_ptr maximum(base_ptr x){
        while(x->right){
            x=x->right;
        }
        return x;
    }
};

template<typename Value>
struct __rb_tree_node: public __rb_tree_node_base{
    using link_type = __rb_tree_node<Value>*;
    Value value_field;
};

struct __rb_tree_base_iterator{

    using base_ptr = __rb_tree_node_base::base_ptr;
    using iterator_category = bidirectional_iterator_tag;
    using difference_type = ptrdiff_t;

    base_ptr node;
    void increment(){
        if(node->right){
            node = node->right;
            while(node->left != nullptr){
                node = node->left;
            }
        }
        else{
            base_ptr y = node->parent;  // 没有右子节点的时候先找到父节点
            while(node == y->right){    // 当前的节点是父节点的右子节点
                node = y;
                y = y->parent;
            }

            if(node->right != y){       // 如果右子节点不等于此时的父节点
                node = y;
            }
        }
    }

    void decrement(){
        if(node->color == __rb_tree_red && node->parent->parent == node){
            node = node->right;
            // 发生于node 为 header的情况
        }
        else if(node->left != nullptr){
            base_ptr y = node->left;
            while(y->right != nullptr){
                y = y->right;
            }
            node = y;
        }
        else{
            base_ptr y = node->parent;
            while(node == y->left){
                node = y;
                y = y->parent;
            }
            node = y;
        }
    }
};

template <typename Value, typename Ref, typename Ptr>
struct __rb_tree_iterator: public __rb_tree_base_iterator {
    using value_type = Value;
    using reference = Ref;
    using pointer = Ptr;
    using iterator = __rb_tree_iterator<Value, Value&, Value*>;
    using const_iterator = __rb_tree_iterator<Value, const Value&, const Value*>;
    using self = __rb_tree_iterator<Value, Ref, Ptr>;
    using link_type = __rb_tree_node<Value>*;

    __rb_tree_iterator() {}
    __rb_tree_iterator(link_type x) {node = x;};
    __rb_tree_iterator(const iterator& it) {node = it.node;};

    reference operator*() const {
        return link_type(node)->value_field;
    }

    pointer  operator->() const {
        return &(operator*());
    }

    self& operator++ (){
        increment();
        return *this;
    }

    self operator++(int){
        self old = *this;
        increment();
        return old;
    }

    self& operator-- (){
        decrement();
        return *this;
    }

    self operator--(int ){
        self old = *this;
        decrement();
        return old;
    }
};

template<typename Key, typename Value, typename KeyOfValue,
        class Compare, class Alloc = allocator<__rb_tree_node<Value> > >
class rb_tree {
protected:
    using void_pointer = void*;
    using base_ptr = __rb_tree_node_base*;
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
private:
    iterator __insert(base_ptr x, base_ptr y, const value_type& v);
    link_type __copy(link_type x, link_type p);
    void __erase(link_type x);
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
    &operator=(const rb_tree<Key, Value, KeyOfValue, Compare, Alloc>& x);
    Compare key_comp() const {return key_compare;}
    iterator begin() {return leftmost();}
    iterator end() {return header;}
    bool empty() const {return node_count == 0;}
    size_type size() const {return node_count;}
    size_type max_size() const {return size_type(-1);}

public:
    pair<iterator, bool> insert_unique(const value_type& x);
    iterator insert_equal(const value_type& x);
};

__JIANQIAO_END__
#endif //JIANQIAOSTL_JIANQIAO_RB_TREE_HPP
