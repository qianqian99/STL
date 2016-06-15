#include "uninitialized.h"
#include <vector>
using namespace std;
int main() {
    vector<int> vc(10);
    vector<int> vb(10, 20);
    hgg::uninitialized_fill_n(vc.begin(), 10, 100);
    hgg::uninitialized_copy(vb.begin(), vb.end(), vc.begin());
    return 0;
}
