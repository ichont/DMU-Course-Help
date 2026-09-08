#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
void main(){
int i = 1;
if(fork() == 0){
printf("child process pid is: %d\n",getpid());
printf("child process:i = %d\n",i);
i = 2;
printf("child process:i = %d\n",i);
}
else
printf("parent process pid is %d: i = %d\n",getpid(),i);
}
