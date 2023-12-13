#include <stdio.h>
#include "stack.h"
#define FILE_NAME_SIZE 101

#define CASE_MOVE_DISC 1
#define CASE_REC_POP 2
#define CASE_END_REC 3

void hanoi(int, FILE*);

int main() {
    int n;
    char file_name[FILE_NAME_SIZE];
    FILE* f;

    printf("Enter the number of discs: ");
    scanf("%d", &n);

    printf("Enter the file to store the moves in: ");
    scanf("%*[\n]%[^\n]", file_name);

    f = fopen(file_name, "w");
    if (! f) {
        printf("Cannot open file for writing output.\n");
        return 1;
    }

    hanoi(n, f);
    fclose(f);
    return 0;
}

void hanoi(int n, FILE* f) {
    // for swapping needles between moves
    char temp;
    // to hold the current move
    element move = {n, 'A', 'C', 'B', CASE_END_REC};
    // initializing the stack
    create_stack(n + 1);

    stack_moves:
        // eqv to 1st half of calling function in recursive hanoi algo
        push(move);
        // if n is non-zero, reduce n and swap dn and in
        if (move.n) {
            move.n--;
            temp = move.in;
            move.in = move.dn;
            move.dn = temp;
            move.ra = CASE_MOVE_DISC;
            // recursively do the above operations
            goto stack_moves;
        } else
            // if n is zero, go to move_disc or recursively_pop
            goto process_ra;

    move_disc:
        // equivalent to 2nd half of calling function
        // current move useless as it would have been printed earlier or n = 0
        pop();
        // get prev move in stack
        move = peek();
        fprintf(f, "Move disc %d from %c to %c.\n", move.n, move.sn, move.dn);
        // reduce n and swap sn and in
        move.n--;
        temp = move.sn;
        move.sn = move.in;
        move.in = temp;
        move.ra = CASE_REC_POP;
        // effectively removes this element and also the previous one
        goto stack_moves;

    recursively_pop:
        // eqv to end of calling function
        pop();
        move = peek();
        goto process_ra;

    process_ra:
        switch(move.ra) {
            case CASE_MOVE_DISC: goto move_disc;
            case CASE_REC_POP: goto recursively_pop;
            case CASE_END_REC: return;
            default: printf("Invalid return address.\n");
        }
}
