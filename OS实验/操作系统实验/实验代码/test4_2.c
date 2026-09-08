#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void main(){
    int i,r,p1,p2,fd[2];
    char buf[50],s[50];

    pipe(fd); //父进程建立管道
    while((p1 = fork()) == -1);

    if(p1 == 0){
        // 子进程 p1
        lockf(fd[1],1,0); //锁定写入端
        sprintf(buf,"messeages from child process p1!\n");
        printf("child process p1!\n");
        write(fd[1],buf,50); //将 buf 中的 50 个字符写入管道
        sleep(5); //睡眠 5 秒，等待父进程读管道
        lockf(fd[1],0,0); //释放管道写入端
        exit(0);
    } else {
        // 父进程
        while((p2 = fork()) == -1);

        if(p2 == 0){
            // 子进程 p2
            lockf(fd[1],1,0);
            sprintf(buf,"messeages from child process p2!\n");
            printf("child process p2!\n");
            write(fd[1],buf,50); //将 buf 中的 50 个字符写入管道
            sleep(5); //睡眠 5 秒，等待父进程读管道
            lockf(fd[1],0,0); //释放管道写入端
            exit(0);
        }
		
            // 父进程
            wait(0);
            if((r = read(fd[0],s,50)) == -1)
                printf("can't read pipe\n");
            else
                printf("%s",s);
            wait(0);
            if((r = read(fd[0],s,50)) == -1)
                printf("can't read pipe\n");
            else
                printf("%s",s);
            exit(0);
        
    }
}
