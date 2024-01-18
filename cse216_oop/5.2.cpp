#include <iostream>
#include <iomanip>
#include <cstring>
#define EMP_COUNT 10

class Employee {
    long _empNo;
    char _name[30];
    public:
        Employee() {
            _empNo = 0;
            strcpy(_name, ""); 
        }
        void getData() {
            using namespace std;
            long empNo;

            cout << "Employee No: ";
            cin >> empNo;
            if (empNo < 0)
                cout << "How can employee no be negative??" << endl;
            else
                _empNo = empNo;

            cout << "Employee Name: ";
            cin >> _name;
        }
        void putData() {
            using namespace std;
            cout << setw(11) << _empNo << " "
                << setiosflags(ios::left) << setw(30) << _name
                << resetiosflags(ios::left) << endl;
        }
};

int main() {
    using namespace std;
    Employee e[EMP_COUNT];

    std::cout << "Enter the details of "
        << EMP_COUNT << " employees." << std::endl;
    for (int i = 0; i < EMP_COUNT; i++) {
        e[i].getData();
    }

    std::cout << "These are the data stored.\n"
        << "Employee No Employee Name" << std::endl;
    for (int i = 0; i < EMP_COUNT; i++) {
        e[i].putData();
    }

    return 0;
}
