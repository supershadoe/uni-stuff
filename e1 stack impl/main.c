#include <stdio.h>
#include "stack.h"

#define NAME_SIZE 101

int main() {
    int n, op;
    element x;
    char file_name[NAME_SIZE];
    printf("Enter the maximum size of stack: ");
    scanf("%d", &n);

    if (n < 1) {
        printf("Cannot create a stack with size < 1.\n");
        return 1;
    }
    create_stack(n);

    printf(
        "Available stack operations. \n"
        "1. Push\n"
        "2. Pop\n"
        "3. Peek\n"
        "4. Multipush\n"
        "5. Multipop\n"
        "6. Exit\n\n"
    );

    do {
        printf("[stack] >>> ");
        scanf("%d", &op);
        switch(op) {
            case 1:
                printf("Enter the element to push: ");
                scanf("%d", &x);
                push(x);
                break;
            case 2: pop(stdout); break;
            case 3: peek(); break;
            case 4:
                printf("Enter the filename to push elements from (limit: 100 chars): ");
                getchar();
                scanf("%[^\n]", file_name);
                multipush(file_name);
                break;
           case 5:
                printf("Enter the filename to pop the elements to (limit: 100 chars): ");
                getchar();
                scanf("%[^\n]", file_name);
                printf("Enter the number of elements to pop: ");
                scanf("%d", &n);
                multipop(file_name, n);
                break;
        }
    } while (op < 6);

    return 0;
}
