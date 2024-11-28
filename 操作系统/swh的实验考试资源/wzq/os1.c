#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void* threadFuction(void *arg) {
	printf("hello world!\n");
	return NULL;
}
int main() {
	pthread_t thread;
	int result;

	result = pthread_create(&thread, NULL, threadFuction, NULL);


	result = pthread_join(thread, NULL);
	return 0;
}