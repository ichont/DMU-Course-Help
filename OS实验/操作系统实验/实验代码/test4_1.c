 #include <stdio.h>
 #include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
void main(){
int x,fd[2];
char buf[30],s[30];
pipe(fd); //创建管道
while ((x = fork()) == -1); //创建管道失败时，一直循环
 if(x == 0){
 sprintf(buf,"This is an example \n");
 write(fd[1],buf,30); //将 buf 中字符写入管道
}
else{ //父进程返回
 wait(0);
read(fd[0],s,30); //父进程读管道中字符
printf("%s",s);
}
}

