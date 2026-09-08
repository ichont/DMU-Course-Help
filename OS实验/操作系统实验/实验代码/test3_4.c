#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int globa = 4;
void main(){
pid_t pid;
int vari = 5;
printf("before fork.\n");
if((pid = fork()) < 0){
printf("fork error.\n");
exit(0);
}
else if ( pid == 0){
globa ++;
vari --;
printf("Child changed the vari and globa.\n");
}
else
printf("Parent did not chang the vari and globa.\n");

k1: printf("globa = %d, vari = %d\n",globa,vari);
k2: exit(0);
}
