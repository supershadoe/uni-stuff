#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

void* thread1() {
    char name[100];
    int *len = malloc(sizeof(int));
    printf("Enter name: ");
    scanf("%s", name);
    *len = strlen(name);
    return len;
}

void* thread2() {
    int year, *leap = malloc(sizeof(int));
    printf("Enter a year: ");
    scanf("%d", &year);
    *leap = year % 400 == 0
        ? 1
        : (year % 100 > 0 && year % 4 == 0);
    return leap;
}

int main() {
    pthread_t t1, t2;
    int *len, *leap;
    pthread_create(&t1, NULL, thread1, NULL);
    pthread_create(&t2, NULL, thread2, NULL);
    pthread_join(t1, (void**) &len);
    pthread_join(t2, (void**) &leap);
    printf("String length is %d\nThe given year is ", *len);
    if (!(*leap)) printf("not ");
    printf("a leap year.\n");
    return 0;
}
