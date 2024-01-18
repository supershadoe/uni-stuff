#include <iostream>

using namespace std;

int add(int a, int b) {
    return a + b;
}

int add(int a, int b, int c) {
    return a + b + c;
}

double add(double a, double b) {
    return a + b;
}

int main() {
    cout << add(2, 3) << "\n";
    cout << add(1, 2, 3) << "\n";
    cout << add(2.1, 3.1) << "\n";
    return 0;
}
