//
// Created by Mac on 24-11-7.
//

#ifndef JIANQIAOSTL_JIANQIAO_RB_TREE_SUPPORT_HPP
#define JIANQIAOSTL_JIANQIAO_RB_TREE_SUPPORT_HPP

#include "config.hpp"
#include "jianqiao_iterator_base.hpp"
#include "alloc.hpp"

#ifdef __JIANQIAO_DEBUG_RB_TREE__
#include <iostream>

using std::cout;
using std::endl;
#endif

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

    // 重载比较操作符
    inline bool operator==(const __rb_tree_base_iterator& x, const __rb_tree_base_iterator& y){
        return x.node == y.node;
    }

    inline bool operator!=(const __rb_tree_base_iterator& x, const __rb_tree_base_iterator& y){
        return x.node != y.node;
    }

    // 在插入之后对于红黑树进行平衡的操作

    // 左旋操作
    inline void __rb_tree_rotate_left(__rb_tree_node_base* x, __rb_tree_node_base*& root){
#ifdef __JIANQIAO_DEBUG_RB_TREE__
        cout<<"left rotate"<<endl;
#endif
        // x 为旋转点
        __rb_tree_node_base* y = x->right;   // y 为旋转点的右子节点
        x->right = y->left; // 将y的左子节点挂到x的右子节点上
        if(y->left != nullptr){
            y->left->parent = x;    // 如果y的左子节点存在，则将其父节点设置为x
        }

        y->parent = x->parent;  // 将y的父节点设置为x的父节点

        // 令 y 顶替 x 的位置, 将 x 挂到 y 的左子节点上
        if(x == root){
            root = y;
        }
        else if(x == x->parent->left){
            x->parent->left = y;
        }
        else{
            x->parent->right = y;
        }

        y->left = x;
        x->parent = y;
    }

    // 右旋操作
    inline void __rb_tree_rotate_right(__rb_tree_node_base* x, __rb_tree_node_base*& root){
        // 和左旋操作相反
#ifdef __JIANQIAO_DEBUG_RB_TREE__
        cout<<"right rotate"<<endl;
#endif

        // x 为旋转点
        __rb_tree_node_base* y = x->left;   // y 为旋转点的左子节点
        x->left = y->right; // 将y的右子节点挂到x的左子节点上
        if(y->right != nullptr){
            y->right->parent = x;    // 如果y的右子节点存在，则将其父节点设置为x
        }

        y->parent = x->parent;  // 将y的父节点设置为x的父节点

        // 令 y 顶替 x 的位置, 将 x 挂到 y 的右子节点上
        if(x == root){
            root = y;
        }
        else if(x == x->parent->right){
            x->parent->right = y;
        }
        else{
            x->parent->left = y;
        }

        y->right = x;
        x->parent = y;
    }

    inline void __rb_tree_rebalance(__rb_tree_node_base* x, __rb_tree_node_base* &root){
        // 先将新插入的节点设置为红色的节点
        x->color = __rb_tree_red;

        while(x != root && x->parent->color == __rb_tree_red){
            // 当这个节点不是根节点并且父节点是红色的时候（不能容纳连续两个红色这种情况出）
            if(x->parent == x->parent->parent->left){// 父节点为祖父节点的左子节点
                __rb_tree_node_base * y = x->parent->parent->right; // y 为伯父节点,也就是父节点的兄弟节点

                if(y && y->color == __rb_tree_red){
                    // 如果伯父节点存在并且为红色
                    // 将父节点和伯父节点都染黑
                    x->parent->color = __rb_tree_black;
                    y->color = __rb_tree_black;
                    // 将祖父节点染红
                    x->parent->parent->color = __rb_tree_red;

                    // 因为祖父节点红了，向上看看祖父节点是否出现了冲突，是否需要调整
                    x = x->parent->parent;
                }
                else{
                    // 如果伯父节点不存在或者为黑色
                    if(x == x->parent->right){  // 如果当前节点为父节点的右子节点
                        x = x->parent;
                        __rb_tree_rotate_left(x, root); // 以父节点为中心左旋
                    }
                    x->parent->color = __rb_tree_black; // 父节点染黑
                    x->parent->parent->color = __rb_tree_red;   // 祖父节点染红
                    __rb_tree_rotate_right(x->parent->parent, root);    // 以祖父节点为中心右旋
                }
            }
            else{
                __rb_tree_node_base* y = x->parent->parent->left;   // y 为伯父节点,也就是父节点的兄弟节点
                // 和前面的相当于是对称的操作
                if(y && y->color == __rb_tree_red){
                    // 如果伯父节点存在并且为红色
                    // 将父节点和伯父节点都染黑
                    x->parent->color = __rb_tree_black;
                    y->color = __rb_tree_black;
                    // 将祖父节点染红
                    x->parent->parent->color = __rb_tree_red;

                    // 因为祖父节点红了，向上看看祖父节点是否出现了冲突，是否需要调整
                    x = x->parent->parent;
                }
                else{
                    // 如果伯父节点不存在或者为黑色
                    if(x == x->parent->left){  // 如果当前节点为父节点的左子节点
                        x = x->parent;
                        __rb_tree_rotate_right(x, root); // 以父节点为中心右旋
                    }
                    x->parent->color = __rb_tree_black; // 父节点染黑
                    x->parent->parent->color = __rb_tree_red;   // 祖父节点染红
                    __rb_tree_rotate_left(x->parent->parent, root);    // 以祖父节点为中心左旋
                }

            }
        }// while

        root->color = __rb_tree_black; // 根节点染黑
    }




__JIANQIAO_END__

#endif //JIANQIAOSTL_JIANQIAO_RB_TREE_SUPPORT_HPP
