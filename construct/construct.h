#ifndef _CONSTRUCT_H_
#define _CONSTRUCT_H_
#include <new>
#include "../list/advance/advance.cc"
#include "../type_traits/type_traits.h"
namespace hgg
{
    template <typename T1, typename T2>
    inline T1 *construct(T1 *p, const T2 &x) {
        return new(p) T1(x);
    }
    template <typename T>
    void destory(T *pcur) {
        pcur->~T();
    }
    template <typename ForwardIterator>
    void _destory_aux(ForwardIterator first, ForwardIterator last, __true_type) {
        
    }
    template <typename ForwardIterator>
    void _destory_aux(ForwardIterator first, ForwardIterator last, __false_type) {
        for (; first != last; ++first) {
            destory(&*first);
        }
    }
    template <typename ForwardIterator, typename T>
    void _destory(ForwardIterator first, ForwardIterator last, T*) {
        typedef typename __type_traits<T>::has_trivial_destructor
            trivial_destructor;
        _destory_aux(first, last, trivial_destructor());
    }
    template <typename ForwardIterator>
    void destory(ForwardIterator first, ForwardIterator last) {
        _destory(first, last, Advance::value_type(first));
    }
}
#endif
