#define MAX_VERT 20
#define T_UNSET 0
#define T_BFS 1
#define T_DFS 2

typedef struct adjnode {
    int adjver;
    struct adjnode* link;
} adjnode;

typedef struct {
    char name[10];
    int adjcount, visited, parent, t_type;
    union {
        int bfd, dfn;
    } dist;
    adjnode* adjptr;
} vertex;

int load_graph(vertex* graph, char* filename);

void display_graph(vertex* graph, int n);

void bfs(vertex* graph, int n, int s);

void dfs(vertex* graph, int n);

