#include <stdio.h>
#include "hashtable.h"

int main() {
    int x, pos;
    FILE *f;

    create_hashtable();

    f = fopen("input.txt", "r");
    if (f == NULL) {
        printf("Check if the file exists.\n");
        return 1;
    }

    while (fscanf(f, "%d", &x) != EOF)
        insert_element(x);

    printf("Enter the element to search for: ");
    scanf("%d", &x);

    pos = hash_search(x);
    if (pos)
        printf("The element was found at position %d in key %d.\n", pos, x % HASH_TABLE_SIZE);
    else
        printf("The element wasn't found in the hash table.\n");

    destroy_hashtable();
    return 0;
}
