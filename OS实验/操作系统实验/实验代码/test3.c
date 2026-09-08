#include <stdio.h>
#include <unistd.h>
void main(){
int pid1,pid2,i;
while((pid1 = fork()) == -1);
if (pid1 == 0){
for (i = 0; i < 10; i++)
printf("child%d\n",i);
}
else{
while((pid2 = fork()) == -1);
if(pid2 == 0){
for(i = 0; i < 10; i++)
printf("son%d\n",i);

}
else{
for(i = 0; i < 10; i++)
printf("daughter%d\n",i);
}
}
}
