#include <stdio.h>
#include <unistd.h>
int i=0;
void main()
{
while(i<3){
        i++;
int pid,pid1;
while((pid = fork( )) == -1);
if(pid != 0) {
while((pid1 = fork( )) == -1);
if(pid1 != 0)
printf("c/n");
else
printf("b/n");
}
else{
printf("a/n");
}
}
}

