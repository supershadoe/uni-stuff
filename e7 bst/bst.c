#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

node* insert_bst(node* root, int x) {
    node *t;
    if (root == NULL) {
        t = malloc(sizeof(node));
        t->data = x;
        t->lchild = t->rchild = NULL;
        return t;
    } else if (root->data > x)
        root->lchild = insert_bst(root->lchild, x);
    else if (root->data < x)
        root->rchild = insert_bst(root->rchild, x);
    else
        printf("Duplicate insertion cannot be performed.\n");
    return root;
}

int search_bst(node* root, int x, int count) {
    count++;
    if (! root)
        return -1;
    else if (root->data == x)
        return count;
    else
        return search_bst(
            (root->data > x) ? root->lchild : root->rchild, x, count
        );
}

node* delete_bst(node* root, int x) {
    node* t;
    if (root == NULL)
        printf("Element not found; Can't delete.");
    else if (root->data > x)
        root->lchild = delete_bst(root->lchild, x);
    else if (root->data < x)
        root->rchild = delete_bst(root->rchild, x);
    else {
        if (! root->lchild)
            return root->rchild;
        if (! root->rchild)
            return root->lchild;
        t = min_bst(root->rchild);
        root->data = t->data;
        root->rchild = delete_bst(root->rchild, t->data);
    }
    return root;
}

node* min_bst(node* root) {
    if (root && root->lchild)
        return min_bst(root->lchild);
    return root;
}

node* max_bst(node* root) {
    if (root && root->rchild)
        return max_bst(root->rchild);
    return root;
}

void preorder(node* root) {
    if (root) {
        printf("%d ", root->data);
        preorder(root->lchild);
        preorder(root->rchild);
    }
}

void inorder(node* root) {
    if (root) {
        inorder(root->lchild);
        printf("%d ", root->data);
        inorder(root->rchild);
    }
}

void postorder(node* root) {
    if (root) {
        postorder(root->lchild);
        postorder(root->rchild);
        printf("%d ", root->data);
    }
}
