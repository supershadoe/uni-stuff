typedef struct {
    int n;
    char sn, dn, in;
    int ra;
} element;

typedef struct {
    int MAX_SIZE;
    int top;
    element* s;
} Stack;

void create_stack(int max_size);

int is_full();

int is_empty();

void push(element x);

element pop();

element peek();
