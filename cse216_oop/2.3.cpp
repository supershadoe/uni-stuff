#include <iostream>

int main() {
    enum days_of_week { sun, mon, tue, wed, thu, fri, sat, };
    enum cities { city1, city2, };

    int temp[2][7];

    for (int i = city1; i <= city2; i++) {
        std::cout << "Enter the temperature data of city " << i << " (from sun to sat): ";
        for (int j = sun; j <= sat; j++)
            std::cin >> temp[i][j];
    }
    
    for (int i = city1; i <= city2; i++) {
        std::cout << "Temperature data of city " << i << " (from sun to sat): ";
        for (int j = sun; j <= sat; j++) {
            std::cout << temp[i][j];
            if (j < sat)
                std::cout << ", ";
        }
        std::cout << std::endl;
    }
    
    
    return 0;
}
