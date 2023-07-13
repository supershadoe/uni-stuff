#include <stdio.h>
#include "graph.h"
#define FNAME_LEN 100

int main() {
    vertex graph[MAX_VERT];
    char filename[FNAME_LEN];
    int vert_count = -1, ch;
    
    printf(
        "Enter what operation to perform.\n"
        "1. Construct a graph from manual input.\n"
        "2. Load a graph from disk.\n"
        "3. Display the graph on console.\n"
        "4. Store the graph on disk.\n"
        "5. Exit.\n\n"
    );
    do {
        printf("[choice] >>> ");
        scanf("%d", &ch);
        switch(ch) {
            case 1:
                vert_count = construct_graph(graph);
                break;
            case 2:
                printf("[filename] ? ");
                scanf("%s", filename);
                vert_count = load_graph(graph, filename);
                break;
            case 3:
                if (vert_count > 0)
                    display_graph(graph, vert_count);
                else
                    printf("The graph is empty.\n");
                break;
            case 4:
                printf("[filename] ? ");
                scanf("%s", filename);
                if (vert_count >= 0)
                    store_graph(graph, vert_count, filename);
                else
                    printf("The graph is empty.\n");
                break;
        }
    } while (ch > 0 && ch < 5);

    return 0;
}
