#include <stdio.h>
#include <stdlib.h>
#include "dll.h"

static struct headnode {
    node* first;
    node* last;
    int count;
} *head = NULL;

void create_dll() {
    head = malloc(sizeof(struct headnode));
    head->first = NULL;
    head->last = NULL;
    head->count = 0;
}

void destroy_dll() {
    int i;
    node *cur, *next;
    cur = head->first;
    for (i = 0; i < head->count; i++) {
        next = cur->next;
        free(cur);
        cur = next;
    }
    free(head);
    head = NULL;
}

void insert_odll(int x) {
    node *cur = head->first, *temp = malloc(sizeof(node));
    temp->data = x;
    while (cur) {
        if (cur->data > x) {
            temp->prev = cur->prev;
            temp->next = cur;
            if (cur->prev)
                cur->prev->next = temp;
            cur->prev = temp;
            head->count++;
            return;
        }
        cur = cur->next;
    }
    temp->prev = head->last;
    temp->next = NULL;
    head->count++;    
    head->last = temp;
    if (head->last->prev)
        head->last->prev->next = temp;
    if (! head->first)
        head->first = temp;
}

void remove_odll(int x) {
    node* cur = head->first;
    while (cur) {
        if (cur->data == x) {
            if (cur->prev)
                cur->prev->next = cur->next;
            if (cur->next)
                cur->next->prev = cur->prev;
            if (cur == head->first)
                head->first = cur->next;
            if (cur == head->last)
                head->last = cur->prev;
            free(cur);
            head->count--;
            return;
        }
        cur = cur->next;
    }
    printf("Element not found.\n");
}

int search_odll(int x) {
    node* cur = head->first;
    int i = -1;
    while (cur) {
        i++;
        if (cur->data == x)
            return i;
        cur = cur->next;
    }
    return -1;
}

void display_FTOL() {
    node* cur = head->first;
    if (!cur)
        printf("DLL is empty.\n");
    else
        while (cur) {
            printf("%d\n", cur->data);
            cur = cur->next;
        }
}

void display_LTOF() {
    node* cur = head->last;
    if (!cur)
        printf("DLL is empty.\n");
    else
        while (cur) {
            printf("%d\n", cur->data);
            cur = cur->prev;
        }
}

