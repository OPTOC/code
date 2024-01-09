#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include "demo_03.h"

struct Queue Queuene;
struct Queue Queuene2;
unsigned short conut = 0;
unsigned short verbose = 0;
unsigned short Printf_count = 0;

// 初始化队列
void initQueue(struct Queue* q) {
    q->front = NULL;
    q->rear = NULL;
    q->count = 0;
}

// 入队
void enqueue(struct Queue* q, const char* path) {
    //定义一个结构体指针 也就是先定义一个变量
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    newNode->path = strdup(path);
    //先将链表尾部清除
    newNode->next = NULL;
    if (q->rear == NULL) {//判断尾部是否为空  ,也就是判断有没有数据过
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;//开始拼接尾部，和链表很像
        q->rear = newNode;
    }
    q -> count++;
}

// 出队
void dequeue(struct Queue* q, char** path) {
    if (q->front == NULL) {
        printf("出问题了出队");
        return;
    }
    struct QueueNode* temp = q->front;
    *path = strdup(temp->path);
    if (q->front == q->rear) {
        q->front = NULL;
        q->rear = NULL;
    } else {
        q->front = q->front->next;
    }
    free(temp->path);
    free(temp);  
    q -> count--;
}
// 出队
void dequeue2(struct Queue* q, char* path) {
    if (q->front == NULL) {
        printf("出问题了出队");
        return;
    }
    struct QueueNode* temp = q->front;
    memcpy(path, temp->path, strlen(temp->path) + 1);
    if (q->front == q->rear) {
        q->front = NULL;
        q->rear = NULL;
    } else {
        q->front = q->front->next;
    }
    free(temp->path);
    free(temp);  
    q -> count--;
}
void listDirectories(const char* path) {
    conut++;
    DIR* dir = opendir(path);
    if (dir == NULL) {
        perror("Error opening directory");
        return;
    }
    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0 && (entry->d_type == DT_DIR || 1)) {
            const unsigned int size_old = (strlen(path) + strlen(entry->d_name) + 1) * sizeof(char);
            char childPath[size_old];
            snprintf(childPath, sizeof(childPath) + 1, "%s/%s", path, entry->d_name);
            {
                Lock(&Queuene, childPath);
            }
            if(entry->d_type == DT_DIR){
                Lock2(&Queuene2, childPath);
                // printf("路径:%s    层数%d  计数%d\n", childPath, conut,Queuene.count);
                listDirectories(childPath);
                conut--;}
        }
    }
    closedir(dir);
}
void erg_thread()
{
    const char* rootPath = "/home/zjh";
    listDirectories(rootPath);
    verbose = 1;
    while(verbose < 3){}
}
int main() {
    
    initQueue(&Queuene);
    initQueue(&Queuene2);
    thread_demo();
    return 0;
}
