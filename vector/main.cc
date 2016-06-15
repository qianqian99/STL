#if 0
#include <iostream>
#include <vector>
using namespace std;
int main() {
    vector<int> v(2, 8);
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    cout << "size : " << v.size() << " capacity: " << v.capacity() << endl; 
    return 0;
}
#else
#include <iostream>
#include "./vector.h"
template <typename Iterator>
void show(Iterator first, Iterator last) {
    for (; first != last; ++first) {
        std::cout << *first << " ";
    }
    std::cout << std::endl;
}
int main() {
    hgg::vector<int> v(100);
    v.push_back(100);
    v.push_back(20);
    v.push_back(20);
    v.push_back(20);
    v.push_back(20);
    v.insert(v.begin(), 100, 99);
    show(v.begin(), v.end());
    return 0;
}
#endif
