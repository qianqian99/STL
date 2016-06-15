#ifndef _UNINITIALIZED_H_
#define _UNINITIALIZED_H_
#include "../construct/construct.h"
#include "../type_traits/type_traits.h"
#include "../list/advance/advance.cc"
#include <cstring>
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
    ///////////////////////////// uninitialized_copy //////////////////
    /*特化版本， 需要知道函数没有偏特化*/
    /*特化与重载的区别：对传入的参数有限制， 重载可以是最传入的参数加上限制*/
   
    template <typename InputIterator, typename ForwardIterator>
    ForwardIterator _uninitialized_copy_aux
    (InputIterator first, InputIterator last,
     ForwardIterator dest, __true_type)
    {
        return std::copy(first, last, dest);
    }
    template <typename InputIterator, typename ForwardIterator>
    ForwardIterator _uninitialized_copy_aux
    (InputIterator first, InputIterator last,
     ForwardIterator dest, __false_type)
    {
        ForwardIterator res = dest;
        for (; first != last; ++first, ++dest) {
            construct(&*dest, *first);
        }
        return res;
    }
    template <typename InputIterator, typename ForwardIterator, typename T>
    ForwardIterator _uninitialized_copy
    (InputIterator first, InputIterator last,
     ForwardIterator dest, T *)
    {
        typedef typename  __type_traits<T>::is_POD_type is_POD;
        return _uninitialized_copy_aux(first, last, dest, is_POD());
    }
    template <typename InputIterator, typename ForwardIterator>
    ForwardIterator uninitialized_copy
    (InputIterator first, InputIterator last,
    ForwardIterator dest)
    {
        return _uninitialized_copy(first, last, dest, Advance::value_type(first));
    }
    template <>
    char *uninitialized_copy
    (const char *first, const char *last, char *dest)
    {
        memmove(dest, first, last-first);
        return dest + (last - first);
    }
}
#endif
