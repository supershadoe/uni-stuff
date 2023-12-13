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

int dequeue() {
    int u = -1;
    if (is_empty())
        printf("Queue would underflow.\n");
    else {
        u = q.q[q.front];
        if (q.front == q.rear) {
            q.front = -1;
            q.rear = -1;
        } else
            q.front++;
    }
    return u;
}
