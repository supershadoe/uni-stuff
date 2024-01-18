#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_KEY 1003
#define SHM_SIZE 1024 // bytes

int main() {
    char inp_buf[SHM_SIZE];
    void* shm_ptr;
    int shm_id;
    
    shm_id = shmget(SHM_KEY, SHM_SIZE, 0666 | IPC_CREAT); // key, size, shmflg
    printf("Shared memory key %d and id %d\n", SHM_KEY, shm_id);
    shm_ptr = shmat(shm_id, NULL, 0); // id, ptr to attach to, flags
    printf("Shared memory --> %p\n", shm_ptr);

    printf("Enter some data to write to shared memory: ");
    fgets(inp_buf, SHM_SIZE, stdin);
    
    strcpy(shm_ptr, inp_buf);
    printf("Data written into shared memory: %s", (char*) shm_ptr);
    return 0;
}
