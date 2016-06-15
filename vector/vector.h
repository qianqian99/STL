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
        ~vector(){
            destory(start, finish);
            data_allocator::deallocate(start);
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
        void pop_back() {
            --finish;
            destory(finish);
        }
        iterator erase(iterator pos) {
            if (pos + 1 != end())
                std::copy(pos+1, finish, pos);
            --finish;
            destory(finish);
            return pos;
        }
        iterator erase(iterator first, iterator last) {
            iterator i = std::copy(last, finish, first);
            destory(i, finish);
            finish = finish - (last - first);
            return first;
            /*被删除元素的下一个元素*/
        }
        iterator insert(iterator pos, size_type n, const T&val) {
            if (n == 0)  return end();
            if ((size_type)(end_of_storage-finish) >= n) {
                const size_type elems_after = finish - pos;
                iterator old_finish = finish;
                if (elems_after > n) {
                    /*先构造finish后的n个数据
                      再copy elems_after-n 个数据
                      再填充n个数据*/
                    uninitialized_copy(finish-n, finish, finish);
                    finish += n;
                    std::copy_backward(pos, old_finish-n, old_finish);
                    fill(pos, pos+n, val);
                }
                else {
                    /*补出n-elems_after个数据
                      copy数据elems_after,
                      fill elems_after个数据val
                    */
                    uninitialized_fill_n(finish, n-elems_after, val);
                    finish += n-elems_after;
                    uninitialized_copy(pos, old_finish, finish);
                    finish += elems_after;
                    fill(pos, old_finish, val);
                }
            }
            else {
                const size_type old_size = size();
                const size_type new_size = old_size + (old_size>n?old_size:n);
                iterator new_start = data_allocator::allocate(new_size);
                iterator new_finish = uninitialized_copy(start, pos, new_start);
                new_finish = uninitialized_fill_n(new_finish, n, val);
                new_finish = uninitialized_copy(pos, finish, new_finish);
                destory(start, finish);
                data_allocator::deallocate(start);
                start = new_start;
                finish = new_finish;
                end_of_storage = new_start + new_size;
            }
        }
        void resize(size_type new_size, const T&val) {
            if (new_size < size()) {
                erase(begin()+new_size,  end());
            }
            else {
                insert(end(), new_size-size(), val);
            }
        }
        void resize(size_type new_size) {
            return resize(new_size, T());
        }
};
}
#endif
