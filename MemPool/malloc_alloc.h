#include <cstdio>
#include <cstdlib>
#if 0
#include <new>
#define __THROW_BAD_ALLOC throw std::bad_alloc
#elif !defined(__THROW_BAD_ALLOC)
#include <iostream>
#define __THROW_BAD_ALLOC std::cerr<<"out of memory"<<std::endl; exit(-1)
#endif
class __malloc_alloc_template {
    private:
        static void *oom_malloc(size_t);
        static void *oom_realloc(void *, size_t);
        static void (*__malloc_alloc_oom_handler)();
    public:
        /*the API which can be used by others*/
        static void *allocate(size_t n) {
            void *result = malloc(n);
            if (NULL == result) return  oom_malloc(n);
            return result;
        }
        static void deallocate(void *p, size_t ) {
            free(p);
        }
        static void *reallocate(void *p, size_t old_sz, size_t new_sz) {
            void *result = realloc(p, new_sz);
            if (NULL == result) result = oom_realloc(p, new_sz);
            return result;
        }
        typedef void(*PFun)();
        static PFun set_malloc_handler(PFun f) {
            PFun old = __malloc_alloc_oom_handler;
            __malloc_alloc_oom_handler = f;
            return old;
        }
};
void (*__malloc_alloc_template::__malloc_alloc_oom_handler)() = NULL;
void *__malloc_alloc_template::oom_malloc(size_t n) {
    PFun my_malloc_handler;
    void *result;
    for (;;) {
        my_malloc_handler = __malloc_alloc_oom_handler;
        if (NULL == my_malloc_handler) {__THROW_BAD_ALLOC;}
        (*my_malloc_handler)();
        result = malloc(n);
        if (NULL != result) return result;
    }
}
void *__malloc_alloc_template::oom_realloc(void *p, size_t sz) {
    PFun my_malloc_handler;
    void * result;
    for(;;) {
        my_malloc_handler = __malloc_alloc_oom_handler;
        if (NULL == my_malloc_handler) {__THROW_BAD_ALLOC;}
        (*my_malloc_handler)();
        result = realloc(p, sz);
        if (NULL != result) return result;
    }
}
typedef __malloc_alloc_template first_allocator;
