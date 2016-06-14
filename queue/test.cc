#include "queue.h"
#include <iostream>
int main (){
    hgg::queue<int> qu;
    for (int i=0; i<1024; ++i) {
        qu.push(i);
    }
    for(int i=0; i<1024; ++i) {
        std::cout << qu.front() << " ";
        qu.pop();
    }
    std::cout << std::endl;
    return 0;
}
