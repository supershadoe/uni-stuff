#include <stdio.h>

#define PROC_CNT 6
#define RES_CNT 4

int allocation[PROC_CNT][RES_CNT] = {
    {2, 0, 2, 1},
    {0, 1, 1, 1},
    {4, 1, 0, 2},
    {1, 0, 0, 1},
    {1, 1, 0, 0},
    {1, 0, 1, 1},
};

int claim[PROC_CNT][RES_CNT] = {
    {9, 5, 5, 5},
    {2, 2, 3, 3},
    {7, 5, 4, 4},
    {3, 3, 3, 2},
    {5, 2, 2, 1},
    {4, 4, 4, 4},
};

int resources[RES_CNT] = {15, 6, 9, 10};

int available[RES_CNT];

int finish[PROC_CNT], safe_seq[PROC_CNT];

void init() {
    int i, j, sum;
    for (i = 0; i < RES_CNT; i++) {
        sum = 0;
        for (j = 0; j < PROC_CNT; j++) {
            sum += allocation[j][i];
        }
        available[i] = resources[i] - sum;
    }
    for (i = 0; i < PROC_CNT; i++)
        safe_seq[i] = 0;
}

int deadlock_detect() {
    int i, j, found, finish_cnt = 0;
    while (finish_cnt < PROC_CNT) {
        found = 0;
        for (i = 0; i < PROC_CNT; i++) {
            if (finish[i]) continue;
            for (j = 0; j < RES_CNT; j++) {
                if (claim[i][j] - allocation[i][j] > available[j]) {
                    break;
                }
            }
            if (j == RES_CNT) {
                found = 1;
                for (j = 0; j < RES_CNT; j++) {
                    available[j] += allocation[i][j];
                    allocation[i][j] = 0;
                    claim[i][j] = 0;
                }
                finish[i] = 1;
                safe_seq[finish_cnt] = i;
                finish_cnt++;
            }
        }
        if (!found) break;
    }
    return found;
}

int main() {
    int res;

    init();
    res = deadlock_detect();
    printf("The system is ");
    if (!res)
        printf("not ");
    printf("in a safe state.\n");

    return 0;
}
