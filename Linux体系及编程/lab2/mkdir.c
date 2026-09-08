#include<sys/stat.h>
#include<sys/types.h>
#include<stdio.h>
int mymkdir(char argv[]){
int i;
	if(mkdir(argv,0775)){
		printf("error! This File Has Exists! Or Wrong Path\n");
	}
}
