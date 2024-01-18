#include <iostream>
#define MAX_SIZE 10

int main() {
    int a[MAX_SIZE][MAX_SIZE], m, n;
    char x;
    enum mat_types {
        not_symm = 1 << 0,
        not_skew = 1 << 1,
        not_diag = 1 << 2,
        not_id = 1 << 3,
    };
    
    std::cout << "Enter the dimensions of the matrix: ";
    std::cin >> m >> x >> n;
    
    if (m < 0 || n < 0) {
        std::cout << "Dimensions cannnot be negative." << std::endl;
        return 1;
    } else if (m > MAX_SIZE || n > MAX_SIZE) {
        std::cout << "Dimension limit exceeded." << std::endl;
        return 1;
    }
    
    std::cout << "Enter the matrix elements." << std::endl;
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            std::cin >> a[i][j];
    
    unsigned int mat_type = 0;
    if (m != n)
        mat_type = not_symm | not_skew | not_id | not_diag;
    else
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (a[i][j] != a[j][i])
                    mat_type |= not_symm | not_id | not_diag;
                if (a[i][j] != -a[j][i])
                    mat_type |= not_skew;
                if (i == j) {
                    if (a[i][j] != 1)
                        mat_type |= not_id;
                    else if (a[i][j] != 0)
                        mat_type |= not_skew;
                } else if (a[i][j] != 0)
                    mat_type |= not_diag;
            }
        }
    if (! (mat_type & not_symm))
        std::cout << "The matrix is symmetric." << std::endl;
    if (! (mat_type & not_skew))
        std::cout << "The matrix is skew-symmetric." << std::endl;
    if (! (mat_type & not_diag))
        std::cout << "The matrix is diagonal." << std::endl;
    if (! (mat_type & not_id))
        std::cout << "The matrix is identity." << std::endl;
    
    return 0;
}
