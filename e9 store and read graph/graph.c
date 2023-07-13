#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int construct_graph(vertex* graph) {
    int adj_ver, i, j, m, n;
    adjnode *p, *t;
    printf("\nEnter number of vertices: ");
    scanf("%d", &n);

    if (n < 1) {
        printf("Cannot have a graph with 0 or less vertices.\n");
        return -1;
    } else if (n > MAX_VERT) {
        printf("Cannot have more than %d vertices in the graph.\n", MAX_VERT);
        return -1;
    }

    for (i = 0; i < n; i++) {
        printf("[vertex-%d] name? ", i+1);
        scanf("%s", graph[i].name);
        printf("[%s] number of adjacent vertices? ", graph[i].name);
        scanf("%d", &graph[i].adjcount);
        graph[i].adjptr = NULL;
        for (j = 0; j < graph[i].adjcount; j++) {
            printf("[index %d]? ", j+1);
            scanf("%d", &adj_ver);
            t = malloc(sizeof(adjnode));
            t->adjver = adj_ver;
            t->link = NULL;
            if (! graph[i].adjptr)
                graph[i].adjptr = t;
            else
                p->link = t;
            p = t;
        }
    }

    return n;
}

void display_graph(vertex* graph, int n) {
    adjnode* t;
    int i;
    printf(
        "Graph Contents:\n\n"
        " %-10s | Adjacent vertices\n"
        , "Name"
    );
    for (i = 0; i < n; i++) {
        printf(" %-10s | ", graph[i].name);
        t = graph[i].adjptr;
        if (!t)
            printf("None");
        else
            while(t) {
                printf("%d", t->adjver);
                if (t->link)
                    printf(", ");
                t = t->link;
            }
        printf("\n");
    }
}

void store_graph(vertex* graph, int n, char* filename) {
    adjnode* t;
    int i;
    FILE* f = fopen(filename, "w");
    
    if (!f) {
        printf("Cannot write to this file.\n");
        return;
    }

    printf("Storing the graph in %s.\n", filename);
    fprintf(f, "%d\n", n);
    for (i = 0; i < n; i++) {
        fprintf(f, "%-10s %d ", graph[i].name, graph[i].adjcount);
        t = graph[i].adjptr;
        if (!t)
            printf("None");
        else
            while(t) {
                fprintf(f, "%d ", t->adjver);
                t = t->link;
            }
        fprintf(f, "\n");
    }

    fclose(f);
}

int load_graph(vertex* graph, char* filename) {
    int adj_ver, i, j, n;
    adjnode *p, *t;
    FILE* f = fopen(filename, "r");

    if (!f) {
        printf("Check if the file exists.\n");
        return -1;
    }

    fscanf(f, "%d", &n);

    if (n < 1 || n > MAX_VERT) {
        printf("Corrupt data.\n");
        return -1;
    }

    for (i = 0; i < n; i++) {
        fscanf(f, "%s", graph[i].name);
        fscanf(f, "%d", &graph[i].adjcount);
        graph[i].adjptr = NULL;
        for (j = 0; j < graph[i].adjcount; j++) {
            fscanf(f, "%d", &adj_ver);
            t = malloc(sizeof(adjnode));
            t->adjver = adj_ver;
            t->link = NULL;
            if (! graph[i].adjptr)
                graph[i].adjptr = t;
            else
                p->link = t;
            p = t;
        }
    }

    fclose(f);
    return n;
}
