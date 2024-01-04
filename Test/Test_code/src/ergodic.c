#include "ergodic.h"
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
    //将数据传入队列
    // snprintf(newNode->path, sizeof(path)+1, "%s", path);
    //先将链表尾部清除
    newNode->next = NULL;
    if (q->rear == NULL) {//判断尾部是否为空  ,也就是判断有没有数据过
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;//开始拼接尾部，和链表很像
        q->rear = newNode;
    }
    q->count++;
}

// 出队
void dequeue(struct Queue* q, char** path) {
    if (q->front == NULL) {
        return;
    }
    struct QueueNode* temp = q->front;
    // snprintf(path, 256, "%s", temp->path);
    // snprintf(path, strlen(temp->path)+1, "%s", temp->path);
    *path = strdup(temp->path);
    if (q->front == q->rear) {
        q->front = NULL;
        q->rear = NULL;
    } else {
        q->front = q->front->next;
    }
    free(temp);
}

// 层序遍历文件夹
void levelOrderTraversal(const char* rootPath) {
    struct Queue queue;
    initQueue(&queue);

    enqueue(&queue, rootPath);

    while (queue.front != NULL) {
        char* path_new = NULL;
        dequeue(&queue, &path_new);
        printf("%d\n", queue.count);
        DIR* dir = opendir(path_new);
        if (dir != NULL) {           
            struct dirent* entry;
            while ((entry = readdir(dir)) != NULL) {
                if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {// 判断是否是文件夹
                    // unsigned int size_old = (strlen(path_new)+strlen(entry->d_name)+1) * sizeof(char);
                    // char* childPath = (char*)malloc(size_old);
                    unsigned int size_old = (strlen(path_new)+strlen(entry->d_name)+1) * sizeof(char);
                    char childPath[size_old];
                    // snprintf(childPath, size_old+1, "%s/%s", path_new, entry->d_name);
                    snprintf(childPath, sizeof(childPath)+1, "%s/%s", path_new, entry->d_name);
                    enqueue(&queue, childPath);
                    // free(childPath);
                }
            }
            free(path_new);
            closedir(dir);
        }  
    }
}

int main() {
    const char* rootPath = "/home/zjh";
    levelOrderTraversal(rootPath);

    return 0;
}
