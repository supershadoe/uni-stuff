#include <iostream>
#include <iomanip>

class CarPart {
    int _car_id;
    int _charge_per_hr;
    float _time;
    public:
        CarPart(int, int);
        void set_time(float);
        void get_data();
        int get_id() { return _car_id; }
        int get_charge() { return _charge_per_hr; }
};

CarPart::CarPart(int id, int charge) {
    _car_id = id;
    _charge_per_hr = charge;
    _time = 0;
}

void CarPart::set_time(float time) {
    if (time >= 0)
        if (time > _time)
            _time = time;
        else
            std::cout << "Time can't flow in reverse??" << std::endl;
    else
        std::cout << "How is time negative??" << std::endl;
}

void CarPart::get_data() {
    using namespace std;
    cout << "Car ID: " << _car_id << endl
        << "Parking Charge per hour: " << _charge_per_hr << endl
        << "Hours parked: " << setprecision(2) << _time << endl
        << "Charges incurred: " << _charge_per_hr * _time << endl;
}

int main() {
    using namespace std;
    CarPart c1(1234, 2), c2(1235, 3), c3(1232, 10);
    float time;
    cout << "How long was car " << c1.get_id() << " parked? ";
    cin >> time;
    c1.set_time(time);
    cout << "How long was car " << c2.get_id() << " parked? ";
    cin >> time;
    c2.set_time(time);
    cout << "How long was car " << c3.get_id() << " parked? ";
    cin >> time;
    c3.set_time(time);
    c1.get_data();
    c2.get_data();
    c3.get_data();
    return 0;
}
