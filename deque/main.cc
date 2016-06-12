#include <iostream>
#include <algorithm>
template <typename Iterator>
void show(Iterator first, Iterator last) {
    for (; first != last; ++first) {
        std::cout << *first << " ";
    }
    std::cout << std::endl;
}
#if 0
#include "deque.h"
int main() {
    hgg::deque<int> queue(10, 4);
    queue.push_back(100);
    queue.push_back(100);
    queue.push_back(100);
    show(queue.begin(), queue.end());
    return 0;
}
#else
int main() {
    int array[9] = {1,2,3,4,5,6,7,8,9};
    const int len = sizeof(array)/sizeof(array[0]);
    int brray[9] = {};
    int crray[9] = {};
    show(array, array+len);
    std::copy(array+3, array+len, brray);
    show(brray, brray+len);
    std::copy_backward(array+3, array+len, crray+len);
    show(crray, crray+len);
    return 0;
}
#endif
