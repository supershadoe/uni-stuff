#include <iostream>

using namespace std;

inline int inline_2x(int x) {
    return x * 2;
}

int main() {
    int a = 5;
    cout << inline_2x(a) << "\n";
    return 0;
}
