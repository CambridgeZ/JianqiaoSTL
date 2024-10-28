//
// Created by Mac on 24-10-28.
//

#ifndef JIANQIAOSTL_JIANQIAO_PRIORITY_QUEUE_HPP
#define JIANQIAOSTL_JIANQIAO_PRIORITY_QUEUE_HPP

#include "jianqiao_vector.hpp"
#include "heap_base.hpp"

__JIANQIAO_BEGIN__

template <class T, class Sequence = Jianqiao::vector<T>,
        class Compare = std::less<typename Sequence::value_type> >
class priority_queue{
public:
    using value_type = typename Sequence::value_type;
    using size_type = typename Sequence::size_type;
    using reference = typename Sequence::reference;
    using const_reference = typename Sequence::const_reference;
protected:
    Sequence c;
    Compare comp;
public:
    priority_queue(): c(){}
    explicit priority_queue(const Compare& x): c(), comp(x) {}

    template<class InputIterator>
    priority_queue(InputIterator first, InputIterator last, const Compare& x):c(first,last),comp(x){
        make_heap(c.begin(), c.end(), comp);
    }

    template<class InputIterator>
    priority_queue(InputIterator first, InputIterator last): c(first,last){
        make_heap(c.begin(),c.end(), comp);
    }

    bool empty() const {
        return c.empty();
    }

    size_type size() const {
        return c.size();
    }

    const value_type& top() const{
        return c.front();
    }

    void push(const value_type& x){
        try{
            c.push_back(x);
            push_heap(c.begin(), c.end(), comp);
        }
        catch (...){
            c.clear();
            throw;
        }
    }

    void pop(){
        try{
            pop_heap(c.begin(), c.end(), comp);
            c.pop_back();
        }
        catch (...){
            c.clear();
            throw ;
        }
    }

};

__JIANQIAO_END__


#endif //JIANQIAOSTL_JIANQIAO_PRIORITY_QUEUE_HPP
