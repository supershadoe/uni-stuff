#include <stdio.h>
#include <pthread.h>

static int flag[2] = {0, 0};
static int turn = -1;

// Shared resource
static int res = 5;

void lock(int self) {
    int other = 1 - self;
    flag[self] = 1;
    turn = other;
    while (flag[other] && turn == other);
}

void unlock(int self) {
    flag[self] = 0;
}

void* increment(void* tno) {
    int self = * (int*) tno;

    lock(self);

    printf("Thread %d is in critical section.\n", self);
    printf("Incrementing.\n");
    res++;
    printf("Value of shared resource: %d\n", res);

    unlock(self);
}

void* decrement(void* tno) {
    int self = * (int*) tno;

    lock(self);

    printf("Thread %d is in critical section.\n", self);
    printf("Decrementing.\n");
    res--;
    printf("Value of shared resource: %d\n", res);

    unlock(self);
}

int main() {
    pthread_t t1, t2;
    int a = 0, b = 1;
    printf("Value of shared resource: %d\n", res);
    pthread_create(&t1, NULL, increment, &a);
    pthread_create(&t2, NULL, decrement, &b);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}
