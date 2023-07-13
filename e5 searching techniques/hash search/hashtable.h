#define HASH_TABLE_SIZE 23

typedef struct hashnode {
    int data;
    struct hashnode* link;
} hashnode;

void create_hashtable();

void destroy_hashtable();

void insert_element(int x);

int hash_search(int x);
