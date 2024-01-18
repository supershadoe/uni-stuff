#include <iostream>
#define CSE 1
#define ECE 2
#define MECH 3
#define DEPARTMENT ECE

int main() {
    #ifdef DEPARTMENT
    #if DEPARTMENT == CSE || DEPARTMENT == ECE
        std::cout << "The candidate is eligible." << std::endl;
        return 0;
    #endif
    #endif

    std::cout << "The candidate is not eligible." << std::endl;
    return 0;
}
