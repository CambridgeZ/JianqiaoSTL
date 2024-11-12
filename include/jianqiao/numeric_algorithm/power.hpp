//
// Created by Mac on 24-11-12.
//

#ifndef JIANQIAOSTL_POWER_HPP
#define JIANQIAOSTL_POWER_HPP

#include "../config.hpp"
#include "../jianqiao_function.hpp"

__JIANQIAO_BEGIN__

template <typename T, typename Integer>
T power(T x, Integer n){
    if(n == 0){
        return 1;
    }else{
        while((n & 1) == 0){
            // 如果是2的倍数，那么就将x平方，n除以2
            n >>= 1;
            x *= x;
        }
        T result = x;
        n >>= 1;
        while(n != 0){
            x *= x;
            if((n & 1) != 0){
                result *= x;
            }
            n >>= 1;
        }
        return result;
    }
}

template <typename T, typename Integer, typename MonoidOperation>
T power(T x, Integer n, MonoidOperation op){
    if(n == 0){
        return identity_element(op);
    }else{
        while((n & 1) == 0){
            n >>= 1;
            x = op(x, x);
        }
        T result = x;
        n >>= 1;
        while(n != 0){
            x = op(x, x);
            if((n & 1) != 0){
                result = op(result, x);
            }
            n >>= 1;
        }
        return result;
    }
}

__JIANQIAO_END__
#endif //JIANQIAOSTL_POWER_HPP
