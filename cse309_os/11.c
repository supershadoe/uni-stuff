#include <stdio.h>
#include <stdlib.h>

static int* ref_string;
static int ref_count, frame_count;

int fifo_pr() {
    int page_faults = 0, cur_head = 0, i, j;
    int *frames = calloc(sizeof(int), frame_count);
    
    for (i = 0; i < frame_count; i++)
        frames[i] = -1;

    for (i = 0; i < ref_count; i++) {
        for (j = 0; j < frame_count; j++)
            if (frames[j] == ref_string[i])
                break;

        if (j == frame_count) {
            page_faults++;
            frames[cur_head] = ref_string[i];
            cur_head = (cur_head + 1) % frame_count;
        }
    }

    free(frames);
    return page_faults;
}

int lru_pr() {
    int page_faults = 0, lru, i, j;
    int *frames = calloc(sizeof(int), frame_count);
    int *page_hits = calloc(sizeof(int), frame_count);

    for (i = 0; i < frame_count; i++) {
        frames[i] = -1;
        page_hits[i] = 0;
    }

    for (i = 0; i < ref_count; i++) {
        lru = -1;
        for (j = 0; j < frame_count; j++) {
            if (lru < 0 || page_hits[j] < page_hits[lru])
                lru = j;
            if (frames[j] == ref_string[i]) {
                page_hits[j]++;
                break;
            }
        }

        if (j == frame_count) {
            page_faults++;
            frames[lru] = ref_string[i];
            page_hits[lru] = 1;
        }
    }

    free(frames);
    free(page_hits);
    return page_faults;
}

int opr_pr() {
    int page_faults = 0, i, j, k, furthest, furthest_hit;
    int *frames = calloc(sizeof(int), frame_count);

    for (i = 0; i < frame_count; i++)
        frames[i] = -1;

    for (i = 0; i < ref_count; i++) {
        for (j = 0; j < frame_count; j++)
            if (frames[j] == ref_string[i])
                break;

        if (j == frame_count) {
            page_faults++;

            furthest_hit = -1;
            furthest = -1;
            for (k = 0; k < frame_count; k++) {
                for (j = i + 1; j < ref_count; j++) {
                    if (frames[k] == ref_string[j]) {
                        if (j > furthest_hit) {
                            furthest_hit = j;
                            furthest = k;
                        }
                        break;
                    }
                }
                if (j >= ref_count) {
                    furthest_hit = j;
                    furthest = k;
                    break;
                }
            }

            frames[furthest] = ref_string[i];
        }
    }

    free(frames);
    return page_faults;
}

int main() {
    int i, fifo, lru, opr;

    printf("Enter the number of memory frames: ");
    scanf("%d", &frame_count);
    printf("Number of page references: ");
    scanf("%d", &ref_count);

    if (frame_count < 1 || ref_count < 1) {
        fprintf(stderr, "Count cannot be less than 1.\n");
        return 1;
    }

    ref_string = calloc(sizeof(int), ref_count);

    printf("Enter the page reference string: ");
    for (i = 0; i < ref_count; i++)
        scanf("%d", &ref_string[i]);

    fifo = fifo_pr();
    lru = lru_pr();
    opr = opr_pr();

    printf("Number of page faults in FIFO: %d\n", fifo);
    printf("Number of page faults in LRU: %d\n", lru);
    printf("Number of page faults in Optimal Page Replacement: %d\n", opr);

    return 0;
}
