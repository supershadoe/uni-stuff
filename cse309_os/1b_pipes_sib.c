#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define IN 0
#define OUT 1

int main() {
    char *message = "Hello from the other side\n";
    char recvd_msg[100];
    int bytes_read, fd[2];
    pid_t c1, c2;
    
    pipe(fd);
    
    c1 = fork();
    
    if (c1 == -1) {
        printf("Forking failed\n");
        return 1;
    }
    
    if (c1) {
        c2 = fork();
        
        if (c2 == -1) {
            printf("Forking failed\n");
            return 1;
        }
        
        if (c2) {
            close(fd[IN]);
            close(fd[OUT]);
            while(wait(NULL) > 0);
        } else {
            close(fd[OUT]);
            bytes_read = read(fd[IN], recvd_msg, sizeof(recvd_msg));
            write(OUT, recvd_msg, bytes_read);
            close(fd[IN]);
        }
    } else {
        close(fd[IN]);
        write(fd[OUT], message, strlen(message) + 1); // account for NUL
        close(fd[OUT]);
    }

    return 0;
}
