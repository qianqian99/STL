#include "default_alloc.h"
#include <unistd.h>
int main(){
    for (int i=0; i<20240000; ++i) {
        size_t all = rand()%250 +1;
        malloc(all);
    }
    printf("finish\n");
    sleep(100);
    return 0;
}
