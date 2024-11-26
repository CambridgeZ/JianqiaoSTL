//
// Created by Mac on 24-11-26.
//

#ifndef JIANQIAOSTL_PRE_PERMUTATION_HPP
#define JIANQIAOSTL_PRE_PERMUTATION_HPP

#include "../config.hpp"
#include "../jianqiao_algorithm_base.hpp"
#include "../jianqiao_iterator.hpp"

__JIANQIAO_BEGIN__

template <class BidirectionalIterator>
bool prev_permutation(BidirectionalIterator first, BidirectionalIterator last){
    if(first == last){
        return false;
    }
    BidirectionalIterator i = last;
    if(first == --i){
        return false;
    }
    while(true){
        BidirectionalIterator i1 = i;
        if(*i1 < *--i){
            BidirectionalIterator i2 = last;
            while(!(*--i2 < *i));
            Jianqiao::iter_swap(i, i2);
            Jianqiao::reverse(i1, last);
            return true;
        }
        if(i == first){
            Jianqiao::reverse(first, last);
            return false;
        }
    }
}

template <class BidirectionalIterator, class Compare>
bool prev_permutation(BidirectionalIterator first, BidirectionalIterator last, Compare comp){
    if(first == last){
        return false;
    }
    BidirectionalIterator i = last;
    if(first == --i){
        return false;
    }
    while(true){
        BidirectionalIterator i1 = i;
        if(comp(*i, *--i)){
            BidirectionalIterator i2 = last;
            while(!comp(*--i2, *i));
            Jianqiao::iter_swap(i, i2);
            Jianqiao::reverse(i1, last);
            return true;
        }
        if(i == first){
            Jianqiao::reverse(first, last);
            return false;
        }
    }
}



__JIANQIAO_END__

#endif //JIANQIAOSTL_PRE_PERMUTATION_HPP
