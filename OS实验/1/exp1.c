#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include "Queue.h"

#define N 5  // 缓冲区大小

time_t end_time;         // 运行结束时间
sem_t mutex, full, empty; // 信号量
Queue* qt;               // 缓冲区队列
Elemtype p;              // 数据元素

// 函数声明
void productor(void* arg);
void consumer(void* arg);

int main() {
    pthread_t prod1, prod2, prod3, cons1, cons2;
    int ret;

    end_time = time(NULL) + 30; // 设置程序运行时间
    qt = InitQueue();
    p.lNumber = 1000;

    // 初始化信号量
    sem_init(&mutex, 0, 1);  // 互斥信号量
    sem_init(&empty, 0, N);  // 空闲空间信号量
    sem_init(&full, 0, 0);   // 数据信号量

    // 创建线程
    pthread_create(&prod1, NULL, (void*)productor, NULL);
    pthread_create(&prod2, NULL, (void*)productor, NULL);
    pthread_create(&prod3, NULL, (void*)productor, NULL);
    pthread_create(&cons1, NULL, (void*)consumer, NULL);
    pthread_create(&cons2, NULL, (void*)consumer, NULL);

    // 等待线程结束
    pthread_join(prod1, NULL);
    pthread_join(prod2, NULL);
    pthread_join(prod3, NULL);
    pthread_join(cons1, NULL);
    pthread_join(cons2, NULL);

    // 销毁信号量
    sem_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}

void productor(void* arg) {
    while (time(NULL) < end_time) {
        sem_wait(&empty);  // P(empty)
        sem_wait(&mutex);  // P(mutex)

        if (QueueFull(*qt)) {
            printf("Producer: buffer is full, please try later.\n");
        } else {
            EnQueue(qt, p);
            printf("Producer: write [%ld] to buffer\n", p.lNumber);
            p.lNumber++;
        }

        sem_post(&full);   // V(full)
        sem_post(&mutex);  // V(mutex)
        sleep(1);
    }
}

void consumer(void* arg) {
    Elemtype p2;
    while (time(NULL) < end_time || !QueueEmpty(*qt)) {
        sem_wait(&full);   // P(full)
        sem_wait(&mutex);  // P(mutex)

        if (QueueEmpty(*qt)) {
            printf("Consumer: buffer is empty, please try later.\n");
        } else {
            DeQueue(qt, &p2);
            printf("Consumer: read [%ld] from buffer\n", p2.lNumber);
        }

        sem_post(&empty);  // V(empty)
        sem_post(&mutex);  // V(mutex)
        sleep(2);
    }
}

