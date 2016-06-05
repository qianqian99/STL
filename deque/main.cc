#include <iostream>
#include "deque.h"
template <typename Iterator>
void show(Iterator first, Iterator last) {
    for (; first != last; ++first) {
        std::cout << *first << " ";
    }
    std::cout << std::endl;
}
int main() {
    hgg::deque<int> queue(10, 4);
    show(queue.begin(), queue.end());
    return 0;
}
