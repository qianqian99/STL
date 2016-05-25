#ifndef _SPLICE_H_
#define _SPLICE_H_
#include <iostream>
#include <cstdlib>
namespace hgg
{
    template <typename Type>
    struct __list_node {
        typedef __list_node* node_pointer;
        node_pointer prev;
        node_pointer next;
        Type data;
    };
    template <typename Type>
    class list
    {
        public:
            typedef __list_node<Type> list_node;
            typedef list_node * link_type;
            typedef list this_type;
            struct __list_iterator {
                __list_node<Type> *node;
                typedef __list_iterator this_type;
                typedef Type value_type;
                typedef Type * pointer;
                typedef Type & reference;
                typedef int difference_type;
                __list_iterator(__list_node<Type> *pnode) : node(pnode){}
                this_type &operator++() {
                    node = node->next;
                    return *this;
                }
                this_type &operator--() {
                    node = node->prev;
                    return *this;
                }
                this_type operator++(int){
                    __list_node<Type> *tmp = node;
                    /*SGI give the solution is ++*this*/
                    node = node->next;
                    return tmp;
                }
                this_type operator--(int){
                    __list_node<Type> *tmp = node;
                    node = node->prev;
                    return tmp;
                }
                value_type &operator*() {
                    return node->data;
                }
                const value_type &operator*() const {
                    return node->data;
                }
                bool operator != (const this_type &other) const {
                    return node != other.node;
                }
                bool operator == (const this_type &other) const {
                    return node == other.node;
                }
            };
            typedef __list_iterator iterator;
            list(){
                empty_init();
            }
            template <typename T>
            list(const T*start, const T*end) {
                empty_init();
                while (start != end) {
                    push_back(*start++);
                }
            }
            iterator begin() {
                return node->next;
            }
            iterator end() {
                return node;
            }
            iterator insert(iterator position, const Type &val) {
                link_type pnode = get_node();
                pnode->data = val;
                pnode->next = position.node;
                pnode->prev = position.node->prev;
                position.node->prev->next = pnode;
                position.node->prev = pnode;
                return pnode;
            }
            void push_back(const Type &val) {
                insert(end(), val);
            }
            void push_front(const Type &val) {
                insert(begin(), val);
            }
            bool empty() const{
                return node == node->next;
            }
            void transfer(iterator dest, iterator first, iterator last) {
                /*first next, next prev*/
                if (dest != last)   {//  escape first  dest/last
                    last.node->prev->next = dest.node;
                    first.node->prev->next = last.node;
                    dest.node->prev->next = first.node;

                    link_type tmp = dest.node->prev;
                    dest.node->prev = last.node->prev;
                    last.node->prev = first.node->prev;
                    first.node->prev = tmp;
                }
            }
            void splice(iterator dest, this_type &other) {
                if (!other.empty()) {
                    transfer(dest, other.begin(), other.end());
                }
            }
            void splice(iterator dest, this_type &other, iterator p) {
                iterator j = p++;
                if (dest != p && dest != j) {
                    transfer(dest, j, p);
                }
            }
            void splice(iterator dest, this_type &other, iterator first, iterator last) {
                if (first != last) {
                    transfer(dest, first, last);
                }
            }
            iterator erase(iterator dest) {
                if (empty() || dest == end()) return end();
                else {
                    link_type next = dest.node->next;
                    next->prev = dest.node->prev;
                    dest.node->prev->next = next;
                    free(dest.node);
                    return next;
                }
            }
            template <typename _F>
            void reomve_if(const _F&fun){
                for (iterator it=begin(); it!=end();) {
                    if (fun(*it)) erase(it++);
                    else ++it;
                }
            }
            void remove(const Type& elem) {
                for (iterator it=begin(); it!=end();) {
                    if (elem == *it) erase(it++);
                    else ++it;
                }
            }
            void merge(this_type &X) {
                iterator _F1 = begin(), _L1 = end();
                iterator _F2 = X.begin(), _L2 = X.end();
                while (_F1 != _L1 && _F2 != _L2) {
                    if (*_F2 < *_F1) {
                        iterator _M = _F2++;
                        transfer(_F1, _M, _F2);
                    }
                    else ++_F1;
                }
                if (_F2 != _L2) {
                    transfer(end(), _F2, _L2);
                }
            }
            void swap(this_type &other) {
                link_type tmp = node;
                node = other.node;
                other.node = tmp;
            }
            void reverse() {
                if (node->next == node || node->next->next == node) return;
                iterator first = ++begin(), last=end();
                while (first != last) {
                    iterator tmp = first++;
                    transfer(begin(), tmp, first);
                }
            }
        protected:
            link_type get_node() {
                return (link_type)malloc(sizeof(list_node));
            }
            void empty_init() {
                node = get_node();
                node->next = node;
                node->prev = node;
            }
        private:
            link_type node;
    };
}
#endif
