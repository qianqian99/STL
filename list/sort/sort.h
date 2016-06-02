#include "../splice/splice.h"
#include "../../functional/functional.h"
#include "../advance/advance.cc"
namespace hgg{
    template <typename Type>
    void swap(Type &left, Type &right) {
        Type tmp = left;
        left = right;
        right = tmp;
    }
    template <typename _BI, typename _F>
    void choose_sort(_BI first, _BI last, _F fun) {
        for (; first != last; ++first) {
            _BI min_it = first;
            for (_BI start=first; start!=last; ++start) {
                if (fun(*start, *min_it)) min_it = start;
            }
            swap(*min_it, *first);
        }
    }
    template <typename _BI, typename _F>
    void buble_sort(_BI first, _BI last, _F fun) {
        _BI tail = --last;
        for (_BI start=first; start!=last; ++start, --tail) {    //control circle time
            for (_BI head=first; head!=tail;) {
                _BI prev = head++;
                if (fun(*prev, *head)) swap(*prev, *head);
            }
        }
    }
    template <typename _BI>
    typename _BI::difference_type distance(_BI first, _BI last) {
        _BI::difference_type i = 0;
        while (first != last) {
            ++first;
            ++i;
        }
        return i;
    }

    template <typename _BI>
    void merge(_BI _F1, _BI L1, _BI F2, _BI L2) {
        while (_F1 != _L1 && _F2 != _L2) {
            if (*_F2 < *_F1) {
                iterator _M = _F2++;
                transfer(_F1, _M, _F2);
            }
            else ++_F1;
        }
        if (_F2 != _L2) {
            transfer(end(), _F2, _L2);
        }
    }
    template <typename _Con, typename _F>
    void merge_sort(_Con &container, _F fun) {
        typedef  typename _Con::iterator::difference_type diff_type;
        typedef typename _Con::iterator iterator;
        diff_type size = advance(container.begin(), container.end());
        _Con _X;
        diff_type s = 1;
        iterator _L = container.end();
        while (s < size) {
            advance(_L, s);
            merge(_X.begin(), _X.end(), container.begin(), _L);
            s += s;
            
            _L = container.begin();
            advance(_L, s);
            merge(container.begin(), _L, _X.begin(), _X.end());
            s += s;
        }

        //10 8, 9, 12, 234, 23
        //_X                   
        //container  8 9 10 12 234 23
    }
}
