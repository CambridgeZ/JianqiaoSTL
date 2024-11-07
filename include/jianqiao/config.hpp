// namspace Jianqiao
#pragma once

#include <cstddef>
#define __JIANQIAO_BEGIN__ namespace Jianqiao{
#define __JIANQIAO_END__ } //namespace Jianqiao

using std::ptrdiff_t;

#define JIANQIAO_SELF_MEMORY_CONTROL
#define USE_DEQUE 0


#if USE_DEQUE == 0 
#include <deque>
#endif

#define USE_JIANQIAO_ALLOC 1
