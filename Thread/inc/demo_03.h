#ifndef _ROCK_03_H_
#define _ROCK_03_H_

#ifdef __cplusplus
#include <iostream>
#include <cassert>
#include <thread>
#include <mutex>
#include <chrono>
#include "rocksdb/db.h"
extern "C" {
#endif
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
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
void dequeue2(struct Queue* q, char* path);
// int rocksdb1_Fun();
// void Printf();
void thread_demo();
void Lock(struct Queue* q, const char* path);
void Lock2(struct Queue* q, const char* path);
void erg_thread();
extern struct Queue Queuene2;
extern struct Queue Queuene; 
#ifdef __cplusplus
}
#endif
#endif
