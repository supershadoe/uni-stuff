#include <stdio.h>
#include <stdlib.h>

struct process {
    int at, bt, pr, status, ft;
    // Arrival time, Burst time, Priority, Status, Finish time
};

struct process* fcfs(struct process* queue, int n) {
    int i;
    for (i = 0; i < n; i++)
        if (!queue[i].status)
            return queue + i;
}

struct process* sjf(struct process* queue, int n, int clock) {
    int i, bt = -1;
    for (i = 0; i < n; i++)
        if (!queue[i].status)
            if (queue[i].at <= clock)
                if (bt < 0 || queue[i].bt < queue[bt].bt)
                    bt = i;
    return queue + bt;
}

struct process* priority_sch(struct process* queue, int n, int clock) {
    int i, hp = -1;
    for (i = 0; i < n; i++)
        if (!queue[i].status)
            if (queue[i].at <= clock)
                if (hp < 0 || queue[i].pr < queue[hp].pr)
                    hp = i;
    return queue + hp;
}

struct process* dispatcher(const struct process* queue, int n, int clock) {
//    return fcfs(queue, n);
//    return priority_sch(queue, n, clock);
    return sjf(queue, n, clock);
}

const int use_pr = 0;

int main() {
    int n, i, clock = 0, tt, wt;
    float norm_tt, m_tt, m_wt, m_norm_tt;
    struct process *ready_queue, *process;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    if (n < 1) {
        printf("Process count can't be less than one.\n");
        return 1;
    }

    ready_queue = calloc(sizeof(struct process), n);

    printf("Enter the details of the processes as a table.\n");
    printf("AT | BT");
    printf(use_pr ? " | Priority\n": "\n");
    process = ready_queue;
    for (i = 0; i < n; i++) {
        scanf("%d%d", &process->at, &process->bt);
        if (use_pr) scanf("%d", &process->pr);
        process++;
    }

    i = 0;
    while (i < n) {
        process = dispatcher(ready_queue, n, clock);
        process->ft += clock + process->bt;
        process->status = 1;
        clock += process->bt;
        i++;
    }

    printf(
        "Process\tFT\tTT\tWT\tNormalized TT\n"
        "*******\t**\t**\t**\t*************\n"
    );

    process = ready_queue;
    for (i = 0; i < n; i++) {
        tt = process->ft - process->at;
        wt = tt - process->bt;
        norm_tt = (float) tt / process->bt;
        m_tt = (m_tt * i + tt) / (i + 1);
        m_wt = (m_wt * i + wt) / (i + 1);
        m_norm_tt = (m_norm_tt * i + norm_tt) / (i + 1);
        printf("%d\t%d\t%d\t%d\t%.2f\n", i + 1, process->ft, tt, wt, norm_tt);
        process++;
    }
    
    printf(
        "Mean\tTT\tWT\tNormalized TT\n"
        "\t%.2f\t%.2f\t%.2f\n", m_tt, m_wt, m_norm_tt
    );

    free(ready_queue);
    return 0;
}
