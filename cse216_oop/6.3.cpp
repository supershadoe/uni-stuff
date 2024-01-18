#include <iostream>
#include <cstring>

class Details {
    public:
        char name[30], area[30], phoneno[11], area_code[8];
        Details() {
            name[0] = area[0] = phoneno[0] = area_code[0] = '\0';
        }
        Details(
            const char* oName,
            const char* oArea,
            const char* oPhoneNo,
            const char* oAreaCode
        ) {
            strcpy(name, oName);
            strcpy(area, oArea);
            strcpy(phoneno, oPhoneNo);
            strcpy(area_code, oAreaCode);
        }
        void printDetails() {
            using namespace std;
            char joined[11 + 8] = "";
            strcat(joined, area_code);
            strcat(joined, phoneno);
            cout << "Name: " << name << endl
                << "Area: " << area << endl
                << "Phone no: " << joined << endl;
        }
};

int main() {
    Details d1, d2("iafjsosaj", "Montreal", "5143343232", "+1");

    strcpy(d1.name, "fgdfdgfgf");
    strcpy(d1.area, "Delhi");
    strcpy(d1.phoneno, "1143434343");
    strcpy(d1.area_code, "+91");

    d1.printDetails();
    d2.printDetails();

    return 0;
}
