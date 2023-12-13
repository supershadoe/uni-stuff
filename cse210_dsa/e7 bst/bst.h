typedef struct node {
    struct node* lchild;
    int data;
    struct node* rchild;
} node;

node* insert_bst(node* root, int x);

int search_bst(node* root, int x, int count);

node* delete_bst(node* root, int x);

node* min_bst(node* root);

node* max_bst(node* root);

void preorder(node* root);

void inorder(node* root);

void postorder(node* root);

