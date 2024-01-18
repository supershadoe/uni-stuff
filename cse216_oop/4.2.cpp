#include <iostream>
#define min(X, Y) (X < Y ? X : Y)

using namespace std;

int main() {
    int a, b, c;
    cout << "Enter three numbers." << endl;
    cin >> a >> b >> c;
    a = min(a, b);
    a = min(a, c);
    cout << "The smallest of these three numbers is " << a << endl;
    return 0;
}
