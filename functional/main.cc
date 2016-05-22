#include "functional.h"
#include <list>
#include <cstdlib>
#define Size 10
using namespace std;
#if 0
//case 1:
template <typename _II>
void Print(_II first, _II last)
{
    for (; first != last; ++first)
    {
        cout << *first << " ";
    }
}
//case 2:
template <typename _II, typename _FUN>
void Print(_II first, _II last, _FUN fun)
{
    for (; first != last; ++first)
    {
        fun(*first);
    }
}
//case 3:
template <typename _II, typename _Condition, typename _FUN>
void Print(_II first, _II last, _Condition condition, _FUN fun)
{
    for (; first != last; ++first)
    {
        if (condition(*first, 40)) fun(*first);
    }
}
#endif
template <typename _II, typename _Condition, typename _FUN>
void Print(_II first, _II last, _Condition condition, _FUN fun)
{
    for (; first != last; ++first)
    {
        if (condition(*first)) fun(*first);
    }
}
#if 0
int main()
{
    int ar[Size];
    for (int i=0; i<Size; ++i)
    {
        ar[i] = rand()%100+1;
    }
    list<int> data(ar, ar+Size);
    hgg::binder2nd<hgg::greater<int> > bind2nd(hgg::greater<int>(), 30);
    Print(data.begin(), data.end(), bind2nd, hgg::print_elem<int>());
    cout << endl;
    return 0;
}
int main()
{
    int ar[Size];
    for (int i=0; i<Size; ++i)
    {
        ar[i] = rand()%100+1;
    }
    list<int> data(ar, ar+Size);
    Print(data.begin(), data.end(), hgg::bind1st(50, hgg::greater<int>()), hgg::print_elem<int>());
    cout << endl;
    return 0;
}
int main()
{
    int ar[Size];
    for (int i=0; i<Size; ++i)
    {
        ar[i] = rand()%100+1;
    }
    list<int> data(ar, ar+Size);
    Print(data.begin(), data.end(), hgg::not1(hgg::bind1st(50, hgg::greater<int>())), hgg::print_elem<int>());
    cout << endl;
    return 0;
}
#endif
