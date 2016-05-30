#include "malloc_alloc.h"
const int MinBlock = 8;
const int MaxBlock = 128;
const int Num = 16;
class __default_alloc_template {
    public:
        static size_t Round_up(size_t sz) {
            /*      sz + 7 & 111111111000*/
            return (sz + MinBlock -1) & ~(MinBlock-1);
        }
        static int Index(size_t sz) {
            return ((sz + MinBlock - 1) >> 3) - 1;
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
char *__default_alloc_template::start_free = 0;
char *__default_alloc_template::end_free = 0;
size_t __default_alloc_template::heap_size = 0;
typename __default_alloc_template::obj 
*volatile __default_alloc_template::free_list[Num];
void *__default_alloc_template::allocate(size_t sz) {
    obj *result;
    if (sz > (size_t)MaxBlock) {
        return __malloc_alloc_template::allocate(sz);
    }
    obj *volatile *my_free_list = free_list + Index(sz);
}
typedef __default_alloc_template second_allocator;
