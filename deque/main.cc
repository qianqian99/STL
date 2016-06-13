#include <iostream>
#include <algorithm>
template <typename Iterator>
void show(Iterator first, Iterator last) {
    for (; first != last; ++first) {
        std::cout << *first << " ";
    }
    std::cout << std::endl;
}
#if 1
#include "deque.h"
int main() {
    /*
       每个大小是512/4= 128， 那么第一次是八个node
       可插入的元素是128×8=1024
    */
    hgg::deque<int> queue(0,0);
    for (int i=0; i<1024; ++i)
    queue.push_back(i);
    show(queue.begin(), queue.end());
    queue.push_front(100);
    //for (int i=0; i<1024; ++i)
    //queue.push_front(i);
    //show(queue.begin(), queue.end());
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
