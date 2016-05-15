#include <iostream>
#include <list>
#include <vector>
void show(std::input_iterator_tag)
{
    std::cout << "input_iterator_tag show " << std::endl;
}
void show(std::random_access_iterator_tag)
{
    std::cout << "random_access_iterator_tag show" << std::endl;
}
void show(std::bidirectional_iterator_tag)
{
    std::cout << "bidirectional_iterator_tag show" << std::endl;
}
template <typename Iterator>
struct iterator_traits
{
    typedef typename Iterator::iterator_category iterator_category;
};
template <typename Iterator>
void show()
{
    //typedef typename Iterator::iterator_category category;
    typedef typename iterator_traits<Iterator>::iterator_category category;
    show(category());
}
/*
 * 关于萃取器存在的必要性*/
int main()
{
    std::list<int> list;
    show<std::list<int>::iterator>();
    std::vector<int> v;
    show<std::vector<int>::iterator>();
    return 0;
}
