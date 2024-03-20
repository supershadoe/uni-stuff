#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define QUEUE_LEN 5
#define MAX_COUNT 10

static sem_t mutex;
static sem_t empty_slots;
static sem_t filled_slots;

static int front = -1,
    rear = -1,
    buf[QUEUE_LEN];

void* producer() {
    int n = 1;
    while (n <= MAX_COUNT) {
        sem_wait(&empty_slots);
        sem_wait(&mutex);

        rear = (rear + 1) % QUEUE_LEN;
        buf[rear] = n;
        n++;
        printf("Produced %d\n", buf[rear]);

        sem_post(&mutex);
        sem_post(&filled_slots);
    }
}

void* consumer() {
    int i;
    for (i = 0; i < MAX_COUNT; i++) {
        sem_wait(&filled_slots);
        sem_wait(&mutex);

        front = (front + 1) % QUEUE_LEN;
        printf("%d consumed\n", buf[front]);

        sem_post(&mutex);
        sem_post(&empty_slots);
    }
}

int main() {
    pthread_t p, c;

    // 2nd arg - pshared
    // 0 - between threads, non-zero - between processes
    sem_init(&mutex, 0, 1);
    sem_init(&empty_slots, 0, QUEUE_LEN);
    sem_init(&filled_slots, 0, 0);

    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    pthread_join(p, NULL);
    pthread_join(c, NULL);

    return 0;
}
