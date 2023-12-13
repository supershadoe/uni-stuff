typedef int element;

typedef struct {
    int MAX_SIZE, front, rear;
    element* q;
} Queue;

void create_queue(int max_size);

int is_full();

int is_empty();

void enqueue(element x);

void dequeue(FILE* f);

void multi_enqueue(char* filename);

void multi_dequeue(char* filename, int n);
