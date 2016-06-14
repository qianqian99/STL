#include "./stack.h"
#include <iostream>
int main(int argc, char *argv[])
{
    hgg::stack<int> st;
    for(int i=0; i<1024; ++i)
    st.push(i);
    for (int i=0; i<1024; ++i) {
        std::cout << st.top() << " ";
        st.pop();
    }
    std::cout << std::endl;
    return 0;
}
