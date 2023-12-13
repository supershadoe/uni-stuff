#include <stdio.h>
#include "search.h"

int lin_search(element a[], int n, element x) {
    int i;
    for (i = 0; i < n; i++)
        if (a[i] == x)
            return i;
    return -1;
}

int bin_search(element a[], int n, element x) {
    int l = 0, h = n-1, mid;
    while(l <= h) {
        mid = (l + h) / 2;
        if (a[mid] == x)
            return mid;
        else if (a[mid] > x)
            h = mid - 1;
        else
            l = mid + 1;
    }
    printf("Check if the array provided is a sorted one.\n");
    return -1;
}

int rbin_search(element a[], int l, int h, element x) {
    int mid;
    if (l > h) {
        printf("Check if the array provided is a sorted one.\n");
        return -1;
    }
    mid = (l + h) / 2;
    if (a[mid] == x)
        return mid;
    else if (a[mid] > x)
        return rbin_search(a, l, mid - 1, x);
    else
        return rbin_search(a, mid + 1, h, x);
}

