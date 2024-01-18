#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define IN 0
#define OUT 1

int main() {
    char *message = "Hello from the other side";
    char recvd_msg[100];
    int bytes_read, fd[2], status;
    pid_t pid;
    
    pipe(fd);
    
    pid = fork();
    
    if (pid == -1) {
        printf("Forking failed\n");
        return 1;
    }
    
    if (pid) {
        close(fd[OUT]);
        bytes_read = read(fd[IN], recvd_msg, sizeof(recvd_msg));
        printf("Read %d bytes from child: %s\n", bytes_read, recvd_msg);
        close(fd[IN]);
    } else {
        close(fd[IN]);
        write(fd[OUT], message, strlen(message) + 1); // account for NUL
        close(fd[OUT]);
    }

    return 0;
}
