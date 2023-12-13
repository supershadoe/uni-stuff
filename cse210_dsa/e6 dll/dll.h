typedef struct node {
    int data;
    struct node* prev;
    struct node* next;
} node;

void create_dll();

void destroy_dll();

void insert_odll(int x);

void remove_odll(int x);

int search_odll(int x);

void display_FTOL();

void display_LTOF();

