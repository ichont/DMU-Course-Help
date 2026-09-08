#ifndef TYPEDEFINE_H
#define TYPEDEFINE_H

#include "const.h"

typedef struct {           // 字符串类型
    char data[MAXLEN];     // 数据区
    int len;               // 长度（不包括 '\0'）
} SString;

typedef struct {
    SString* strName;      // 定义元素类型
    long lNumber;          // 号码
} Elemtype;

typedef struct node {      // 链表节点
    Elemtype data;         // 数据域
    struct node *next;     // 指向下一个节点
} SNode;

typedef struct {           // 队列的基本结构
    Elemtype q[MaxSize];   // 队列存储空间
    int front;             // 头指针
    int rear;              // 尾指针（指向下一个可用位置）
} Queue;

typedef struct {           // 栈的基本类型定义
    Elemtype data[MaxSize];
    int top;
} Stack;

typedef int BOOL;
typedef int Status;

#endif

