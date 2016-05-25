#include <iostream>
#include <list>
using namespace std;
template <typename T>
void show(const T&con)
{
    typename T::const_iterator it = con.begin();
    for (; it != con.end(); ++it)
    {
        cout << *it << " ";
    }
    cout << endl;
}
int main()
{
    int arr[] = {1,2,3,23,56,34,2};
    list<int> list1(arr, arr+sizeof(arr)/sizeof(arr[0]));
    show(list1);
    int brr[] = {33, 45, 78, 12, 90, 100};
    list<int> list2(brr, brr+6);
   // show(list2);
    //list1.splice(list1.begin(), list1);
    //list1.transfer(list1.begin(), list1.begin(), list1.end());
    //list1.splice(list1.begin(), list1, ++list1.begin());
    //list1.transfer(list1.begin(), list1.begin(), list1.begin()+1);
    list1.splice(list1.begin(), list1, ++list1.begin(), --list1.end());
    show(list1);
    //show(list2);
    return 0;
}
//void splice ( iterator position, list<T,Allocator>& x );
//void splice ( iterator position, list<T,Allocator>& x, iterator i );
//void splice ( iterator position, list<T,Allocator>& x, iterator first, iterator last );
