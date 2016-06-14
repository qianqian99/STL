#ifndef _VECTOR_H_
#define _VECTOR_H_
#include "../MemPool/simple_alloc.h"
#include <cstddef>
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
};
#endif
