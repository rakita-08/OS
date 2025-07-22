#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include<sys/wait.h>

#define TOTAL_ITEMS 10
#define MSG_TYPE 1

struct msgbuf {
    long mtype;
    int data;
};

void producer(int msqid) {
    struct msgbuf msg;
    msg.mtype = MSG_TYPE;

    for (int i = 1; i <= TOTAL_ITEMS; i++) {
        msg.data = i;
        if (msgsnd(msqid, &msg, sizeof(int), 0) == -1) {
            perror("msgsnd failed");
            exit(1);
        }
        printf("Produced: %d\n", i);
        sleep(1);
    }
}

void consumer(int msqid) {
    struct msgbuf msg;

    for (int i = 1; i <= TOTAL_ITEMS; i++) {
        if (msgrcv(msqid, &msg, sizeof(int), MSG_TYPE, 0) == -1) {
            perror("msgrcv failed");
            exit(1);
        }
        printf("Consumed: %d\n", msg.data);
        sleep(2);
    }
}

int main() {
    key_t key = ftok("progfile", 65);  // Generate unique key
    int msqid = msgget(key, 0666 | IPC_CREAT);

    if (msqid == -1) {
        perror("msgget failed");
        exit(1);
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } else if (pid == 0) {
        // Child process: consumer
        consumer(msqid);
        exit(0);
    } else {
        // Parent process: producer
        producer(msqid);

        // Wait for child
        wait(NULL);

        // Cleanup message queue
        if (msgctl(msqid, IPC_RMID, NULL) == -1) {
            perror("msgctl cleanup failed");
            exit(1);
        }
        printf("All items produced and consumed. Exiting.\n");
    }
    printf("Name:Rakita Rimal, Roll No:27, Lab No:2.4c\n");

    return 0;
}
