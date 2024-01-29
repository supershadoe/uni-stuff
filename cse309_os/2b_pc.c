#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/ipc.h>

#define BUF_SIZE 100

struct msgbuf {
    long mtype;
    char mtext[BUF_SIZE];
};

void send(const int* msq_id, const int* msg_typ) {
    struct msgbuf buf = {*msg_typ, ""};
    int bytes_read;

    getchar();

    printf("Producer process.\n\n");
    while (1) {
        write(1, "Enter the message: ", 20);
        bytes_read = read(0, buf.mtext, BUF_SIZE - 1);

        buf.mtext[bytes_read] = '\0';

        if (! strcmp(buf.mtext, "exit\n")) {
            msgctl(*msq_id, IPC_RMID, NULL);
            break;
        }

        msgsnd(*msq_id, &buf, strlen(buf.mtext) + 1, 0);
    }
}

void receive(const int* msq_id, const int* msg_typ) {
    struct msgbuf buf = {*msg_typ, ""};
    int bytes_read;

    printf("Consumer process.\n\n");
    while (1) {
        bytes_read = msgrcv(*msq_id, &buf, BUF_SIZE, *msg_typ, 0);

        if (bytes_read == -1) break;

        write(1, buf.mtext, bytes_read);
    }
}

int main(int argc, char *argv[]) {
    key_t msq_key;
    int msq_id;
    int ch;
    
    msq_key = ftok(argv[0], 2345);
    msq_id = msgget(msq_key, 0600 | IPC_CREAT);
    
    printf("Producer (1) or consumer (2)? ");
    scanf("%d", &ch);

    switch(ch) {
        case 1:
            printf("Enter the producer ID: ");
            scanf("%d", &ch);
            send(&msq_id, &ch);
            break;
        case 2:
            printf("Enter the producer ID to listen to: ");
            scanf("%d", &ch);
            receive(&msq_id, &ch);
            break;
        default:
            printf("Invalid choice\n");
            return 1;
    }

    printf("\nMessage queue destroyed.\n");
    return 0;
}
