#include <stdio.h>
#include <stdlib.h>

static struct process {
    int at, bt, actual_bt, ft, status, cpu;
} *ready_queue;

static int *cpus, *idle_time, cpu_count = 0;

static int clock = 0, n = 0;

static void init_res() {
    ready_queue = calloc(sizeof(struct process), n);
    cpus = calloc(sizeof(int), cpu_count);
    idle_time = calloc(sizeof(int), cpu_count);
}

static void rel_res() {
    free(ready_queue);
    free(cpus);
    free(idle_time);
}

int dispatcher(int is_mp) {
    int i, can_dispatch = 0;
    struct process *queue = ready_queue;
    for (i = 0; i < n; i++) {
        can_dispatch =
            ready_queue[i].at <= clock
            && !ready_queue[i].status;
        if (is_mp)
            can_dispatch = can_dispatch && ready_queue[i].cpu < 0;
        if (can_dispatch)
            return i;
    }
    return -1;
}

void simulate_mp() {
    int i = 0, j, pid;
    struct process *temp;
    while (i < n) {
        for (j = 0; j < cpu_count; j++) {
            pid = cpus[j];
            if (pid < 0) {
                pid = dispatcher(1);
                if (pid < 0) {
                    idle_time[j]++;
                    continue;
                }
                cpus[j] = pid;
                ready_queue[pid].cpu = j;
            }
            temp = ready_queue + pid;
            temp->bt--;
            if (temp->bt == 0) {
                temp->status = 1;
                temp->ft = clock + 1;
                cpus[j] = -1;
                i++;
            }
        }
        clock++;
    }
}

void simulate() {
    int i = 0, pid;
    struct process *temp;

    while (i < n) {
        pid = dispatcher(0);
        if (pid < 0) {
            idle_time[0]++;
            continue;
        }
        temp = ready_queue + pid;
        temp->ft = clock + temp->bt;
        temp->status = 1;
        clock += temp->bt;
        i++;
    }
}

int main() {
    struct process *temp;
    int i, tt, wt;
    float m_tt = 0, m_wt = 0, mp_m_tt = 0, mp_m_wt = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the number of CPUs: ");
    scanf("%d", &cpu_count);

    if (n < 1) {
        fprintf(stderr, "Number of processes cannot be less than 1.");
        return 1;
    }

    if (cpu_count < 1) {
        fprintf(stderr, "Number of CPUs cannot be less than 1.");
        return 1;
    }

    init_res();

    printf(
        "Enter the info about each process.\n"
        "AT\tBT\n"
    );
    for (i = 0; i < n; i++) {
        temp = ready_queue + i;
        scanf("%d%d", &temp->at, &temp->bt);
        temp->cpu = -1;
        temp->status = 0;
        temp->actual_bt = temp->bt;
    }

    for (int i = 0; i < cpu_count; i++)
        cpus[i] = -1;

    simulate_mp();

    printf(
        "Multiprocessor simulation results are as follows.\n"
        "FT\tTT\tWT\tCPU\n"
    );
    for (i = 0; i < n; i++) {
        temp = ready_queue + i;
        tt = temp->ft - temp->at;
        mp_m_tt = ((m_tt * i) + tt) / (i + 1);
        wt = tt - temp->actual_bt;
        mp_m_wt = ((m_wt * i) + wt) / (i + 1);
        printf("%d\t%d\t%d\t%d\n", temp->ft, tt, wt, temp->cpu + 1);
    }

    printf("Mean TT: %.2f\nMean WT: %.2f\n", mp_m_tt, mp_m_wt);

    printf("Idle time of CPUs:\nCPU\tIdle time\n");
    for (i = 0; i < cpu_count; i++)
        printf("%d\t%d\n", i+1, idle_time[i]);

    for (i = 0; i < n; i++) {
        temp = ready_queue + i;
        temp->bt = temp->actual_bt;
        temp->status = 0;
    }

    simulate();
    
    printf(
        "Uniprocessor simulation results are as follows.\n"
        "FT\tTT\tWT\n"
    );
    for (i = 0; i < n; i++) {
        temp = ready_queue + i;
        tt = temp->ft - temp->at;
        m_tt = ((m_tt * i) + tt) / (i + 1);
        wt = tt - temp->actual_bt;
        m_wt = ((m_wt * i) + wt) / (i + 1);
        printf("%d\t%d\t%d\n", temp->ft, tt, wt);
    }

    printf("Mean TT: %.2f\nMean WT: %.2f\n", m_tt, m_wt);

    printf("Idle time of CPU: %d\n", idle_time[0]);

    if (mp_m_tt > m_tt && mp_m_wt > m_wt) {
        printf("Overall Single Processor performance was better.\n");
    } else {
        printf("Overall Multiprocessor performance was better.\n");
    }

    rel_res();
    return 0;
}
