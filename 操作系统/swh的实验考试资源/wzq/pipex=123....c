#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#define MACLINE 1024
#define READ 0
#define WRITE 1


int main()
{
	int x=0;
	pid_t pid;
	int fd1[2],fd2[2];
	pipe(fd1);
	pipe(fd2);
	pid = fork();
	if(pid==0){
		//子进程
		close(fd2[READ]);
		close(fd1[WRITE]);
		//等待父进程写
		sleep(3);
		while(x<10){
			read(fd1[READ],&x,sizeof(int));
			if(x == 10){
				printf("子进程接收%d 子进程结束\n",x);
				exit(0);
			}
			else{
				printf("子进程%d 读取x=%d\n",getpid(),x);
				x++;
				write(fd2[WRITE],&x,sizeof(int));
			}
		}
	}
	else{
		//父进程
		close(fd1[READ]);
		close(fd2[WRITE]);
		x++;
		printf("父进程发送 %d\n",x);
		write(fd1[WRITE],&x,sizeof(int));
		while(x<10){
			read(fd2[READ],&x,sizeof(int));
			if(x == 10){
				printf("父进程接收%d  父进程结束\n",x);
				write(fd1[WRITE],&x,sizeof(int));
				int statu =0 ;
				wait(&statu);
			}
			else{
				printf("父进程%d 读取x=%d\n",getpid(),x);
				x++;
				write(fd1[WRITE],&x,sizeof(int));
			}
		}
		
	}
	return 0;
}
