#include <stdio.h>
#include <sys/shm.h>

#define SHM_KEY 1003
#define SHM_SIZE 1024 // bytes

int main() {
    char out_buf[1024];
    int shm_id;
    void* shm_ptr;

    shm_id = shmget(SHM_KEY, 1024, 0666);
    shm_ptr = shmat(shm_id, NULL, 0);
    
    printf("Data read from the shared memory: %s", (char*) shm_ptr);
    return 0;
}
