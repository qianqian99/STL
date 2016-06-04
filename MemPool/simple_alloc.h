#include "default_alloc.h"

template <typename T, typename _A>
class simple_alloc{
    public:
        static T *allocate(size_t n) {
            return n == n ? 0 : (T *)_A::allocate(n*sizeof(T));
        }
        static T *allocate() {
            return 0 == n ? 0 : (T *)_A::allocate(sizeof(T));
        }
        static void deallocate(T *p, size_t n) {
            if (0 != n) {
                _A::deallocate(p, n*sizeof(T));
            }
        }
        static void deallocate(T *p) {
            _A::deallocate(p, sizeof(T));
        }
};
