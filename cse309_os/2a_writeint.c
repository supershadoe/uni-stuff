#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_KEY 1002
#define SHM_SIZE 10 * 4 // bytes

int main() {
    int* shm_ptr;
    int shm_id;
    int i;
    
    shm_id = shmget(SHM_KEY, SHM_SIZE, 0666 | IPC_CREAT); // key, size, shmflg
    printf("Shared memory key %d and id %d\n", SHM_KEY, shm_id);
    shm_ptr = shmat(shm_id, NULL, 0); // id, ptr to attach to, flags
    printf("Shared memory --> %p\n", shm_ptr);

    printf("Enter 10 numbers to write to shared memory: ");
    for (i = 0; i < SHM_SIZE / sizeof(int); i++)
        scanf("%d", shm_ptr+i);

    printf("Numbers stored in shared memory are: ");
    for (i = 0; i < SHM_SIZE / sizeof(int); i++)
        printf("%d ", shm_ptr[i]);
    printf("\n");
    return 0;
}
