#include <stdio.h>
#include <stdlib.h>
#include "poly.h"

poly* create_poly() {
    poly* p = malloc(sizeof(poly));
    p->first = NULL;
    p->last = NULL;
    return p;
}

void display_poly(poly* p) {
    term *temp = p->first;
    if (!temp)
        printf("No elements to display: The list is empty.");
    while (temp) {
        if (temp->coef >= 0)
            printf("+");
        printf("%.2fx^%d ", temp->coef, temp->exp);
        temp = temp->link;
    }
    printf("\n");
}

void delete_poly(poly* p) {
    term *cur, *next;
    cur = p->first;
    while(cur) {
        next = cur->link;
        free(cur);
        cur = next;
    }
    free(p);
}

void insert_at_end(poly* p, float coef, int exp) {
    term* t = malloc(sizeof(term));
    t->coef = coef;
    t->exp = exp;
    t->link = NULL;
    if (p->last) {
        p->last->link = t;
        p->last = t;
    } else
        p->first = p->last = t;
}

void insert_ord(poly* p, float coef, int exp) {
    term* t = malloc(sizeof(term)), *temp;
    t->coef = coef;
    t->exp = exp;
    if (!p->first) {
        t->link = NULL;
        p->first = p->last = t;
    } else if (p->first->exp < exp) {
        t->link = p->first;
        p->first = t;
    } else if (p->first->exp == exp) {
        coef += p->first->coef;
        if (coef)
            p->first->coef = coef;
        else {
            free(t);
            t = p->first;
            p->first = p->first->link;
        }
        free(t);
    } else {
        temp = p->first;
        while (temp->link && temp->link->exp > exp) {
            temp = temp->link;
        }
        if (!temp->link) {
            temp->link = t;
            t->link = NULL;
            p->last = t;
        } else if (temp->link->exp < exp) {
            t->link = temp->link;
            temp->link = t;
        } else if (temp->link->exp == exp) {
            coef += temp->link->coef;
            if (coef)
                temp->link->coef = coef;
            else {
                free(t);
                t = temp->link;
                temp->link = temp->link->link;
            }
            free(t);
        }
    }
}

poly* add_poly(poly* p1, poly* p2) {
    poly* res = create_poly();
    float c;
    int e;
    term *t1, *t2;
    t1 = p1->first;
    t2 = p2->first;
    while(t1 && t2) {
        if (t1->exp == t2->exp) {
            c = t1->coef + t2->coef;
            if (c) insert_at_end(res, c, t1->exp);
            t1 = t1->link;
            t2 = t2->link;
        } else if (t1->exp > t2->exp) {
            insert_at_end(res, t1->coef, t1->exp);
            t1 = t1->link;
        } else {
            insert_at_end(res, t2->coef, t2->exp);
            t2 = t2->link;
        }
    }
    while (t1) {
        insert_at_end(res, t1->coef, t1->exp);
        t1 = t1->link;
    }
    while(t2) {
        insert_at_end(res, t2->coef, t2->exp);
        t2 = t2->link;
    }
    return res;
}

