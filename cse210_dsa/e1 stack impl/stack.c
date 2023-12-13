#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

static Stack s;

void create_stack(int max_size) {
    s.s = calloc(sizeof(element), max_size);
    s.MAX_SIZE = max_size;
    s.top = -1;
}

int is_full() {
    return s.top == s.MAX_SIZE - 1;
}

int is_empty() {
    return s.top == -1;
}

void push(element x) {
    if (is_full())
        printf("Stack would overflow.\n");
    else {
        s.top++;
        s.s[s.top] = x;
    }
}

void pop(FILE* f) {
    if (is_empty())
        printf("Stack would underflow.\n");
    else {
        if (f == stdout)
            printf("The popped element is ");
        fprintf(f, "%d\n", s.s[s.top]);
        s.top--;
    }
}

void peek() {
    if (is_empty())
        printf("Stack is empty.\n");
    else
        printf("The topmost element is %d\n", s.s[s.top]);
}

void multipush(char* filename) {
    FILE* f;
    element x;
    f = fopen(filename, "r");

    if (! f) {
        printf("Check if the file exists.\n");
        return;
    }
    
    while (! ( (fscanf(f, "%d", &x) == EOF) || is_full() ))
        push(x);

    fclose(f);
}

void multipop(char* filename, int n) {
    FILE* f;
    int i = 0;
    f = fopen(filename, "w");

    if (! f) {
        printf("Check if the file exists.\n");
        return;
    }

    while (i < n && !is_empty()) {
        pop(f);
        i++;
    }

    fclose(f);
}

