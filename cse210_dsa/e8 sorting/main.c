#include <stdio.h>
#include "sort.h"

int main() {
    int a[ARR_SIZE], n, temp;

    printf("Enter the size of the array: ");
    scanf("%d", &n);

    if (n < 1) {
        printf("Cannot have an array with size < 1.\n");
        return 1;
    } else if (n > ARR_SIZE) {
        printf("Cannot have an array with size > %d.\n", ARR_SIZE);
        return 1;
    }

    printf("Enter %d numbers: ", n);
    for (temp = 0; temp < n; temp++)
        scanf("%d", &a[temp]);

    printf("Choose the required sort: 1 - insertion, 2 - merge sort\n[choose] >>> ");
    scanf("%d", &temp);

    if (temp == 1)
        insertion_sort(a, n);
    else if (temp == 2)
        merge_sort(a, 0, n - 1);
    else {
        printf("Invalid choice.\n");
        return 1;
    }

    printf("Sorted array: ");
    for (temp = 0; temp < n; temp++)
        printf("%d ", a[temp]);
    printf("\n");

    return 0;
}
