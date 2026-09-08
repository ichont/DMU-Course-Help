#ifndef QUEUE_H
#define QUEUE_H

#include "Typedefine.h"

// 队列的基本操作函数声明
Queue* InitQueue();                      // 初始化队列
int EnQueue(Queue *Q, Elemtype x);       // 入队操作
int DeQueue(Queue *Q, Elemtype *x);      // 出队操作
int QueueEmpty(Queue Q);                 // 判断队列是否为空
boolean QueueFull(Queue Q);              // 判断队列是否已满
int QueueCount(Queue *Q);                // 统计队列中的元素个数

#endif

