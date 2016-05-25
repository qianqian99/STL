#include "sort.h"
template <typename _II>
void show(_II first, _II last) {
    for (; first != last; ++first) {
        std::cout << *first << " ";
    }
    std::cout << std::endl;
}
int main() {
    int arr[10];
    for (int i=0; i<10; ++i) {
        arr[i] = rand() % 100 +1;
    }
    hgg::list<int> list1(arr, arr+10);
    show(list1.begin(), list1.end());
    buble_sort(list1.begin(), list1.end(), hgg::greater<int>());
    show(list1.begin(), list1.end());
}
