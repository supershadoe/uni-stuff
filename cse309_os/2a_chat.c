#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>

#define SHM_SIZE 2052
#define SHM_KEY 2345

int main() {
    int shm_id;
    char* shm_ptr;
    char* sender;
    char* msg;
    char me[3];

    shm_id = shmget(SHM_KEY, SHM_SIZE, 0666 | IPC_CREAT);
    shm_ptr = shmat(shm_id, NULL, 0);

    srand(time(0));
    sprintf(me, "%03d", rand() % 1000);

    sender = shm_ptr;
    sender[3] = '\0';
    msg = shm_ptr + 4;

    printf("I am %s\n", me);

    while (1) {
        if (!strcmp(sender, me)) continue;

        printf("Sender %s: %s", sender, msg);
        printf("Reply: ");
        fgets(msg, SHM_SIZE - 4, stdin);
        sprintf(sender, "%s", me);
    }

    return 0;
}
