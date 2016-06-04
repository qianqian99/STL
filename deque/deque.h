#ifndef _DEQUE_H_
#define _DEQUE_H_
#include "iterator.h"
template <typename _T, typename _A=std::alloc, size_t BuffSize=0>
class deque{
    public:
        typedef _T value_type;
        typedef value_type * pointer;
        typedef size_t size_type;
        typedef deque this_type;
        typedef value_type & reference;

        //todo
        typedef _deque_iterator<_T, _T *, _T &, BuffSize> iterator;
        /*for the queue and the stack, we use protected*/
        iterator begin() {
            return start;
        }
        iterator end() {
            return finish;
        }
        reference operator[] (size_t n) {
            return start[difference_type(n)];
        }
        reference front() {
            return *start;
        }
        /*利用--规避很多情况*/
        reference back() {
            iterator tmp = finish;
            --tmp;
            return *tmp;
        }
        //size_type size() const {
        //    return finish - start;
        //}
        bool empty() const{
            return start == finish;
        }
        deque(int n, const value_type &val)
            : start(), finish(), map(0), map_size(0)
        {
            fill_initialize(n, val);
        }
        void fill_initialize(int n, const value_type &val);
        void create_map_nodes(size_type n);
    protected:
        typedef pointer * map_pointer;
        iterator start;
        iterator finish;
        map_pointer map;
        size_type map_size;
    public:
        iterator begin() {return start;}
        iterator end() {return finish;}
        reference operator[](size_type n) {
            return start[difference_type(n)];
        }
};
template <typename _T, typename _A, size_t BuffSize>
void deque<_T, _A, BuffSize>::fill_initialize(int n, const value_type &val) {
    create_map_nodes(n);
    map_pointer cur;
    for (cur=start.node; cur<finish.node; ++cur) {
        uninitalized_fill(*cur, *cur+buff_size(), val);
    }
}
template <typename _T, typename _A, size_t BuffSize>
void deque<_T, _A, BuffSize>::create_map_nodes(size_type n) {
    size_type num_nodes = n / buff_size() + 1;
    map_size = max(initial_map_size(), num_nodes+2);
    map = malloc(sizeof(T*)*map_size); 
    map_pointer nstart = map + (map_size - num_nodes) / 2;
}
#endif
