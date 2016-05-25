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
    template <typename _BI, typename _F>
    void merge_sort(_BI first, _BI last, _F fun) {
        _BI::difference_type size = distance(first, last);
        int s = 1;
        while (s<size) {
            _BI next = first;
        }
    }
}
