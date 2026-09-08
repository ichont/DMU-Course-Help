#include<stdio.h>
#include<unistd.h>
int cd(char argv[]){
        if(chdir(argv) == -1){
        printf("Direction Not Found\n");
        return -1;
        }
return 0;
}
