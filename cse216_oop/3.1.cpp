#include <iostream>

using namespace std;

int by_val(int x) {
    return x * 2;
}

int& by_ref(int& x) {
    x = x * 3;
    return x;
}

int main() {
    int a = 5;
    cout << by_val(a) << "\n";
    cout << a << "\n";
    cout << by_ref(a) << "\n";
    cout << a << "\n";
    return 0;
}
