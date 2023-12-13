#include <stdio.h>
#include "bst.h"

int main() {
    node* bst = NULL;
    int choice, temp;
    printf(
        "Available operations.\n"
        "1. Insertion.\n"
        "2. Deletion.\n"
        "3. Searching.\n"
        "4. Find max element.\n"
        "5. Find min element.\n"
        "6. Pre-order traversal.\n"
        "7. In-order traversal.\n"
        "8. Post-order traversal.\n"
        "9. Exit.\n\n"
    );
    do {
        printf("[bst] >>> ");
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                printf("[insert] Element? ");
                scanf("%d", &temp);
                bst = insert_bst(bst, temp);
                break;
            case 2:
                printf("[delete] Element? ");
                scanf("%d", &temp);
                bst = delete_bst(bst, temp);
                break;
            case 3:
                printf("[search] Element? ");
                scanf("%d", &temp);
                temp = search_bst(bst, temp, -1);
                if (temp > -1)
                    printf("The element was found at level %d.\n", temp);
                else
                    printf("The element was not found.\n");
                break;
            case 4:
                if (bst)
                    printf("The greatest element in the BST is %d.\n", max_bst(bst)->data);
                else
                    printf("The tree is empty.\n");
                break;
            case 5:
                if (bst)
                    printf("The least element in the BST is %d.\n", min_bst(bst)->data);
                else
                    printf("The tree is empty.\n");
                break;
            case 6:
                if (bst) {
                    printf("[pre-order]: ");
                    preorder(bst);
                    printf("\n");
                } else
                    printf("The BST is empty.\n");
                break;
            case 7:
                if (bst) {
                    printf("[in-order]: ");
                    inorder(bst);
                    printf("\n");
                } else
                    printf("The BST is empty.\n");
                break;
            case 8:
                if (bst) {
                    printf("[post-order]: ");
                    postorder(bst);
                    printf("\n");
                } else
                    printf("The BST is empty.\n");
                break;
        }
    } while (choice > 0 && choice < 9);
    return 0;
}
