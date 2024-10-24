#ifndef __JIANQIAO_STACK_HPP__
#define __JIANQIAO_STACK_HPP__

#include "config.hpp"
#include <deque>

__JIANQIAO_BEGIN__

template <typename T, typename Sequence = std::deque<T> >
class stack{
    // friend bool operator == <> (const stack& x, const stack& y);
    // friend bool operator < <> (const stack&, const stack&);
public:
    using value_type = typename Sequence::value_type;
    using size_type = typename Sequence::size_type;
    using reference = typename Sequence::reference;
    using const_reference = typename Sequence::const_reference;

protected:
    Sequence c;
public:
    bool empty() const { return c.empty(); }
    size_type size() const { return c.size(); }
    reference top() { return c.back(); }
    const_reference top() const { return c.back(); }
    void push(const value_type& x) { c.push_back(x); }
    void pop() { c.pop_back(); }
};

template <typename T, typename Sequence>
bool operator == (const stack<T, Sequence>& x, const stack<T, Sequence>& y){
    return x.c == y.c;
}

template <typename T, typename Sequence>
bool operator < (const stack<T, Sequence>& x, const stack<T, Sequence>& y){
    return x.c < y.c;
}
__JIANQIAO_END__


#endif // __JIANQIAO_STACK_HPP__