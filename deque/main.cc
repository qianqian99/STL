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
    int arry[] = {1,2,3,4,5,6,7};
    hgg::deque<int> queue(10,3);
    for (int i=0; i<7; ++i) {
        queue.push_back(arry[i]);
    }
    for (int i=0; i<10; ++i) {
        queue.erase(queue.begin()+i);
        show(queue.begin(), queue.end());
    }
    return 0;
}
#else
#include <deque>
int main() {
    int array[] = {1,2,3,4,5, 7, 8, 9};
    std::deque<int> queue(array, array+8);
    // std::copy(queue.begin(), queue.end()-1, queue.begin()+1);
    queue.insert(queue.begin()+3, 1000);
    show(queue.begin(), queue.end());
    return 0;
}
#endif
