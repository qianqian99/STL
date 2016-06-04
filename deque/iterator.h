#ifndef _ITERATOR_H_
#define _ITERATOR_H_
namespace hgg {
    inline size_t _deque_buf_size(size_t n, size_t sz) {
        return n != 0 ? n :
            (sz<512 ? size_t(512/sz) : size_t(1));
    }
    template <typename T, typename Ptr, typename Ref, size_t BuffSize>
    class _deque_iterator{
        public:
            //typedef _deque_iterator<T, T*, T&, BuffSize> iterator;
           // typedef _deque_iterator<T, const T*, const T&, BuffSize> 
                //const_iterator;
            static size_t buff_size() {
                return _deque_buf_size(BuffSize, sizeof(T));
            }
            /*iterator traits*/
            typedef T value_type;
            typedef T* pointer;
            typedef T& reference;
            typedef int difference_type;
            typedef size_t size_type;
            typedef std::random_access_iterator_tag
                iterator_category;
            typedef _deque_iterator self;
            typedef T** map_pointer;

            /*data*/
            T *cur;
            T *first;
            T *last;
            map_pointer node;
            /*function*/
            void set_node(map_pointer new_node) {
                node = new_node;
                first = *new_node;
                last = first + difference_type(buff_size());
            }
            reference operator*() const {
                return *cur;
            }
            /*some doubt*/
            pointer operator->() const {
                return &(operator*());
            }
            self &operator++() {
                ++cur;
                if (cur == last) {
                    set_node(node+1);
                    cur = first;
                }
                return *this;
            }
            self operator++(int) {
                self tmp = *this;
                ++*this;
                return tmp;
            }
            self &operator--() {
                if (cur == first) {
                    set_node(node - 1);
                    cur = last;
                }
                --cur;
                return *this;
            }
            self operator--(int) {
                self tmp = *this;
                --*this;
                return tmp;
            }
            self operator+=(difference_type n) {
                difference_type diff = n + (cur-first);
                /*in one commen buffer*/
                if (diff >= 0 && diff < difference_type(buff_size())) {
                    cur += n;
                }
                else {
                    /*not in common buffer*/
                    difference_type node_offset = 
                        diff > 0 ? diff/difference_type(buff_size())
                        : -difference_type((-diff-1)/buff_size()) - 1;
                    set_node(node_offset);
                    cur = first + (diff - node_offset * difference_type(buff_size()));
                }
                return *this;
            }
            self operator + (difference_type n) const {
                self tmp = *this;
                return tmp += n;
            }
            self &operator -= (difference_type n) {
                return *this += -n;
            }
            self operator - (difference_type n) const {
                self tmp = *this;
                return tmp -= n;
            }
            /*迭代器的随机取*/
            reference operator[] (difference_type n) const {
                return *(*this + n);
            }
            bool operator == (const self &x) const {
                return cur == x.cur;
            }
            bool operator != (const self &x) const {
                return cur != x.cur;
            }
            /*< very good*/
            bool operator < (const self &x) const {
                return node == x.node ? cur < x.cur : node < x.node;
            }
    };
}
#endif
