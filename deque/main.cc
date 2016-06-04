#include <iostream>
#include <deque>
#include <algorithm>
using namespace std;
template <typename Iterator>
void show(Iterator first, Iterator last) {
    for (; first != last; ++first) {
        cout << *first << " ";
    }
    cout << endl;
}
int main() {
    deque<int> queue(10, 4);
    return 0;
}
