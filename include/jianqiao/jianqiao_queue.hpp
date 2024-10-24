#ifndef __JIANQIAO_QUEUE_HPP__
#define __JIANQIAO_QUEUE_HPP__


#include "config.hpp"
#include <deque>

__JIANQIAO_BEGIN__

template<typename T, typename Sequenece = std::deque<T> >
class queue{
    // friend bool operator == <> (const queue&, const queue&);
    // friend bool operator < <> (const queue& , const queue &);
protected:
    Sequenece S;
public:
    using value_type = typename Sequenece::value_type;
    using size_type = typename Sequenece::size_type;
    using reference = typename Sequenece::reference;
    using const_reference = typename Sequenece::const_reference;
public:
    bool empty() const {return S.empty();};
    void push(const value_type &elem) {S.push_back(elem);}
    void pop() {S.pop_front();}
    reference front() {return S.front();}
    const_reference front() const { return S.front(); }
};

template<typename T, typename Sequenece = std::deque<T> >
bool operator == (const queue<T, Sequenece>& lhs, const queue<T, Sequenece>& rhs){
    return lhs.S == rhs.S;
}

template<typename T, typename Sequenece = std::deque<T> >
bool operator < (const queue<T, Sequenece>& lhs, const queue<T, Sequenece>& rhs){
    return lhs.S < rhs.S;
}




__JIANQIAO_END__


#endif // __JIANQIAO_QUEUE_HPP__