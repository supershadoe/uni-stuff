#include <iostream>

template <typename T>
T findMax(T a, T b)
{
    return a > b ? a : b;
}

template <>
char findMax(char a, char b)
{
    char c = a > 'a' ? a : 'a' + a - 'A';
    char d = b > 'a' ? b : 'a' + b - 'A';
    return c > d ? a : b;
}

int main()
{
    using namespace std;
    cout << findMax(1, 2) << endl;
    cout << findMax(3.2, 5.2) << endl;
    cout << findMax('a', 'b') << endl;
    cout << findMax('a', 'B') << endl;
    return 0;
}
