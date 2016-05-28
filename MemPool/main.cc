#include "malloc_alloc.h"
int main(){
    void *p = __malloc_alloc_template<10>::allocate(sizeof(int));
    void *r = __malloc_alloc_template<10>::reallocate(p, sizeof(int), sizeof(int)*2);
    return 0;
}
