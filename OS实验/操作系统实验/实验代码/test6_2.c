#include <stdio.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

#define MSGKEY 75

struct msgform {
    long mtype;
    char msgtext[1030];
} msg;

int msgqid, pid, pid1;

void SERVER() {
    do {
        msgrcv(msgqid, &msg, 1030, 0, 0);
        printf("(server) received message %d\n", msg.mtype);
    } while (msg.mtype != 1);
    msgctl(msgqid, IPC_RMID, 0);
    exit(0);
}

void CLIENT() {
    int i;
    msgqid = msgget(MSGKEY, 0777);
    for (i = 10; i >= 1; i--) {
        msg.mtype = i;
        printf("(client) sent\n");
        msgsnd(msgqid, &msg, 1030, 0);
    }
    exit(0);
}

int main() {
    msgqid = msgget(MSGKEY, 0777 | IPC_CREAT);
    while ((pid = fork()) == -1);
    if (pid == 0)
        SERVER();
    while ((pid1 = fork()) == -1);
    if (pid1 == 0)
        CLIENT();
    wait(0);
    wait(0);
    return 0;
}

