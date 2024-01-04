#ifndef _ERGODIC_H
#define _ERGODIC_H
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

// 定义节点
struct QueueNode {
    char* path;
    struct QueueNode* next;
};

// 定义队列
struct Queue {
    struct QueueNode* front;
    struct QueueNode* rear;
    unsigned int count; 
};

void initQueue(struct Queue* q);
void enqueue(struct Queue* q, const char* path);
void dequeue(struct Queue* q, char** path);
void levelOrderTraversal(const char* rootPath);


#endif 