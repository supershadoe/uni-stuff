#include <stdio.h>
#include <stdlib.h>

static int n, track_cnt, cur_head, max = 0;
static int *tracks;

static int is_out_of_range(int r) {
    if (r > track_cnt || r < 1) {
        fprintf(stderr, "Track ref out of range.\n");
        return 1;
    }
    return 0;
}

int fcfs_ds() {
    int i, seek_time = 0, s;
    int head = cur_head;
    for (i = 0; i < n; i++) {
        s = head - tracks[i];
        seek_time += s < 0 ? -s: s;
        head = tracks[i];
    }
    return seek_time;
}

int sstf_ds() {
    int i, j, shortest, s1, s2, seek_time = 0, head = cur_head;
    int *finish = calloc(sizeof(int), n);
    for (i = 0; i < n; i++) {
        shortest = -1;
        for (j = 0; j < n; j++) {
            if (finish[j]) continue;
            s1 = head - tracks[j];
            s2 = head - tracks[shortest];
            s1 = s1 < 0 ? -s1 : s1;
            s2 = s2 < 0 ? -s2 : s2;
            if (shortest < 0 || s1 < s2)
                shortest = j;
        }
        s2 = head - tracks[shortest];
        s2 = s2 < 0 ? -s2 : s2;
        seek_time += s2;
        head = tracks[shortest];
        finish[shortest] = 1;
    }
    free(finish);
    return seek_time;
}

int scan_ds() {
    return cur_head + max;
}

int main() {
    int i, fcfs, sstf, scan;

    printf("Enter number of tracks: ");
    scanf("%d", &track_cnt);
    printf("Enter the number of references: ");
    scanf("%d", &n);

    if (n < 1 || track_cnt < 1) {
        fprintf(stderr, "Count cannot be < 1\n");
        return 1;
    }

    tracks = calloc(sizeof(int), n);

    printf("Enter the track reference string: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &tracks[i]);
        if (tracks[i] > max)
            max = tracks[i];
        if (is_out_of_range(tracks[i])) return 1;
    }

    printf("Enter the current head position: ");
    scanf("%d", &cur_head);
    if (is_out_of_range(cur_head)) return 1;

    fcfs = fcfs_ds();
    sstf = sstf_ds();
    scan = scan_ds();

    printf(
        "Seek time according to each algorithm:\n"
        "FCFS: %d\n"
        "SSTF: %d\n"
        "SCAN: %d\n",
        fcfs, sstf, scan
    );

    return 0;
}    

// vim: sw=4: ts=4: sts=4: et:
