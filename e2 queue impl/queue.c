#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

static Queue q;

void create_queue(int max_size) {
    q.q = calloc(sizeof(element), max_size);
    q.MAX_SIZE = max_size;
    q.front = -1;
    q.rear = -1;
}

int is_full() {
    return q.rear >= q.MAX_SIZE - 1;
}

int is_empty() {
    return q.front == -1;
}

void enqueue(element x) {
    if (is_full())
        printf("Queue would overflow.\n");
    else {
        q.rear++;
        q.q[q.rear] = x;
        if (q.front == -1)
            q.front++;
    }
}

void dequeue(FILE* f) {
    if (is_empty())
        printf("Queue would underflow.\n");
    else {
        fprintf(
            f, (f == stdout) ? "%d has been dequeued.\n" : "%d\n", q.q[q.front]
        );
        if (q.front == q.rear) {
            q.front = -1;
            q.rear = -1;
        } else
            q.front++;
    }
}

void multi_enqueue(char* filename) {
    FILE* f;
    element x;
    f = fopen(filename, "r");

    if (! f) {
        printf("Check if the file exists.\n");
        return;
    }

    while (! (fscanf(f, "%d", &x) == EOF) && !is_full())
        enqueue(x);

    fclose(f);
}

void multi_dequeue(char* filename, int n) {
    FILE* f;
    int i = 0;
    f = fopen(filename, "w");

    if (! f) {
        printf("Check if the file exists.\n");
        return;
    }

    while (i < n && !is_empty()) {
        dequeue(f);
        i++;
    }

    fclose(f);
}
