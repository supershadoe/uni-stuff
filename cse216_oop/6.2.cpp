#include <iostream>
#include <iomanip>

class Time {
    int _hr, _min, _sec;

    public:
        Time() {
            _hr = _min = _sec = 0;
        }
        Time(int hr, int min, int sec) {
            if (hr < 0 || min < 0 || sec < 0) {
                std::cout << "Negative values provided. Setting 00:00:00"
                    << std::endl;
                _hr = _min = _sec = 0;
                return;
            }
            _sec = sec % 60;
            min += (sec / 60);
            _min = min % 60;
            _hr = hr + (min / 60);
        }
        void display() {
            using namespace std;
            cout << "The time is "
                << setw(2) << setfill('0') << _hr << ":"
                << setw(2) << setfill('0') << _min << ":"
                << setw(2) << setfill('0') << _sec << endl;
        } 
        void add(Time& result, Time& other) {
            int temp;
            temp = _sec + other._sec;
            result._sec = temp % 60;
            temp = _min + other._min + (temp / 60);
            result._min = temp % 60;
            result._hr = _hr + other._hr + (temp / 60);
        }
};

int main() {
    Time t1(1, 59, 59), t2(13, 59, 61), t3;

    t1.display();
    t2.display();

    t1.add(t3, t2);

    std::cout << "\nAfter addition:" << std::endl;
    t3.display();

    return 0;
}
