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
            iterator reomve_if();
            iterator remove();
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
