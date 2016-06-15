#ifndef _VECTOR_H_
#define _VECTOR_H_
#include "../MemPool/simple_alloc.h"
#include "../copy_tool/uninitialized.h"
#include "../construct/construct.h"
#include <cstddef>
namespace hgg
{
template <typename T, typename Alloc=second_allocator>
class vector{
    public:
        /*type alias*/
        typedef T value_type;
        typedef value_type * pointer;
        typedef value_type * iterator;
        typedef value_type & reference;
        typedef size_t size_type;
        typedef int difference_type;
    protected:
        typedef simple_alloc<value_type, Alloc> data_allocator;
        iterator start;
        iterator finish;
        iterator end_of_storage;
        iterator allocate_and_fill(size_type n, const T&val) {
            iterator res = data_allocator::allocate(n);
            uninitialized_fill_n(res, n, val); 
            return res;
        }
        void fill_initialize(size_type n, const T&val) {
            start = allocate_and_fill(n, val);
            finish = start + n;
            end_of_storage = finish;
        }
    public:
        iterator begin() {
            return start;
        }
        iterator end() {
            return finish;
        }
        size_type size() const {
            return (size_type)(finish-start);
        }
        size_type capacity() const {
            return (size_type)(end_of_storage - start);
        }
        reference operator[] (size_type n) {
            return *(start+n);
        }
        reference front() {
            return *start;
        }
        reference back() {
            return *(finish-1);
        }
        vector() : start(NULL), finish(NULL) , end_of_storage(NULL){}
        vector(size_type n, const T&val) {
            fill_initialize(n, val);
        }
        explicit vector(size_type n) {
            fill_initialize(n, T());
        }
        /*insert function*/
        void insert_aux(iterator pos, const T&val) {
            if (pos != end_of_storage) {
                construct(finish, *(finish-1));
                ++finish;
                std::copy_backward(pos, finish-2, finish-1);
                *pos = val;
            }
            else {
                const size_type old_size = size();
                const size_type new_size = old_size != 0?
                    2 * old_size : 1;
                iterator new_start = data_allocator::allocate(new_size);
                iterator new_finish = uninitialized_copy(start, pos, new_start);
                construct(new_finish, val);
                ++new_finish;
                new_finish = uninitialized_copy(pos, finish, new_finish);
                destory(begin(), end());
                data_allocator::deallocate(start);
                start = new_start;
                finish = new_finish;
                end_of_storage = start + new_size;
            }
        }
        void push_back(const T&val) {
            if (finish != end_of_storage) {
                construct(finish, val);
                ++finish;
            }
            else {
                insert_aux(end(), val);
            }
        }
};
}
#endif
