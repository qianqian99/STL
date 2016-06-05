#include "uninitialized.h"
#include <vector>
using namespace std;
int main() {
    vector<int> vc(10);
    uninitialized_fill_n(vc.begin(), 10, 100);
    return 0;
}
