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

void bankers_init() {
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

int res_req(int req[RES_CNT], int pid) {
    int i;
    for (i = 0; i < RES_CNT; i++) {
        if (! (req[i] <= available[i] &&
            req[i] <= claim[pid][i] - allocation[pid][i])) {
            return 0;
        }
    }
    return 1;
}

int safety() {
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

    int req[] = {3, 2, 3, 3};
    int pid = 5;

    bankers_init();
    res = res_req(req, pid);
    if (!res) {
        printf("Cannot grant the request.\n");
        return 0;
    }
    res = safety();
    if (!res) {
        printf("The system is not in a safe state.\n");
        return 0;
    }

    printf("The system is in a safe state.\nSafe seq: ");
    for (int i = 0; i < PROC_CNT; i++)
        printf("P%d ", safe_seq[i]);
    printf("\n");

    return 0;
}
