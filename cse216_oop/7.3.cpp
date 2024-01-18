#include <iostream>
#include <cstring>

class CustomString {
    char* sptr;
    int len;
    public:
        CustomString(const char* str, int slen) {
            sptr = new char[len + 1];
            len = slen;
            strcpy(sptr, str);
        }
        void operator = (const char* str) {
            strcpy(sptr, str);
        }
        const char* get_str() {
            return sptr;
        }
        CustomString operator +(CustomString const &b) {
            CustomString res(sptr, len + b.len);
            strcat(res.sptr, b.sptr);
            return res;
        }
};

int main() {
    using namespace std;
    CustomString a("Hello", 5), b(" Earth!", 7);
    cout << a.get_str() << endl;
    cout << b.get_str() << endl;
    b = " World!";
    std::cout << (a + b).get_str() << std::endl;
    return 0;
}
