#include "malloc_alloc.h"
const int MinBlock = 8;
const int MaxBlock = 128;
const int Num = 16;
template <int inst>
class __default_alloc_template {
    private:
        static size_t Round_up(size_t sz) {
            /*      sz + 7 & 111111111000*/
            return (sz + MinBlock -1) & ~(MinBlock-1);
        }
        static Index(size_t sz) {
            return (sz + MinBlock - 1) >> 3;
        }
        union obj {
            union obj * free_list_link;
            char *client[1];
        };
        static obj *volatile free_list[Num];
        static void *refill(size_t n);
        static char *chunk_alloc(size_t size, int &nobjs);

        static char *start_free;
        static char *end_free;
        static size_t heap_size;
    public:
        static void *allocate(size_t n);
        static void *reallocate(void *p, size_t old_sz, size_t new_sz);
        static void deallocate(void *p, size_t size);
};
template <int inst>
char *__default_alloc_template<inst>::start_free = 0;
template <int inst>
char *__default_alloc_template<inst>::end_free = 0;
template <int inst>
int *__default_alloc_template<inst>::heap_size = 0;
template <int inst> 
__default_alloc_template<inst>::obj 
*volatile __default_alloc_template<inst>::free_list[Num];
template <int inst>
static void *__default_alloc_template<inst>::allocate(size_t sz) {
    obj *
}
