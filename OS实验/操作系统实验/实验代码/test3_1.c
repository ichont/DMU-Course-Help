#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
void main(){
	int i = 1;
	if(fork() == 0){
		printf("child process:i=%d\n",i);
		i = 2;
		printf("child process:i=%d\n",i);
		exit(0);
	}
	printf("parent process:i=%d\n",i);
}

