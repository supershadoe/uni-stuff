#include <iostream>
#include <cmath>

class Decimal {
    int _n;
    public:
        Decimal(int n): _n(n) {};
        int operator ~() {
            _n = pow(10, trunc(log10(_n)) + 1) - _n;
            return _n;
        }
        void display() {
            std::cout << _n << std::endl;
        }
};

int main() {
    Decimal d(54);
    d.display();
    std::cout << "The 2's complement of 54 is " << ~54 << std::endl;
    d.display();
    std::cout << "The 10's complement of 54 is " << ~d << std::endl;
    d.display();
    return 0;
}
