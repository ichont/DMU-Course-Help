#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define MACLINE 1024
#define READ 0
#define WRITE 1

int main() {
    int x = 1; 
    pid_t pid;
    int pipe1[2], pipe2[2];
    
    pipe(pipe1);
    pipe(pipe2);
    pid = fork();
    
    if (pid < 0) {
        printf("create process error!\n");
        exit(1);
    }
    
    if (pid == 0) {
        close(pipe1[WRITE]);
        close(pipe2[READ]);
        
        while (x < 10) {
            read(pipe1[READ], &x, sizeof(x));
            printf("Child Process (PID: %d) read x = %d\n", getpid(), x);
            
            x++;
            
            write(pipe2[WRITE], &x, sizeof(x));
        }
        
        close(pipe1[READ]);
        close(pipe2[WRITE]);
        exit(0);
    }
    else {
        close(pipe1[READ]);
        close(pipe2[WRITE]);
        
        while (x <= 10) {
            write(pipe1[WRITE], &x, sizeof(x));
            // printf("Parent Process (PID: %d) wrote x = %d\n", getpid(), x);
            
            read(pipe2[READ], &x, sizeof(x));
            printf("Parent Process (PID: %d) read x = %d\n", getpid(), x);
            
            x++;
        }
        
        close(pipe1[WRITE]);
        close(pipe2[READ]);
        
        wait(NULL);
    }

    return 0;
}

