#include <iostream>

using namespace std;

class Account2;

class Account1
{
private:
    int bal;

public:
    Account1(int _bal) : bal(_bal) {}
    int getBal() { return bal; }
    friend void transferAmount(int, Account1 &, Account2 &);
    friend void transferAmount(int, Account2 &, Account1 &);
};

class Account2
{
private:
    int bal;

public:
    Account2(int _bal) : bal(_bal) {}
    int getBal() { return bal; }
    friend void transferAmount(int, Account1 &, Account2 &);
    friend void transferAmount(int, Account2 &, Account1 &);
};

void transferAmount(int amt, Account1 &source, Account2 &dest)
{
    if (source.bal - amt < 0)
    {
        cout << "Low balance" << endl;
        return;
    }
    dest.bal += amt;
    source.bal -= amt;
    cout << "Transferred " << amt << endl;
}

void transferAmount(int amt, Account2 &source, Account1 &dest)
{
    if (source.bal - amt < 0)
    {
        cout << "Low balance" << endl;
        return;
    }
    dest.bal += amt;
    source.bal -= amt;
    cout << "Transferred " << amt << endl;
}

int main()
{
    Account1 a1(100);
    Account2 a2(100);
    cout << "Balance in account 1 and 2: "
         << a1.getBal() << " " << a2.getBal() << endl;
    transferAmount(100, a1, a2);
    transferAmount(1, a1, a2);
    transferAmount(50, a2, a1);
    cout << "Balance in account 1 and 2: "
         << a1.getBal() << " " << a2.getBal() << endl;
    return 0;
}
