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
    /*
       每个大小是512/4= 128， 那么第一次是八个node
       可插入的元素是128×8=1024
    */
    hgg::deque<int> queue(0,0);
    for (int i=0; i<1024; ++i)
    queue.push_back(i);
    //show(queue.begin(), queue.end());
    for (int i=0; i<1024; ++i)
    queue.push_front(i);
  //  show(queue.begin(), queue.end());
    std::cout << queue.size() << std::endl; 
    return 0;
}
#else
#include <deque>
int main() {
    int array[] = {1,2,3,4,5};
    std::deque<int> queue(array, array+5);
    std::copy(queue.begin(), queue.end()-1, queue.begin()+1);
    show(queue.begin(), queue.end());
    return 0;
}
#endif
