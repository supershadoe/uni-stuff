#include <stdio.h>
#include "queue.h"

#define NAME_SIZE 101

int main() {
    int n, op;
    element x;
    char file_name[NAME_SIZE];
    printf("Enter the maximum size of queue: ");
    scanf("%d", &n);

    if (n < 1) {
        printf("Cannot create a queue with size < 1.\n");
        return 1;
    }
    create_queue(n);

    printf(
        "Available queue operations. \n"
        "1. Enqueue\n"
        "2. Dequeue\n"
        "3. Multienqueue\n"
        "4. Multidequeue\n"
        "5. Exit\n\n"
    );

    do {
        printf("[queue] >>> ");
        scanf("%d", &op);
        switch(op) {
            case 1:
                printf("Enter the element to enqueue: ");
                scanf("%d", &x);
                enqueue(x);
                break;
            case 2: dequeue(stdout); break;
            case 3:
                printf("Enter filename (limit 100 chars): ");
                getchar();
                scanf("%[^\n]", file_name);
                multi_enqueue(file_name);
                break;
           case 4:
                printf("Enter filename (limit 100 chars): ");
                getchar();
                scanf("%[^\n]", file_name);
                printf("Enter the number of elements to dequeue: ");
                scanf("%d", &n);
                multi_dequeue(file_name, n);
                break;
        }
    } while (op < 5);

    return 0;
}
