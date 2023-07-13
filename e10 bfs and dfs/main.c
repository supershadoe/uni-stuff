#include <stdio.h>
#include "graph.h"
#define FNAME_LEN 100

int main() {
    vertex graph[MAX_VERT];
    char filename[FNAME_LEN];
    int vert_count = -1, s, ch;

    printf("Path on disk to graph? ");
    scanf("%s", filename);
    vert_count = load_graph(graph, filename);
    
    if (vert_count <= 0) {
        printf("The graph is empty.\n");
        return 1;
    }

    display_graph(graph, vert_count);

    printf("\nEnter the index of the node to perform the traversal from: ");
    scanf("%d", &s);
    if (s >= vert_count || s < 0) {
        printf("That node doesn't exist.\n");
        return 1;
    }

    printf("Enter the traversal to perform (1 - BFS, 2 - DFS): ");
    scanf("%d", &ch);
    if (ch == 1)
        bfs(graph, vert_count, s);
    else if (ch == 2)
        dfs(graph, vert_count);
    else {
        printf("No such option.\n");
        return 1;
    }

    if (vert_count > 0)
        display_graph(graph, vert_count);
    else
        printf("The graph is empty.\n");

    return 0;
}
