#include <iostream>
#include <deque>
#include <algorithm>
#include "iterator.h"
using namespace std;
int main() {
    deque<int> queue;
    queue.push_back(100);
    queue.push_back(100);
    queue.push_back(100);
    queue.push_back(100);
    queue.push_back(100);
    queue[4] = 3;
    return 0;
}
