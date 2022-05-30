#include<stdio.h>
#include<unistd.h>
int rm(char argv[]){
	if(unlink(argv)==-1){
		printf("The File has't Exists");
	}
	return 0;
}
