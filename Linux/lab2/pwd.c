#include<stdio.h>
#include<unistd.h>
#define MAXPATH 50
int pwd(char * path){
	puts(getcwd(path,MAXPATH));
	return 0;
}
