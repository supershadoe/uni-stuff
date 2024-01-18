#include <iostream>
#define MAX_SIZE 10
int main() {
    int a[MAX_SIZE][MAX_SIZE], b[MAX_SIZE][MAX_SIZE], m, n, p, q;
    char x;

    std::cout << "Enter the dimensions of matrix A: ";
    std::cin >> m >> x >> n;

    std::cout << "Enter the dimensions of matrix B: ";
    std::cin >> p >> x >> q;
    
    if (m < 0 || n < 0 || p < 0 || q < 0) {
        std::cout << "Dimensions cannnot be negative." << std::endl;
        return 1;
    } else if (n != p) {
        std::cout << "Cannot perform multiplication with these dimensions."
            << std::endl;
        return 1;
    } else if (m > MAX_SIZE || n > MAX_SIZE || p > MAX_SIZE || q > MAX_SIZE) {
        std::cout << "Dimension limit exceeded." << std::endl;
        return 1;
    }
    
    std::cout << "Enter the values for matrix A." << std::endl;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            std::cin >> a[i][j];

    std::cout << "Enter the values for matrix B." << std::endl;
    for (int i = 0; i < p; i++)
        for (int j = 0; j < q; j++)
            std::cin >> b[i][j];

    std::cout << "The resultant product matrix is:" << std::endl;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < q; j++) {
            int sum = 0;
            for (int k = 0; k < p; k++) {
                sum += a[i][k] * b[k][j];
            }
            std::cout << sum << "\t";
        }
        std::cout << std::endl;
    }

    return 0;
}
