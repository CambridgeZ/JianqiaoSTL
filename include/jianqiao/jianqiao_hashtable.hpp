//
// Created by Mac on 24-11-9.
//

#ifndef JIANQIAOSTL_JIANQIAO_HASHTABLE_HPP
#define JIANQIAOSTL_JIANQIAO_HASHTABLE_HPP

#include "config.hpp"
#include "jianqiao_hashtable_support.hpp"
#include "alloc.hpp"
#include "jianqiao_vector.hpp"
#include "jianqiao_pair.hpp"

__JIANQIAO_BEGIN__

static const int __stl_num_primes = 28;
static const unsigned long __stl_prime_list[__stl_num_primes] = {
        53, 97, 193, 389, 769,
        1543, 3079, 6151, 12289, 24593,
        49157, 98317, 196613, 393241, 786433,
        1572869, 3145739, 6291469, 12582917, 25165843,
        50331653, 100663319, 201326611, 402653189, 805306457,
        1610612741, 3221225473ul, 4294967291ul
};

template <class Value, class Key,
        class HashFcn, class ExtractKey, class EqualKey, class Alloc = allocator<__hashtable_node<Value> > >
class hashtable{
    friend struct __hashtable_iterator<int, Key, HashFcn, ExtractKey, EqualKey, Alloc>;
    friend struct __hashtable_const_iterator<int, Key, HashFcn, ExtractKey, EqualKey, Alloc>;
    friend struct __hashtable_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>;
    friend struct __hashtable_const_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>;
public:
    using hasher = HashFcn;
    using key_equal = EqualKey;
    using size_type = size_t;
    using value_type = Value;
    using key_type = Key;
    using iterator = __hashtable_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>;
    using difference_type = ptrdiff_t;
    using const_iterator = __hashtable_const_iterator<Value, Key, HashFcn, ExtractKey, EqualKey, Alloc>;
    using const_pointer = const Value*;
    using const_reference = const Value&;
    using pointer = Value*;
    using reference = Value&;

private:
    hasher hash;
    key_equal equals;
    ExtractKey get_key;

    using node = __hashtable_node<Value>;
    using node_allocator = simple_alloc<node, Alloc>;

//    vector<node*, Alloc> buckets;
    vector<node*> buckets;
    size_type num_elements;

public:
    // 痛的个数的大小
    size_type bucket_count() const { return buckets.size(); }
    // 返回桶的大小
    size_type max_bucket_count() const { return __stl_prime_list[__stl_num_primes - 1]; }

    node* new_node(const value_type& obj){
        node* n = node_allocator::allocate();
        n->next = nullptr;
        try{
            construct(&n->val, obj);
            return n;
        }
        catch(...){
            node_allocator::deallocate(n);
        }
        return n;
    }

    void delete_node(node* n){
        destroy(&n->val);
        node_allocator::deallocate(n);
    }

    hashtable(size_type n, const HashFcn& hf, const EqualKey& eql):
        hash(hf), equals(eql), get_key(ExtractKey()), num_elements(0){
        initialize_buckets(n);
    }

    void initialize_buckets(size_type n){
        const size_type n_buckets = next_size(n);

        // 分配n_bucket个桶
        buckets.reserve(n_buckets);
        buckets.insert(buckets.end(), n_buckets, (node*)0);
        num_elements = 0;
    }

    size_type next_size(size_type n) const{
        // 返回__stl_prime_list中第一个大于n的值
        for(int i = 0; i < __stl_num_primes; ++i){
            if(__stl_prime_list[i] > n){
                return __stl_prime_list[i];
            }
        }
        return __stl_prime_list[__stl_num_primes - 1];
    }

    size_type size() const {
        return num_elements;
    }

    pair<iterator, bool> insert_unique(const value_type& obj){
        // 判断是否
        resize(num_elements + 1);
        return insert_unique_noresize(obj);
    }

    void resize(size_type num_elements_hint){
        const size_type old_n = buckets.size();// 旧的桶的个数
        if(num_elements_hint > old_n){
            const size_type n = next_size(num_elements_hint);
            if(n > old_n){
                vector<node*> tmp(n, (node*)0);
                for(size_type bucket = 0; bucket < old_n; ++bucket){
                    // 遍历每一个桶
                    node* first = buckets[bucket];
                    while(first){
                        // 遍历每一个桶中的链表
                        size_type new_bucket = bkt_num(first->val, n);
                        // 令旧桶的下一个元素为当前元素
                        buckets[bucket] = first->next;
                        // 令当前元素的下一个元素为新桶的第一个元素
                        first->next = tmp[new_bucket];
                        // 令新桶的第一个元素为当前元素
                        tmp[new_bucket] = first;
                        // 令当前元素为旧桶的下一个元素
                        first = buckets[bucket];
                    }
                }
                // 交换buckets
                buckets.swap(tmp);
            }
        }
    }

    void resize(size_type num_elements_hint, const hasher& hf){
        hash = hf;
        resize(num_elements_hint);
    }

    //swap
    void swap(hashtable& ht){
        buckets.swap(ht.buckets);
        std::swap(num_elements, ht.num_elements);
    }

    pair<iterator, bool> insert_unique_noresize(const value_type& obj){
        // 在不需要重建表格的情况下进行元素的插入
        const size_type n = bkt_num(obj); // 获取obj的hash值
        node* first = buckets[n];   // 获取第n个桶的第一个元素
        for(node* cur = first; cur; cur = cur->next){
            if(equals(get_key(cur->val), get_key(obj))){
                // 如果发现其中有键值和当前的相同，就不插入
                return pair<iterator, bool>(iterator(cur, this), false);
            }
        }
        node* tmp = new_node(obj);
        tmp->next = first;
        buckets[n] = tmp;
        ++num_elements;
        return pair<iterator, bool>(iterator(tmp, this), true);
    }


    // bkt_num 根据键值获取hash值
    size_type bkt_num(const value_type& obj, size_t n) const {
        return bkt_num_key(get_key(obj), n);
    }

    size_type bkt_num(const value_type& obj) const {
        return bkt_num_key(get_key(obj));
    }

    // bkt_num_key: 根据键值获取hash值
    size_type bkt_num_key(const key_type& key, size_t n) const {
        return hash(key) % n;
    }

    size_type bkt_num_key(const key_type& key) const {
        return bkt_num_key(key, buckets.size());
    }

    iterator insert_equal(const value_type& obj){
        resize(num_elements + 1);
        return insert_equal_noresize(obj);
    }

    iterator insert_equal_noresize(const value_type& obj){
        // 允许相等的情况下，在不需要表格的时候
        const size_type n = bkt_num(obj);
        node* first = buckets[n];
        for(node* cur = first; cur; cur = cur->next){
            if(equals(get_key(cur->val), get_key(obj))){
                // 如果发现有键值相同的，就马上插入然后返回
                node* tmp = new_node(obj);
                tmp->next = cur->next;
                cur->next = tmp;
                ++num_elements;
                return iterator(tmp, this);
            }
        }
        node* tmp = new_node(obj);
        tmp->next = first;
        buckets[n] = tmp;
        ++num_elements;
        return iterator(tmp, this);
    }

    void clear(){
        for(size_type i=0; i< buckets.size();i++){
            node* cur = buckets[i];
            while(cur != 0){
                node* next = cur->next;
                delete_node(cur);
                cur = next;
            }
            buckets[i] = 0;
        }
        num_elements = 0;
    }

    void copy_from(const hashtable& ht){
        // 判断ht不是自己
        if(ht.buckets == this->buckets){
            return ;
        }

        this->buckets.clear();
        buckets.reserve(ht.buckets.size());
        // 向自己的bucket的尾端插入n个nullptr 元素

        buckets.insert(buckets.end(), ht.buckets.size(), nullptr);

        try{
            // 对于里面的节点进行复制相关的操作

            for(size_type i = 0; i<ht.buckets.size() ; i++){
                // 复制vector 的每一个元素，每一个指针及其指向的链表里面的东西
                if(const node* cur = ht.buckets[i]){
                    // 对于每个不为空的桶进行操作

                    node* copy = new_node(cur->val);
                    buckets[i] = copy;

                    while(cur->next){
                        copy->next = new_node(cur->val);
                        copy = copy->next;
                        cur = cur->nextl;
                    }
                }
            }

            num_elements = ht.num_elements;
        }
        catch(...){
            clear();
        }
    }

public:
    iterator end() {
        return iterator(nullptr, this);
    }

    iterator begin(){
        for(size_type i = 0; i < buckets.size(); ++i){
            if(buckets[i]){
                return iterator(buckets[i], this);
            }
        }
        return end();
    }

//    iterator find(const value_type& k){
//        /*
//         * 确定在哪个bucket当中，然后遍历这个bucket当中的链表
//         */
//        size_type n = bkt_num(k);
//        node* first;
//        for(first = buckets[n]; first && !equals(get_key(first->val), get_key(k)); first = first->next){
//            // 什么都不做
//        }
//        return iterator(first, this);
//    }

    iterator find(const key_type& k){
        /*
         * 确定在哪个bucket当中，然后遍历这个bucket当中的链表
         */
        size_type n = bkt_num_key(k);
        node* first;
        for(first = buckets[n]; first && !equals(get_key(first->val), k); first = first->next){
            // 什么都不做
        }
        return iterator(first, this);
    }

    size_type  count(const value_type &k){
        /*
         * 确定在哪个bucket当中，然后便利这个bucket当中的链表进行查找
         */
        const size_type n = bkt_num(k);
        size_type result = 0;
        for(const node* cur = buckets[n]; cur; cur = cur->next){
            if(equals(get_key(cur->val), get_key(k))){
                ++result;
            }
        }
        return result;
    }

    ~hashtable(){
        clear();
    }

    // erase 的各种实现

    void erase(const key_type& key) {
        // 删除hash_table 当中所有关键字为key的元素

        size_type n = bkt_num_key(key);
        node* first = buckets[n];
        if(first){
            // 如果对应的所在的桶是有元素的
            while(equals(get_key(first->val), key)){
                // 如果第一个元素就是要删除的元素
                node* next = first->next;
                delete_node(first);
                first = next;
                buckets[n] = first;
                --num_elements;
                if(!first){
                    return ;
                }
            }

            node* cur = first;
            node* next = cur->next;

            while(next){
                // 遍历桶提供的链表，然后看看链表里面是否有对应的元素
                if(equals(get_key(next->val), key)){
                    cur->next = next->next;
                    delete_node(next);
                    next = cur->next;
                    --num_elements;
                }
                else{
                    cur = next;
                    next = cur->next;
                }
            }
        }

    }

    void erase(iterator it){
        // 删除it所指向的元素
        node* p = it.cur;
        if(p){
            // 在链表当中找到对应的节点并对节点实行删除操作
            size_type n = bkt_num(p->val);
            node* cur = buckets[n];
            if(cur == p){
                buckets[n] = cur->next;
                delete_node(cur);
                --num_elements;
            }
            else{
                node* next = cur->next;
                while(next){
                    if(next == p){
                        cur->next = next->next;
                        delete_node(next);
                        --num_elements;
                        break;
                    }
                    else{
                        cur = next;
                        next = cur->next;
                    }
                }
            }
        }
    }

    void erase(iterator begin, iterator end){
        // 删除begin 到 end 之间的元素

        // 分别计算begin 和 end 所在的桶的位置
        size_type first_bucket = begin.cur ? bkt_num(begin.cur->val) : buckets.size();
        size_type last_bucket = end.cur ? bkt_num(end.cur->val) : buckets.size();
        if(begin.cur == end.cur){
            // 如果两个直接就是一个元素，也就是说需要删除的是一个空去见
            return ;
        }
        else if(first_bucket == last_bucket){
            // 两个不是一个元素，但是在一个桶当中
            erase_bucket(first_bucket, begin.cur, end.cur);
        }
        else{
            erase_bucket(first_bucket, begin.cur, 0);
            for(size_type n = first_bucket + 1; n < last_bucket; ++n){
                erase_bucket(n, 0);
            }
            if(last_bucket != buckets.size()){
                erase_bucket(last_bucket, end.cur);
            }
        }
    }

    void erase_bucket(size_type n, node* first, node* last){
        // 删除桶n当中的first 到 last 之间的元素
        node* cur = buckets[n];
        if(cur == first){
            erase_bucket(n, last);
        }
        else{
            node* next;
            for(next = cur->next; next != first; cur = next, next = cur->next){
                // 什么都不做
            }
            while(next != last){
                cur->next = next->next;
                delete_node(next);
                next = cur->next;
                --num_elements;
            }
        }
    }

    void erase_bucket(size_type n, node* last){
        // 删除last 之前的所有元素
        node* cur = buckets[n];
        while(cur != last){
            node* next = cur->next;
            delete_node(cur);
            cur = next;
            buckets[n] = cur;
            --num_elements;
        }
    }

    pair<iterator, iterator> equal_range(const value_type& obj){
        // 返回一个pair，pair的第一个元素是一个迭代器，指向第一个等于obj的元素
        // pair的第二个元素是一个迭代器，指向最后一个等于obj的元素的下一个元素
        const size_type n = bkt_num(obj);
        node* first;
        for(first = buckets[n]; first && !equals(get_key(first->val), get_key(obj)); first = first->next){
            // 什么都不做
        }
        if(first){
            node* last = first;
            while(last->next && equals(get_key(last->next->val), get_key(obj))){
                last = last->next;
            }
            return pair<iterator, iterator>(iterator(first, this), iterator(last, this));
        }
        else{
            return pair<iterator, iterator>(iterator(nullptr, this), iterator(nullptr, this));
        }
    }

    pair<const_iterator , const_iterator > equal_range (const value_type& obj) const{
        const size_type n = bkt_num(obj);
        const node* first;
        for(first = buckets[n]; first && !equals(get_key(first->val), get_key(obj)); first = first->next){
            // 什么都不做
        }

        if(first){
            const node* last = first;
            while(last->next && equals(get_key(last->next->val), get_key(obj))){
                last = last->next;
            }
            return pair<const_iterator, const_iterator>(const_iterator(first, this), const_iterator(last, this));
        }
        else{
            return pair<const_iterator, const_iterator>(const_iterator(nullptr, this), const_iterator(nullptr, this));
        }
    }

    // find_or_insert
    reference find_or_insert(const value_type& obj){
        size_type n = bkt_num(obj);
        node* first = buckets[n];
        for(node* cur = first; cur; cur = cur->next){
            if(equals(get_key(cur->val), get_key(obj))){
                // 如果发现有键值相同的，就返回
                return cur->val;
            }
        }
        // 如果没有找到对应的元素，就插入
        resize(num_elements + 1);
        node* tmp = new_node(obj);
        tmp->next = first;
        buckets[n] = tmp;
        ++num_elements;
        return tmp->val;
    }


};



__JIANQIAO_END__

#endif //JIANQIAOSTL_JIANQIAO_HASHTABLE_HPP
