#include <stdio.h>
#include <sys/shm.h>

#define SHM_KEY 1002
#define SHM_SIZE 4 * 10 // bytes

void sort_num(int* a, int n) {
    int i, j, key;
    for (i = 1; i < n; i++) {
        j = i - 1;
        key = a[i];

        while (j >= 0 && a[j] > key) {
            a[j+1] = a[j];
            j--;
        }

        a[j+1] = key;
    }
}

int add_num(int* a, int n) {
    int i, sum = 0;

    for (i = 0; i < n; i++)
        sum += a[i];

    return sum;
}

int main() {
    int shm_id;
    int* shm_ptr;
    const int n = SHM_SIZE/sizeof(int);
    int sorted[SHM_SIZE/sizeof(int)];

    shm_id = shmget(SHM_KEY, 1024, 0666);
    shm_ptr = shmat(shm_id, NULL, 0);
    
    printf("Numbers stored in shared memory are: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", shm_ptr[i]);
        sorted[i] = shm_ptr[i];
    }
    printf("\n");

    sort_num(sorted, n);
    
    printf("The numbers after sorting are: ");
    for (int i = 0; i < n; i++)
        printf("%d ", sorted[i]);
    printf("\n");
    
    printf("Sum of the above numbers: %d\n", add_num(shm_ptr, n));
    return 0;
}
