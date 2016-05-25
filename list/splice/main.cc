#include "splice.h"
#include "../../functional/functional.h"
#include <list>
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
    int arr[10] = {3,4,5,6,8,9,100,101,123,144};
    int brr[5] = {7,12,14,15,18};
    hgg::list<int> list1(arr, arr+10);
    hgg::list<int> list2(brr, brr+5);
    show(list1.begin(), list1.end());
    show(list2.begin(), list2.end());
    list1.merge(list2);
    list1.swap(list2);
    show(list1.begin(), list1.end());
    show(list2.begin(), list2.end());
    list2.reverse();
    show(list1.begin(), list1.end());
    show(list2.begin(), list2.end());
    return 0;
}
