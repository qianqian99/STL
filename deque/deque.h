#ifndef _DEQUE_H_
#define _DEQUE_H_
#include "iterator.h"
#include "../MemPool/simple_alloc.h"
#include "../copy_tool/uninitialized.h"
namespace hgg{
template <typename _T, typename _A=second_allocator,  size_t BuffSize=0>
class deque{
    public:
        typedef _T value_type;
        typedef value_type * pointer;
        typedef size_t size_type;
        typedef deque this_type;
        typedef value_type & reference;

        static size_t buff_size() {
            return hgg::_deque_buf_size(BuffSize, sizeof(_T));
        }
        //todo
        typedef hgg::_deque_iterator<_T, _T *, _T &, BuffSize> iterator;
        /*for the queue and the stack, we use protected*/
        iterator begin() {
            return start;
        }
        iterator end() {
            return finish;
        }
        reference operator[] (size_t n) {
            return start[value_type(n)];
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
        typedef simple_alloc<_T, _A> data_allocator;
        typedef simple_alloc<_T *, _A> map_allcator;
        typedef pointer * map_pointer;
        iterator start;
        iterator finish;
        map_pointer map;
        size_type map_size;
        const static int default_map_size; 
    public:
        size_type max(size_type first, size_type second) {
            return first > second ? first : second;
        }
};
template <typename _T, typename _A, size_t BuffSize>
const int deque<_T, _A, BuffSize>::default_map_size = 8;
template <typename _T, typename _A, size_t BuffSize>
void deque<_T, _A, BuffSize>::fill_initialize(int n, const value_type &val) {
    create_map_nodes(n);
    map_pointer cur;
    for (cur=start.node; cur<finish.node; ++cur) {
        uninitialized_fill(*cur, *cur+buff_size(), val);
    }
    uninitialized_fill(finish.first, finish.cur, val);
}
template <typename _T, typename _A, size_t BuffSize>
void deque<_T, _A, BuffSize>::create_map_nodes(size_type n) {
    size_type num_nodes = n / buff_size() + 1;
    map_size = max(default_map_size, num_nodes+2);
    map = map_allcator::allocate(map_size);
    map_pointer nstart = map + (map_size - num_nodes) / 2;
    map_pointer nfinish = nstart + num_nodes - 1;
    map_pointer cur;
    for (cur=nstart; cur<=nfinish; ++cur) {
        *cur = data_allocator::allocate(hgg::_deque_buf_size(0, sizeof(_T)));
    }
    start.set_node(nstart);
    finish.set_node(nfinish);
    start.cur = start.first;
    finish.cur = finish.first + n % buff_size();
    /*[head, tail)*/
}
}
#endif
