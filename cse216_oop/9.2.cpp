#include <iostream>

class Base
{
public:
    virtual void show() = 0;
};

class D1 : Base
{
private:
    int x;

public:
    D1(int _x) : x(_x) {}
    void show()
    {
        std::cout << "The value stored is " << x << std::endl;
    }
};

class D2 : Base
{
private:
    char x;

public:
    D2(char _x) : x(_x) {}
    void show()
    {
        std::cout << "The value stored is " << x << std::endl;
    }
};

int main()
{
    // Base b; // Cannot instantiate as Base is an abstract class
    D1 d1(10);
    D2 d2('a');
    // b.show(); // Pure virtual function so doesn't work
    d1.show();
    d2.show();
    return 0;
}
