typedef int element;

typedef struct {
    int MAX_SIZE;
    int top;
    element* s;
} Stack;

void create_stack(int max_size);

int is_full();

int is_empty();

void push(element x);

void pop(FILE* f);

void peek();

void multipush(char* filename);

void multipop(char* filename, int n);
