#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>

#define PHIL_CNT 5

typedef enum {
    thinking,
    hungry,
    eating,
} phil_state;

sem_t mutex;
phil_state states[PHIL_CNT];
sem_t hungry_phils[PHIL_CNT];

int are_forks_avail(int tid) {
    int left = (tid + PHIL_CNT - 1) % PHIL_CNT;
    int right = (tid + 1) % PHIL_CNT;
    return states[left] != eating && states[right] != eating;
}

void take_forks(int tid) {
    int avail = 0;
    sem_wait(&mutex);
    states[tid] = hungry;
    printf("Philosopher %d is hungry.\n", tid + 1);
    avail = are_forks_avail(tid);
    if (avail)
        states[tid] = eating;
    sem_post(&mutex);
    if (!avail)
        sem_wait(&hungry_phils[tid]);
}

void put_forks(int tid) {
    int left = (tid + PHIL_CNT - 1) % PHIL_CNT;
    int right = (tid + 1) % PHIL_CNT;
    sem_wait(&mutex);
    states[tid] = thinking;
    if (are_forks_avail(left)) {
        states[left] = eating;
        sem_post(&hungry_phils[left]);
    }
    if (are_forks_avail(right)) {
        states[right] = eating;
        sem_post(&hungry_phils[right]);
    }
    sem_post(&mutex);
}

void* phil_code(void* tid) {
    int phil_no = * (int *) tid;

    while (1) {
        printf("Philosopher %d is thinking.\n", phil_no);
        sleep(1);
        take_forks(phil_no);
        printf("Philosopher %d is eating.\n", phil_no);
        sleep(5);
        put_forks(phil_no);
        sleep(4);
    }
}


int main() {
    int i = 0, p[PHIL_CNT];
    pthread_t tids[PHIL_CNT];
    for (i = 0; i < PHIL_CNT; i++) {
        sem_init(&hungry_phils[i], 0, 0);
        p[i] = i;
    }
    sem_init(&mutex, 0, 1);

    for (i = 0; i < PHIL_CNT; i++)
        pthread_create(&tids[i], NULL, phil_code, &p[i]);
    for (i = 0; i < PHIL_CNT; i++)
        pthread_join(tids[i], NULL);
    return 0;
}
