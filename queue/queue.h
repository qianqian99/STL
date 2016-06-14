#ifndef _QUEUE_H_
#define _QUEUE_H_
#include "../deque/deque.h"
namespace hgg
{
    template <typename T, typename Con=deque<T> >
    class queue{
        private:
            Con c;
        public:
            typedef typename Con::value_type value_type;
            typedef typename Con::size_type size_type;
            typedef typename Con::reference reference;
        public:
            queue() : c(0, 0){}
            bool empty() const {
                return c.empty();
            }
            size_type size() const {
                return c.size();
            }
            reference back() {
                return c.back();
            }
            value_type back() const {
                return c.back();
            }
            reference front() {
                return c.front();
            }
            value_type front() const {
                return c.front();
            }
            void push(const T&val) {
                c.push_back(val);
            }
            void pop() {
                return c.pop_front();
            }
            bool operator == (const queue&oqueue) const {
                return c == oqueue.c;
            }
            bool operator < (const queue &oqueue) const {
                return c < oqueue.c;
            }
    };
}
#endif
