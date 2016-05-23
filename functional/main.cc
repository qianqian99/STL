#include "functional.h"
#include <list>
#include <cstdlib>
#include "functionalex.h"
#define Size 10
using namespace std;
/*我有一些问题*/
class A
{
    public:
        int show()
        {
            cout << "show()" << endl;
            return 1;
        }
        //int show() const
        //{
        //    cout << "show() const" << endl;
        //    return 1;
        //}
        int dis() const
        {
            cout << "dis()" << endl;
            return 1;
        }

};
int main()
{
    A a;
    const A b;
    //hgg::mem_fun_ref_t<A, int> _a(&A::show);
    hgg::mem_fun(&A::show)(&a);
    //hgg::const_mem_fun_ref_t<A, int> _cb(&A::show);
    hgg::mem_fun(&A::dis)(&b);
    return 0;
}
#if 0
int main()
{
    A a;
    const A const_a;
    hgg::mem_fun_t<A, int> a_fun(&A::show);
    hgg::const_mem_fun_t<A, int> cons_a_fun(&A::show);
    a_fun(&a);
    cons_a_fun(&const_a);
    return 0;
}
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
template <typename _II, typename _Condition, typename _FUN>
void Print(_II first, _II last, _Condition condition, _FUN fun)
{
    for (; first != last; ++first)
    {
        if (condition(*first)) fun(*first);
    }
}
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

int add_self(int a)
{
    return ++a;
}
int add(int a, int b)
{
    return a+b;
}
int main()
{
    //pointer_to_unary_function<int, int> Add(add_self);
    //cout << ptr_fun(add_self)(10) << endl;
    //hgg::pointer_to_binary_function<int, int, int> Add(add);
    cout << hgg::ptr_fun(add)(3,4) << endl;
    return 0;
}
#include <vector>
#include <algorithm>
#include <functional>
class Shape
{
    public:
        virtual int show()=0;
};
class Rect: public Shape
{
    public:
        virtual int show()
        {
            cout << "Rect show ()" << endl;
            return 1;
        }
};
class Circle : public Shape
{
    public:
        virtual int show()
        {
            cout << "Circle show()" << endl;
            return 1;
        }
};
class Square : public Shape
{
    public:
        virtual int show()
        {
            cout << "Square show()" << endl;
            return 1;
        }
};
int main()
{
    vector<Shape *> v;
    v.push_back(new Rect);
    v.push_back(new Circle);
    v.push_back(new Square);
    v.push_back(new Circle);
    v.push_back(new Rect);
    for (int i=0; i<v.size(); ++i)
    {
        v[i]->show();
    }
    for_each(v.begin(), v.end(),
    hgg::mem_fun_t<Shape, int>(&Shape::show));
    return 0;
}
#endif
