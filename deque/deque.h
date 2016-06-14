#ifndef _DEQUE_H_
#define _DEQUE_H_
#include "iterator.h"
#include "../MemPool/simple_alloc.h"
#include "../copy_tool/uninitialized.h"
#include <algorithm>
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
    private:
        void reallocate_map(size_t add_size, bool is_add_front) {
            size_type num_use_nodes = finish.node - start.node + 1;
            size_type new_nodes = num_use_nodes + add_size;
            map_pointer new_start;
            /*只是需要重新修改中控的位置*/
            if (map_size > 2*new_nodes) {
                /*精华的调整*/
                new_start = map + (map_size - new_nodes) / 2
                                +(is_add_front ? add_size : 0);
                /*在左边*/
                if (new_start < start.node) {
                    std::copy(start.node, finish.node+1, new_start);
                }
                else {
                    std::copy_backward(start.node, finish.node+1, 
                                       new_start+num_use_nodes);
                }
            }
            else {
                size_type new_map_size = map_size + max(map_size, add_size) + 2;
                map_pointer new_map = map_allcator::allocate(new_map_size);
                new_start = new_map + (new_map_size - new_nodes) / 2
                                +(is_add_front ? add_size : 0);
                std::copy(start.node, finish.node+1, new_start);
                map_allcator::deallocate(map, map_size);
                map = new_map;
                map_size = new_map_size;
            }
            start.set_node(new_start);
            finish.set_node(new_start + num_use_nodes - 1);
        }
        void reserve_map_at_back(size_type add_size = 1) {
            if (add_size + 1 > map_size - (finish.node - map)) 
                reallocate_map(add_size, false);
        }
        void reserve_map_at_front(size_type add_size =1) {
            if (add_size > map - start.node) {
                reallocate_map(add_size, true);
            }
        }
        void push_back_aux(const _T &val) {
            reserve_map_at_back();
            *(finish.node + 1) = data_allocator::allocate(
                         hgg::_deque_buf_size(0, sizeof(_T)));
            construct(finish.cur, val);
            finish.set_node(finish.node + 1);
            finish.cur = finish.first;
        }
        void push_front_aux(const _T &val) {
            reserve_map_at_front();
            *(start.node-1) = data_allocator::allocate(
                    hgg::_deque_buf_size(0, sizeof(_T)));
            start.set_node(start.node - 1);
            start.cur = start.last - 1;
            construct(start.cur, val);
        }
    public:
        size_type max(size_type first, size_type second) {
            return first > second ? first : second;
        }
        size_type size() const{
            return finish - start;
        }
        void push_front(const _T &val) {
            if (start.cur != start.first) {
                construct(start.cur-1, val);
                --start.cur;
            }
            else {
                push_front_aux(val);
            }
        }
        void push_back(const _T &val) {
            if (finish.cur != finish.last-1) {
                construct(finish.cur, val);
                ++finish.cur;
            }
            else {
                push_back_aux(val);
            }
        }
    public:
        iterator insert_aux(iterator pos, const _T &val) {
            /*拥有元素个数的多少，来决定挪的是哪一个数据*/
            size_type diffBe = pos - start;
            if (diffBe < size()/2) {
                /*非常好而且非常有必要*/
                push_front(*start);
                /*新插入元素会导致迭代器失效*/
                iterator front1 = start;
                ++front1;
                iterator front2 = front1;
                ++front2;
                /*调整失效后的迭代器*/
                pos = start + diffBe;
                iterator pos1 = pos;
                ++pos1;
                std::copy(front2, pos1, front1);
            }
            else {
                push_back(back());
                iterator tail1 = finish;
                --tail1;
                iterator tail2 = tail1;
                --tail2;
                /*迭代器会失效*/
                pos = start + diffBe;
                std::copy_backward(pos, tail2, tail1);
            }
            *pos = val;
            return start;
        }
        /*在此我不提供insert方法因此放在私有*/
        iterator insert(iterator pos, const _T &val) {
            if (pos.cur == start.cur) {
                push_front(val);
                return start;
            }
            else if (pos.cur == finish.cur){
                push_back(val);
                iterator tmp = finish;
                --tmp;
                return tmp;
            }
            else {
                return insert_aux(pos, val);
            }
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
