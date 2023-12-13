#include <stdio.h>
#include "search.h"

#define ARR_SIZE 10

int main() {
    element a[ARR_SIZE], x;
    int i, n, ch, pos;

    printf("Enter number of elements to be stored: ");
    scanf("%d", &n);
    if (n > ARR_SIZE) {
        printf("Array size cannot be greater than %d.\n", ARR_SIZE);
        return 1;
    } else if (n < 1) {
        printf("Array size cannot be lower than 1.\n");
        return 1;
    }

    printf("Enter %d elements: ", n);
    for(i = 0; i < n; i++)
        scanf("%d", &a[i]);
        
    printf("Enter the element to search: ");
    scanf("%d", &x);

    printf(
        "Enter what search to perform:\n"
        "\t1. Linear search\n"
        "\t2. Binary search\n"
        "\t3. Recursive binary search\n\n"
    );
    
    printf("Enter the choice: ");
    scanf("%d", &ch);
    
    switch(ch) {
        case 1:
            pos = lin_search(a, n, x); break;
        case 2:
            pos = bin_search(a, n, x); break;
        case 3:
            pos = rbin_search(a, 0, n - 1, x); break;
        default:
            printf("Not implemented.\n");
    }

    if (pos == -1)
        printf("The element was not found in the array.\n");
    else
        printf("The element was present in array index %d.\n", pos);

    return 0;
}
