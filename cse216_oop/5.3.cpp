#include <iostream>

class Distance {
    int feet[10], inches[10];
    public:
        void getData() {
            using namespace std;
            char temp[2];
            cout << "Enter 10 distances as x ft y in." << endl;
            for (int i = 0; i < 10; i++)
                cin >> feet[i] >> temp >> inches[i] >> temp;
        }
        void avgDistance() {
            int res = 0;
            for (int i = 0; i < 10; i++) {
                res += feet[i] * 12 + inches[i];
            }
            res /= 10;
            int ft = res / 12, in = res % 12;
            std::cout << "The average distance is "
                << ft << "ft " << in << "in."
                << std::endl;
        }
};

int main() {
    Distance d;
    d.getData();
    d.avgDistance();
    return 0;
}
