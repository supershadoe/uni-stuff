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

element pop() {
    element x = {0, 0, 0, 0, 0};
    if (is_empty())
        printf("Stack would underflow.\n");
    else {
        x = s.s[s.top];
        s.top--;
    }
    return x;
}

element peek() {
    element x = {0, 0, 0, 0, 0};
    if (is_empty())
        printf("Stack is empty.\n");
    else
        x = s.s[s.top];
    return x;
}

