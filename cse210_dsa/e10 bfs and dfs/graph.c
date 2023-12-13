#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "queue.h"
#include "graph.h"

int time;

void display_graph(vertex* graph, int n) {
    adjnode* t;
    int i;
    printf(
        "Graph Contents:\n\n"
        " %-10s | %9s | "
        , "Name", "Adj count"
    );
    if (graph[0].t_type)
        printf("%7s | %6s | ", "Visited", "Parent");
    if (graph[0].t_type == T_BFS)
        printf("%18s | ", "Distance from root");
    else if (graph[0].t_type == T_DFS)
        printf("%4s | ", "DFN");
    printf("Adjacent vertices\n");
    for (i = 0; i < n; i++) {
        printf(" %-10s | %9d | ", graph[i].name, graph[i].adjcount);
        if (graph[i].t_type)
            printf("%7d | %6d | ", graph[i].visited, graph[i].parent);
        if (graph[i].t_type == T_BFS)
            printf("%18d | ", graph[i].dist.bfd);
        else if (graph[i].t_type == T_DFS)
            printf("%4d | ", graph[i].dist.dfn);
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
        fscanf(f, "%s %d", graph[i].name, &graph[i].adjcount);
        graph[i].visited = 0;
        graph[i].parent = -1;
        graph[i].t_type = T_UNSET;
        graph[i].dist.bfd = INT_MAX;
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

void bfs(vertex* graph, int n, int s) {
    int i, u, v;
    adjnode* temp;
    for (i = 0; i < n; i++) {
        graph[i].visited = 0;
        graph[i].parent = -1;
        graph[i].dist.bfd = INT_MAX;
        graph[i].t_type = T_BFS;
    }
    graph[s].visited = 1;
    graph[s].dist.bfd = 0;
    create_queue(n);
    enqueue(s);
    while (! is_empty()) {
        u = dequeue();
        temp = graph[u].adjptr;
        while (temp) {
            v = temp->adjver;
            if (! graph[v].visited) {
                graph[v].visited = 1;
                graph[v].parent = u;
                graph[v].dist.bfd = graph[u].dist.bfd + 1;
                enqueue(v);
            }
            temp = temp->link;
        }
    }
}

void dfs_visit(vertex* graph, int u) {
    int v;
    adjnode* temp = graph[u].adjptr;
    time++;
    graph[u].dist.dfn = time;
    graph[u].visited = 1;
    while (temp) {
        v = temp->adjver;
        if (! graph[v].visited) {
            graph[v].parent = u;
            dfs_visit(graph, v);
        }
        temp = temp->link;
    }
}

void dfs(vertex* graph, int n) {
    int i;
    for (i = 0; i < n; i++) {
        graph[i].visited = 0;
        graph[i].parent = -1;
        graph[i].t_type = T_DFS;
        graph[i].dist.dfn = INT_MAX;
    }
    time = 0;
    for (i = 0; i < n; i++)
        if (! graph[i].visited)
            dfs_visit(graph, i);
}
