#include <stdio.h>
#include <unistd.h>
#include <sys/msg.h>
#include <sys/ipc.h>

#define BUF_SIZE 100

struct msgbuf {
    long mtype;
    char mtext[BUF_SIZE];
};

void send(const int* msq_id) {
    struct msgbuf buf = {1, ""};
    int bytes_read;

    getchar();

    write(1, "Enter the message: ", 20);
    bytes_read = read(0, buf.mtext, BUF_SIZE - 1);

    buf.mtext[bytes_read] = '\0';

    msgsnd(*msq_id, &buf, bytes_read + 1, 0);

    printf("Message sent to the queue: %s", buf.mtext);
}

void receive(const int* msq_id) {
    struct msgbuf buf = {1, ""};

    msgrcv(*msq_id, &buf, BUF_SIZE, 0, 0);

    printf("Message received from the queue: %s", buf.mtext);
}

int main(int argc, char *argv[]) {
    key_t msq_key;
    int msq_id;
    int ch;
    
    msq_key = ftok(argv[0], 2345);
    msq_id = msgget(msq_key, 0600 | IPC_CREAT);
    
    printf("Sender (1) or receiver (2)? ");
    scanf("%d", &ch);

    switch(ch) {
        case 1:
            send(&msq_id);
            break;
        case 2:
            receive(&msq_id);
            break;
        default:
            printf("Invalid choice\n");
            return 1;
    }

    return 0;
}
