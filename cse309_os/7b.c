#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <string.h>

#define PHRASE_LEN 100

static sem_t rw_mutex;
static sem_t count_mutex;

static int read_count = 0;
static char phrase[PHRASE_LEN];

void* writer(void* writer_no) {
    while (1) {
        sem_wait(&rw_mutex);
        printf("[writer %d] Enter some phrase: ", * (int*) writer_no);
        fgets(phrase, PHRASE_LEN, stdin);
        sem_post(&rw_mutex);
        sleep(1);
    }
}

void* reader(void* reader_no) {
    while (1) {
        sem_wait(&count_mutex);
        read_count++;
        if (read_count == 1)
            sem_wait(&rw_mutex);
        sem_post(&count_mutex);

        printf("Reader %d: %s", * (int*) reader_no, phrase);

        sem_wait(&count_mutex);
        read_count--;
        if (read_count == 0)
            sem_post(&rw_mutex);
        sem_post(&count_mutex);
        sleep(1);
    }
}

int main() {
    pthread_t w, r1, r2;
    int a = 0, b = 1;

    sem_init(&rw_mutex, 0, 1);
    sem_init(&count_mutex, 0, 1);

    pthread_create(&w, NULL, writer, &a);
    pthread_create(&r1, NULL, reader, &a);
    pthread_create(&r2, NULL, reader, &b);

    pthread_join(w, NULL);
    pthread_join(r1, NULL);
    pthread_join(r2, NULL);
    return 0;
}
