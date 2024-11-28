#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t printMutex;
void* func1(void* arg){
	for(int i=0;i<3;i++){
		pthread_mutex_lock(&printMutex);
		printf("aa\n");
		pthread_mutex_unlock(&printMutex);
	}
}

void* func2(void* arg){
	for(int i=0;i<6;i++){
		pthread_mutex_lock(&printMutex);
		printf("bb\n");
		pthread_mutex_unlock(&printMutex);
	}
}


int main()
{
	pthread_t t1,t2;
	pthread_mutex_init(&printMutex,NULL);
	pthread_create(&t1,NULL,func1,NULL);
	pthread_create(&t2,NULL,func2,NULL);
	
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	pthread_mutex_destroy(&printMutex);

	return 0;
}
