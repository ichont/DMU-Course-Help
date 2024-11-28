#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
int global_var = 0;
pthread_mutex_t mutex;
void* increment(void *arg) {
	for(int i = 0;i < 200 ; i++){
     pthread_mutex_lock(&mutex);
     global_var++;
     pthread_mutex_unlock(&mutex);
  }
	return NULL;
}

void* decrement(void *arg) {
	for(int i = 0;i < 100 ; i++){
     pthread_mutex_lock(&mutex);
     global_var--;
     pthread_mutex_unlock(&mutex);
  }
	return NULL;
}


int main() {
	pthread_t in_thread,de_thread;
	
  pthread_mutex_init(&mutex,NULL);
  
	pthread_create(&in_thread, NULL, increment, NULL);
  pthread_create(&de_thread, NULL, decrement, NULL);
  
  
  
	pthread_join(in_thread, NULL);
  pthread_join(de_thread, NULL);
  
  pthread_mutex_destroy(&mutex);
  printf("number:%d\n",global_var);
	return 0;
}