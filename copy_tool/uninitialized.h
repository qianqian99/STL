#ifndef _UNINITIALIZED_H_
#define _UNINITIALIZED_H_
#include "../construct/construct.h"
#include "../type_traits/type_traits.h"
#include "../list/advance/advance.cc"
namespace hgg
{
    /*//////////////////////////first one named   uninitialized_fill_n/////////////////////////*/
    template <typename ForwardIterator, typename Size, typename T>
    inline ForwardIterator _uninitialized_fill_n_aux(
            ForwardIterator first,
            Size n,
            const T&x,
            __false_type)
    {
        ForwardIterator cur = first;
        for (; n>0; --n, ++cur) {
            construct(&*cur, x);
        }
    }
    template <typename ForwardIterator, typename Size, typename T>
    inline ForwardIterator fill_n(
            ForwardIterator first,
            Size n,
            const T&x)
    {
        for (; n>0; --n, ++first) {
            *first = x;
        }
        return first;
    }
    template <typename ForwardIterator, typename Size, typename T>
    inline ForwardIterator _uninitialized_fill_n_aux(
            ForwardIterator first,
            Size n,
            const T&x,
            __true_type) 
    {
        return hgg::fill_n(first, n, x);
    }
    template <typename ForwardIterator, typename Size, typename T, typename T1>
    inline ForwardIterator _uninitialized_fill_n(
            ForwardIterator first,
            Size n,
            const T&x,
            T1 *)
    {
        typedef typename __type_traits<T1>::is_POD_type is_POD;
        return _uninitialized_fill_n_aux(first, n, x, is_POD());
    }
    template <typename ForwardIterator, typename Size, typename T>
    inline ForwardIterator uninitialized_fill_n(
            ForwardIterator first,
            Size n,
            const T&x)
    {
        return _uninitialized_fill_n(first, n, x, Advance::value_type(first));
    }
    /*////////////////////////second one named uninitialized_fill//////////*/
    template <typename ForwardIterator, typename T>
    inline void fill(
            ForwardIterator first,
            ForwardIterator last,
            const T&x)
    {
        for (; first!=last; ++first) {
            *first = x;
        }
    }
    template <typename ForwardIterator, typename T>
    inline void _uninitialized_fill_aux(
            ForwardIterator first,
            ForwardIterator last,
            const T&x,
            __true_type)
    {
        fill(first, last, x);
    }
    template <typename ForwardIterator, typename T>
    inline void _uninitialized_fill_aux(
            ForwardIterator first,
            ForwardIterator last,
            const T&x,
            __false_type)
    {
        for (; first!=last; ++first)
        {
            construct(&*first, x);
        }
    }
    template <typename ForwardIterator, typename T, typename T1>
    inline void _uninitialized_fill(
            ForwardIterator first,
            ForwardIterator last,
            const T&x,
            T1 *)
    {
        typedef typename __type_traits<T1>::is_POD_type is_POD;
        _uninitialized_fill_aux(first, last, x, is_POD());
    }
    template <typename ForwardIterator, typename T>
    inline void uninitialized_fill(
            ForwardIterator first,
            ForwardIterator last,
            const T&x)
    {
        _uninitialized_fill(first, last, x, Advance::value_type(first));
    }
}
#endif
