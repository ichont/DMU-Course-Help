#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

void* thread1_func(void* arg) {
    sleep(1);
    for (int i = 0; i < 3; i++) {
        printf("aa\n");
        fflush(stdout);
    }
    return NULL;
}

void* thread2_func(void* arg) {
    for (int i = 0; i < 6; i++) {
        printf("bb\n");
        fflush(stdout);
    }
    return NULL;
}

int main() {
    pthread_t thread1, thread2;

    if (pthread_create(&thread1, NULL, thread1_func, NULL) != 0) {
        perror("pthread_create for thread1 failed");
        return 1;
    }

    if (pthread_create(&thread2, NULL, thread2_func, NULL) != 0) {
        perror("pthread_create for thread2 failed");
        return 1;
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}

