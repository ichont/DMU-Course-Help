#include <stdio.h>
#include <pthread.h>

// 全局变量
int global_variable = 0;

// 锁对象，用于线程同步
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

// 函数用于增加全局变量的值
void* increment_global_variable(void* thread_number) {
    int thread_num = *(int*)thread_number;
    while (global_variable < 20) {
        // 获取锁
        pthread_mutex_lock(&lock);

        if (global_variable < 20) {
            global_variable++;
            printf("线程 %d: 当前值为 %d\n", thread_num, global_variable);
        }

        // 释放锁
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main() {
    // 创建两个线程
    pthread_t thread1, thread2;
    int thread_num1 = 1;
    int thread_num2 = 2;

    pthread_create(&thread2, NULL, increment_global_variable, &thread_num2);
    pthread_create(&thread1, NULL, increment_global_variable, &thread_num1);

    // 等待两个线程完成
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    printf("操作结束\n");

    // 销毁锁
    pthread_mutex_destroy(&lock);

    return 0;
}

