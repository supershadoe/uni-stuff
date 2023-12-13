#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"

static hashnode** hashtable;

void create_hashtable() {
    hashtable = calloc(sizeof(hashnode*), HASH_TABLE_SIZE);
}

void destroy_hashtable() {
    int i;
    hashnode *cur, *next;
    for (i = 0; i < HASH_TABLE_SIZE; i++) {
        cur = hashtable[i];
        while (cur) {
            next = cur->link;
            free(cur);
            cur = next;
        }
    }
    free(hashtable);
    hashtable = NULL;
}

void insert_element(int x) {
    int index = x % HASH_TABLE_SIZE;
    hashnode *t = malloc(sizeof(hashnode));
    t->data = x;
    t->link = hashtable[index];
    hashtable[index] = t;
}

int hash_search(int x) {
    int pos = 0;
    hashnode* temp = hashtable[x % HASH_TABLE_SIZE];
    while (temp) {
        pos++;
        if (x == temp->data)
            return pos;
        temp = temp->link;
    }
    return 0;
}

