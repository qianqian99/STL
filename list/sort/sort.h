#include "../splice/splice.h"
#include "../../functional/functional.h"
namespace hgg{
    template <typename Type>
    void swap(Type &left, Type &right) {
        Type tmp = left;
        left = right;
        right = tmp;
    }
    template <typename _BI, typename _F>
    void buble_sort(_BI first, _BI last, _F fun) {
        for (; first != last; ++first) {
            _BI min_it = first;
            for (_BI start=first; start!=last; ++start) {
                if (fun(*start, *min_it)) min_it = start;
            }
            swap(*min_it, *first);
        }
    }
}
