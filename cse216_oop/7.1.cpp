#include <iostream>

class Counter {
    int _n;
    public:
        Counter(): _n(0) {};
        int operator ++() {
            return ++_n;
	}
	int operator --() {
            return --_n;
        }
        void display() {
            std::cout << _n << std::endl;
        }
};

int main() {
    Counter c;
    c.display();
    ++c;
    ++c;
    c.display();
    --c;
    c.display();
    return 0;
}
