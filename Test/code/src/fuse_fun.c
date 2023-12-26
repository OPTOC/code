#include "fuse_fun.h"


// 初始化动态字符串数组
void initializeDynamicStringArray(DynamicStringArray *array, size_t initialCapacity) {
    array->data = (char **)malloc(initialCapacity * sizeof(char*));
    array->size = 0;
    array->capacity = initialCapacity;
}
// 添加字符串到动态字符串数组
void appendString(DynamicStringArray *array, const char *value) {
    // 如果数组满了，扩展内存
    if (array->size == array->capacity) {
        array->capacity *= 2;  // 可根据需要调整扩展策略
        array->data = (char **)realloc(array->data, array->capacity * sizeof(char*));
    }

    // 在数组末尾添加新字符串
    array->data[array->size++] = strdup(value);
}
// 释放动态字符串数组的内存
void freeDynamicStringArray(DynamicStringArray *array) {
    for (size_t i = 0; i < array->size; ++i) {
        free(array->data[i]);  // 释放每个字符串的内存
    }
    free(array->data);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
}
int append_to_file(const char *filename, const char *command,const char *path,const char *state, const char* content_conut) {
	
    FILE *file;
    file = fopen(filename, "a");
	printf("创建 %s\n", filename);//FUSE_LOG_INFO = 6
    if (file == NULL) {
        fprintf(stderr, "无法打开文件\n");
        return 1;
    }
	const char* content = (path + strlen(content_conut));
	// const char *content = strrchr(path, '/');
	if (content == NULL) {
        printf("失败\n");
        return 0;
    }
	content++;
	printf("路径 %s\n", path);
	printf("路径 %s\n", content);
    time_t now = time(NULL);
    struct tm *tm_now = localtime(&now);
    char time_str[20];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", tm_now);

    fprintf(file, "[%s] %s %s %s\n", time_str, command,content,state);
    fclose(file);
    return 0;
}

void print(void)
{
	printf("*************************我是好人**********************\n\n");
}

// int main() {
//     DynamicStringArray dynamicStringArray;
//     size_t initialCapacity = 5;  // 初始容量
//     // 初始化动态字符串数组
//     initializeDynamicStringArray(&dynamicStringArray, initialCapacity);
//     // 添加字符串到数组
//     appendString(&dynamicStringArray, "One");
//     appendString(&dynamicStringArray, "Two");
//     appendString(&dynamicStringArray, "Three");
//     // 输出数组元素
//     printf("Dynamic string array elements: ");
//     for (size_t i = 0; i < dynamicStringArray.size; ++i) {
//         printf("%s ", dynamicStringArray.data[i]);
//     }
//     printf("\n");
//     // 释放动态字符串数组的内存
//     freeDynamicStringArray(&dynamicStringArray);
//     return 0;
// }