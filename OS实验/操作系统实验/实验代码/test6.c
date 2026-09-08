#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>
#define MSGKEY 75
// 定义消息结构体
struct msgform {
    long mtype;          // 消息类型
    char mtext[1030];    // 消息文本
} msg;
int msgqid;             // 消息队列标识
int client_done = 0;    // 客户端是否完成的标志
// 处理信号的函数
void handle_signal(int signal) {
    if (signal == SIGUSR1) {
        exit(0);
	    //client_done = 1;
    }
}
int main() {
    // 创建或获取消息队列
    msgqid = msgget(MSGKEY, 0777 | IPC_CREAT);
    // 注册信号处理函数
    signal(SIGUSR1, handle_signal);
    // 创建子进程
    pid_t pid = fork();
    //int i = 0;
    if (pid == 0) {
        // 子进程（服务器）
        while (!client_done) {
            // 等待接收消息
            msgrcv(msgqid, &msg, 1030, 0, 0);
            printf("(server) 接收到消息 %ld: %s", msg.mtype, msg.mtext);
	    //printf("%d",i++);
	}
        // 删除消息队列并退出
        msgctl(msgqid, IPC_RMID, 0);
        exit(0);
    } else {
        // 父进程（客户端）
        for (int i = 1; i <= 10; i++) {
            msg.mtype = i;
            sprintf(msg.mtext, "来自客户端的消息 %d\n", i);
            // 发送消息到消息队列
            msgsnd(msgqid, &msg, strlen(msg.mtext) + 1, 0);
            printf("(client)发送了一条消息\n");
	    sleep(1);  // 暂停1秒
        }
	// 通知服务器端客户端已经完成
	kill(pid, SIGUSR1);

        // 等待服务器进程结束
        wait(NULL);
        printf("客户端进程完成。\n");
    }
    return 0;
}

