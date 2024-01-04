#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#define MAX_PATH_LEN 256

// 定义栈节点
struct StackNode {
    char path[MAX_PATH_LEN];
    struct StackNode* next;
};

// 定义栈
struct Stack {
    struct StackNode* top;
};

// 初始化栈
void initStack(struct Stack* stack) {
    stack->top = NULL;
}

// 入栈
void push(struct Stack* stack, const char* path) {
    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    strncpy(newNode->path, path, MAX_PATH_LEN);
    newNode->next = stack->top;
    stack->top = newNode;
}

// 出栈
void pop(struct Stack* stack, char* path) {
    if (stack->top == NULL) {
        return;
    }

    struct StackNode* temp = stack->top;
    stack->top = temp->next;
    strncpy(path, temp->path, MAX_PATH_LEN);
    free(temp);
}

// 判断栈是否为空
int isEmpty(struct Stack* stack) {
    return stack->top == NULL;
}

// 栈遍历目录
void stackGetDir(const char* path) {
    struct Stack stack;
    initStack(&stack);
    push(&stack, path);

    while (!isEmpty(&stack)) {
        char currentPath[MAX_PATH_LEN];
        pop(&stack, currentPath);
        printf("当前路径：%s\n", currentPath);

        DIR* dir = opendir(currentPath);
        if (dir != NULL) {
            struct dirent* entry;
            while ((entry = readdir(dir)) != NULL) {
                if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
                    unsigned short size_old = strlen(currentPath) + strlen(entry->d_name) + 1 + 1;
                    char childPath[size_old];
                    snprintf(childPath, sizeof(childPath), "%s/%s", currentPath, entry->d_name);
                    if (entry->d_type == DT_DIR) {
                        printf("目录：%s\n", entry->d_name);
                        push(&stack, childPath);
                    } else {
                        printf("文件：%s\n", entry->d_name);
                    }
                }
            }
            closedir(dir);
        }
    }
}

int main() {
    const char* rootPath = "/home";
    stackGetDir(rootPath);

    return 0;
}
