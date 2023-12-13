#include "sort.h"

void insertion_sort(int a[], int n) {
    int i, j, key;
    for (i = 1; i < n; i++) {
        key = a[i];
        j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = key;
    }
}

void merge(int a[], int low, int mid, int high) {
    int t[ARR_SIZE];
    int i = low, j = mid + 1, k = 0;
    while (i <= mid && j <= high) {
        if (a[i] <= a[j]) {
            t[k] = a[i];
            i++;
        } else {
            t[k] = a[j];
            j++;
        }
        k++;
    }
    while (i <= mid) {
        t[k] = a[i];
        i++; k++;
    }
    while (j <= high) {
        t[k] = a[j];
        j++; k++;
    }
    for (k = low; k <= high; k++)
        a[k] = t[k-low];
}

void merge_sort(int a[], int low, int high) {
    int mid;
    if (low < high) {
        mid = (low + high) / 2;
        merge_sort(a, low, mid);
        merge_sort(a, mid + 1, high);
        merge(a, low, mid, high);
    }
}

