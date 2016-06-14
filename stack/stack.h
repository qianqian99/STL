#ifndef _STACK_H_
#define _STACK_H_
#include "../deque/deque.h"
namespace hgg
{
template <typename T, typename Con=deque<T> >
class stack {
    private:
        Con c;
    public:
        typedef typename Con::size_type size_type;
        typedef typename Con::value_type value_type;
        typedef typename Con::reference reference;
    public:
        stack() : c(0, 0){}
        bool empty() const {
            return c.empty();
        }
        size_type size() const {
            return c.size();
        }
        reference top() {
            return c.back();
        }
        value_type top() const {
            return c.back();
        }
        void push(const T&val) {
            c.push_back(val);
        }
        void pop() {
            return c.pop_back();
        }
        bool operator == (const stack &ostack) const {
            return c == ostack.c;
        }
        bool operator < (const stack &ostack) const {
            return c < ostack.c;
        }
};
}
#endif
