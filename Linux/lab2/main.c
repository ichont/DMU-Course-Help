#include"main.h"
#include"stdio.h"
#include"string.h"
#include"iostream"
#define MAX 128
int main(){
	printf("Welcome to Mybash.\n");
	printf("Now you can use some basic command like 'ls'.\n");
	printf("put 'help' to get more command\n");
while(1){
	printf(">>>");
	char buff[128]={0};
	fgets(buff,128,stdin);
	buff[strlen(buff)-1]=0;
	char *s=strtok(buff," ");
	if(s==NULL)
	{
		continue;
	}
	char* myargv[MAX] ={0};
	myargv[0]=s;
	int i = 1;
	while((s=strtok(NULL,""))!=NULL)
		{
			myargv[i++]=s;
		}
	if(strcmp(myargv[0],"help") == 0){
		help();
	}else if(strcmp(myargv[0],"ls") == 0){
		ls();
	}else if(strcmp(myargv[0],"pwd") == 0){
		pwd(myargv[0]);
	}else if(strcmp(myargv[0],"exit") == 0){
		exit(-1);
	}else if(strcmp(myargv[0],"cat") == 0){
		cat(myargv[1]);
	}else if(strcmp(myargv[0],"cd") == 0){
		cd(myargv[1]);
	}else if(strcmp(myargv[0],"echo") == 0){
		echo(i,myargv);
	}else if(strcmp(myargv[0],"wc") == 0){
		wc(myargv[1]);
	}else if(strcmp(myargv[0],"rm") == 0){
		rm(myargv[1]);
	}else if(strcmp(myargv[0],"mkdir") == 0){
		mymkdir(myargv[1]);
	}else if(strcmp(myargv[0],"clear") == 0){
		clear();
	}else{
	printf("Wrong Command\n");
	}
}
return 0;
}
