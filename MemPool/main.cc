#include "default_alloc.h"
int main(){
    for (size_t i=0; i<129; ++i) {
        std::cout << second_allocator::Index(i) << std::endl;
    }
    return 0;
}
