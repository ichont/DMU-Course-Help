#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
pthread_mutex_t mutex;
void *counta(){
  sleep(1);
  for(int i = 0;i<3;i++){
    pthread_mutex_lock(&mutex);
    printf("aa\n");
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

void *countb(){
  for(int i = 0;i<6;i++){
    pthread_mutex_lock(&mutex);
    printf("bb\n");
    pthread_mutex_unlock(&mutex);
  }
  return NULL;
}

int main(){
  pthread_t thread1,thread2;

  pthread_mutex_init(&mutex,NULL);
  
  pthread_create(&thread1,NULL,counta,NULL);
  pthread_create(&thread2,NULL,countb,NULL);

  pthread_join(thread1, NULL);
  pthread_join(thread2, NULL);
  
  
  pthread_mutex_destroy(&mutex);
  exit(0);
  return 0;
}