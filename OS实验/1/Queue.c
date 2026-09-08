#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"

Queue* InitQueue() {
    Queue* Q = (Queue*)malloc(sizeof(Queue));
    Q->front = Q->rear = 0;  // 初始化头尾指针
    return Q;
}

int EnQueue(Queue *Q, Elemtype x) {
    if ((Q->rear + 1) % MaxSize == Q->front) { // 判断队列是否已满
        return FALSE;
    } else {
        Q->q[Q->rear] = x;
        Q->rear = (Q->rear + 1) % MaxSize;
        return TRUE;
    }
}

int DeQueue(Queue *Q, Elemtype *x) {
    if (Q->rear == Q->front) { // 判断队列是否为空
        return FALSE;
    } else {
        *x = Q->q[Q->front];
        Q->front = (Q->front + 1) % MaxSize;
        return TRUE;
    }
}

int QueueEmpty(Queue Q) {
    return Q.rear == Q.front ? TRUE : FALSE;
}

boolean QueueFull(Queue Q) {
    return ((Q.rear + 1) % MaxSize == Q.front) ? TRUE : FALSE;
}

