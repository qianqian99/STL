#ifndef _DEQUE_H_
#define _DEQUE_H_
template <typename _T, typename _A, size_t BuffSize>
class deque{
    public:
        typedef _T value_type;
        typedef value_type * pointer;
        typedef size_t size_type;
        typedef deque this_type;

        //todo
        typedef _deque_iterator<> iterator;
        /*for the queue and the stack, we use protected*/
    protected:
        typedef pointer * map_pointer;
        iterator start;
        iterator finish;
        map_pointer map;
        size_type map_size;
};
#endif
