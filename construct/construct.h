#ifndef _CONSTRUCT_H_
#define _CONSTRUCT_H_
#include <new>
namespace hgg
{
    template <typename T1, typename T2>
    inline T1 *construct(T1 *p, const T2 &x) {
        return new(p) T1(x);
    }
}
#endif
