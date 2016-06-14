#include "malloc_alloc.h"
#include <string.h>
const int MinBlock = 8;
const int MaxBlock = 128;
const int Num = 16;
const int Nobj = 20;
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
__default_alloc_template::obj 
*volatile __default_alloc_template::free_list[Num];
void *__default_alloc_template::allocate(size_t sz) {
    if (sz > (size_t)MaxBlock) {
        return __malloc_alloc_template::allocate(sz);
    }
    obj *volatile *my_free_list = free_list + Index(sz);
    obj *result = *my_free_list;
    if (result == NULL) {
        return refill(Round_up(sz));
    }
    *my_free_list = result->free_list_link;
    return result;
}
void *__default_alloc_template::refill(size_t size) {
    int nobj = Nobj;
    char * chunk = chunk_alloc(size, nobj);   // nobj pass by reference
    if (1 == nobj) {
        return chunk;
    }
    /*nobj > 1 , we should link the list, and return the chunk*/
    obj *result = (obj *)chunk;   // get the return pointer
    obj * volatile *my_free_list = free_list + Index(size);
    obj * current = NULL, *next = NULL;
    next = *my_free_list = (obj *)(chunk+size);
    for (int i=1; ; ++i) {
        current = next;
        next = (obj *)(((char*)next) + size);   // not the size of sizeof(obj);
        if (nobj-1 == i) {
            current->free_list_link = NULL;
            break;
        }
        else {
            current->free_list_link = next;
        }
    }
    return result;
}
char *__default_alloc_template::chunk_alloc(size_t size, int &nobj) {
    size_t left_space = end_free - start_free;
    size_t need_space = size*nobj;
    if (left_space < need_space) {
        /*one obj size*/
        if (left_space < size) {
            size_t space_to_get = 2*need_space + Round_up(heap_size>>4);
            if (left_space > 0) {
                /*left space head insert*/
                obj*volatile *my_free_list = free_list + Index(left_space);
                ((obj *)start_free)->free_list_link = *my_free_list;
                *my_free_list = (obj *)start_free;
            }
            start_free = (char *)malloc(space_to_get);
            if (start_free == NULL) {
                /*malloc fail, we need use from free_list*/
                obj* volatile * my_free_list = free_list;
                int i = Index(size) + 1;
                int sz = size + MinBlock;
                for (; i<Num; ++i, sz+=MinBlock) {
                    if (my_free_list[i] != NULL) {
                        start_free = (char *)my_free_list[i];
                        my_free_list[i] = (my_free_list[i])->free_list_link;
                        end_free = start_free + sz;
                        return chunk_alloc(size, nobj);
                    }
                }
                start_free = (char *)first_allocator::allocate(space_to_get);
            }
            end_free = start_free + space_to_get;
            heap_size += space_to_get;
            return chunk_alloc(size, nobj);
        }
        else {
            nobj = left_space/size;
            need_space = nobj*size;
            char *res = start_free;
            start_free += need_space;
            return res;
        }
    }
    else {
        char *res = start_free;
        start_free += need_space;
        return res;
    }
}
void __default_alloc_template::deallocate(void *p, size_t size) {
    if (size > (size_t)MaxBlock) {
        first_allocator::deallocate(p, size);
        return;
    }
    if (p != NULL) {
        obj* volatile *my_free_list = free_list + Index(size);
        ((obj *)p)->free_list_link = *my_free_list;
        *my_free_list = (obj *)p;
    }
}
void *__default_alloc_template::reallocate(void *p, size_t old_size, size_t new_size) {
    if (Round_up(old_size) == Round_up(new_size)) {
        return p;
    }
    if (Round_up(old_size) > MaxBlock &&
        Round_up(new_size) > MaxBlock){
        return first_allocator::reallocate(p, old_size, new_size);
    }
    void *q = allocate(new_size); 
    size_t len = old_size > new_size ? new_size : old_size;
    memcpy(q, p, len);
    deallocate(p, old_size);
    return p;
}
typedef __default_alloc_template second_allocator;
