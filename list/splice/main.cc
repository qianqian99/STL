#include "splice.h"
template <typename _BI>
void show(_BI first, _BI last) {
    while (first != last)
    {
        std::cout << *first++ << " ";
    }
    std::cout << std::endl;
}
int main()
{
    int arr[10];
    for (int i=0; i<10; ++i) {
        arr[i] = rand() %20 +1;
    }
    int brr[10] = {12,23,34,45,56,67, 78,89,90,100};
    hgg::list<int> list1(arr, arr+10);
    hgg::list<int> list2(brr, brr+10);
    show(list1.begin(), list1.end());
    show(list2.begin(), list2.end());
    list1.splice(list1.begin(), list2, list2.begin());
    show(list1.begin(), list1.end());
    show(list2.begin(), list2.end());
    return 0;
}
