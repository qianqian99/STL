#include <iostream>
#include <list>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <typeinfo>
#if 0
实现一个自己的advance
支持各种迭代器，
包括指针

获得我们迭代器类型的方法:
1.萃取  需要注意我们的特化
2.直接获得
3.定义函数： 1.还是基于萃取器， 2.基于模板参数的推演
#endif
namespace Advance
{
    template <typename Iterator>
    struct iterator_traits
    {
        typedef typename Iterator::value_type value_type;
        typedef typename Iterator::iterator_category iterator_category;
        typedef typename Iterator::difference_type difference_type;
        typedef typename Iterator::pointer pointer;
        typedef typename Iterator::reference reference;
    };
    /*为了支持指针的操作我们需要对萃取器进行特化*/
    template <typename T>
    struct iterator_traits<T *>
    {
        typedef T value_type;
        typedef std::random_access_iterator_tag iterator_category;
        typedef int difference_type;
        typedef T * pointer;
        typedef T & reference; 
    };
    template <typename _II>
    inline void advance(_II &first, int n, std::input_iterator_tag)
    {
        if (n < 0) return;
        while (n--) ++first;
    }
    template <typename _IF>
    inline void advance(_IF &first, int n, std::forward_iterator_tag)
    {
        advance(first, n, std::input_iterator_tag());
    }
    template <typename _IB>
    inline void advance(_IB &first, int n, std::bidirectional_iterator_tag)
    {
        if (n < 0) while (n++) --first;
        else advance(first, n, std::input_iterator_tag());
    }
    template <typename _IRA>
    void advance(_IRA &first, int n, std::random_access_iterator_tag)
    {
        first += n;
    }
    /*给定接口获得迭代器的类型*/
    template <typename Iterator>
    inline typename iterator_traits<Iterator>::iterator_category
    iterator_category(Iterator it)
    {
        return typename iterator_traits<Iterator>::iterator_category();
    }
    template <typename Iterator>
    inline typename iterator_traits<Iterator>::value_type *
    value_type(Iterator it)
    {
        typedef typename iterator_traits<Iterator>::value_type value_type;
        return static_cast<value_type *>(0);
    }
    /*另一种得到value_type 的值*/
    /*传入迭代器*/
    template <typename _Cat, typename _T, typename _Dis, typename _P, typename _Ref>
    _Cat _Cat_Iter(const std::iterator<_Cat, _T, _Dis, _P, _Ref> &)
    {
        return _Cat();
    }
    template <typename T>
    std::random_access_iterator_tag _Cat_Iter(const T *)
    {
        return std::random_access_iterator_tag();
    }
    template <typename Iterator>
    void advance(Iterator &it, int n)
    {
        //typedef typename Iterator::iterator_category iterator_category;
        //typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
        //advance(it, n, iterator_category(it));
        advance(it, n, _Cat_Iter(it));
    }
};
int main()
{
    int arr[10];
    for (int i=0; i<10; ++i)
    {
        arr[i] = rand()%100;
    }
    int *p = arr;
    Advance::advance(p, 5);
    std::vector<int> _vec(arr, arr+10);
    return 0;
}
#if 0
int main()
{
    int arr[10];
    for (int i=0; i<10; ++i)
    {
        arr[i] = rand()%100;
    }
    std::vector<int> _vec(arr, arr+10);
    std::list<int> _list(arr, arr+10);
    std::list<int>::iterator it = _list.begin();
    //std::for_each(it, _list.end(), [](int e)->void{std::cout << e << " ";});
    //std::cout << std::endl;
    //advance(it, 5);
    Advance::advance(it, 5);
    //std::vector<int>::iterator vit = _vec.begin();
    //Advance::advance(vit, 5);
    //const int *p = arr;
    //Advance::advance(p, 5);
    //double *pd = NULL;
    //Advance::advance(pd, 5);
    //std::for_each(it, _list.end(), [](int e)->void{std::cout << e << " ";});
    //std::cout << std::endl;
    return 0;
}
#endif
