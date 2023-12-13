#include <stdio.h>
#include "dll.h"

int main() {
    int op, x;
    create_dll();

    printf(
        "Available operations on DLL:\n"
        "1. Insertion\n"
        "2. Deletion\n"
        "3. Searching\n"
        "4. Displaying first to last\n"
        "5. Displaying last to first\n"
        "6. Exit\n\n"
    );

    do {
        printf("[dll] >>> ");
        scanf("%d", &op);
        switch(op) {
            case 1:
                printf("[dll|insert] > ");
                scanf("%d", &x);
                insert_odll(x);
                break;
            case 2:
                printf("[dll|delete] > ");
                scanf("%d", &x);
                remove_odll(x);
                break;
            case 3:
                printf("[dll|search] > ");
                scanf("%d", &x);
                x = search_odll(x);
                if (x > -1)
                    printf("The element was found at position %d.\n", x);
                else
                    printf("The element was not found in the list.\n");
                break;
            case 4:
                display_FTOL();
                break;
            case 5:
                display_LTOF();
                break;
        }
    } while (op > 0 && op < 6);

    destroy_dll();

    return 0;
}
