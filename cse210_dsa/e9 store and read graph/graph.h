#define MAX_VERT 20

typedef struct adjnode {
    int adjver;
    struct adjnode* link;
} adjnode;

typedef struct {
    char name[10];
    int adjcount;
    adjnode* adjptr;
} vertex;

int construct_graph(vertex* graph);

int load_graph(vertex* graph, char* filename);

void display_graph(vertex* graph, int n);

void store_graph(vertex* graph, int n, char* filename);

