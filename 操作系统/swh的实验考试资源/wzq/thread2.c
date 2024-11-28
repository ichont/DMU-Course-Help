#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#define MACLINE 1024
#define READ 0
#define WRITE 1
int main(){
  int x = 0; 
  pid_t pid;
  int pipe1[2],pipe2[2];
  pipe(pipe1);
  pipe(pipe2);
  pid = fork();
  if(pid < 0)
  {
    printf("creat process error!\n");
    exit(1);
  }
  if(pid == 0)
  {
    sleep(1);
    while(x<10){
      read(pipe1[READ],&x,sizeof(int));
      if(x==10){
        printf("kid = %d,X=%d\n",getpid(),x);
        exit(0);
      }
      else{
        printf("kid = %d,X=%d\n",getpid(),x);
        x++;
        write(pipe2[WRITE],&x,sizeof(int));
      } 
    }
   
   
  }
  else if(pid > 0)
  {
     x++;
     write(pipe1[WRITE],&x,sizeof(int));
     while(x<10){
      read(pipe2[READ],&x,sizeof(int));
      if(x==10){
        printf("parent = %d,X=%d\n",getpid(),x);
        exit(0);
      }
      else{
        printf("parent = %d,X=%d\n",getpid(),x);
        x++;
        write(pipe1[WRITE],&x,sizeof(int));
      } 
    }
   
  } 
}