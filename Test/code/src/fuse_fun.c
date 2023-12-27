#include "fuse_fun.h"

// 初始化动态字符串数组
void initializeDynamicStringArray(DynamicStringArray *array, size_t initialCapacity) {
    array->data = (char **)malloc(initialCapacity * sizeof(char*));
    array->data1 = (char **)malloc(initialCapacity * sizeof(char*));
    array->size = 0;
    array->capacity = initialCapacity;
}
// 添加字符串到动态字符串数组
void appendString(DynamicStringArray *array, const char *value, const char *value1) {
    int size_old = array->size++;
    // 如果数组满了，扩展内存
    if (array->size == array->capacity) {
        array->capacity *= 2;  // 可根据需要调整扩展策略
        array->data = (char **)realloc(array->data, array->capacity * sizeof(char*));
        array->data1 = (char **)realloc(array->data1, array->capacity * sizeof(char*));
    }

    // 在数组末尾添加新字符串
    array->data[size_old] = strdup(value);
    array->data1[size_old] = strdup(value1);
}
// 释放动态字符串数组的内存
void freeDynamicStringArray(DynamicStringArray *array) {
    for (size_t i = 0; i < array->size; ++i) {
        free(array->data[i]);  // 释放每个字符串的内存
        // free(array->data1[i]); 
    }
    free(array->data);
    // free(array->data1);
    array->data = NULL;
    array->data1 = NULL;
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
	const char* content = (path + strlen(content_conut));//实现获取他的名称长度
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
                            ////测试代码
// int main() {
//     string_init(String);
//     DynamicStringArray dynamicStringArray;
//     size_t initialCapacity = 5;  // 初始容量
//     // 初始化动态字符串数组
//     String.initializeDynamicStringArray(&dynamicStringArray, initialCapacity);
//     // 添加字符串到数组
//     String.appendString(&dynamicStringArray, "One", "我");
//     String.appendString(&dynamicStringArray, "Two", "是");
//     String.appendString(&dynamicStringArray, "Three", "好人");
//     // 输出数组元素
//     printf("Dynamic string array elements: ");
//     for (size_t i = 0; i < dynamicStringArray.size; ++i) {
//         printf("%s :", dynamicStringArray.data[i]);
//         printf("%s ", dynamicStringArray.data1[i]);
//     }
//     printf("\n");
//     // 释放动态字符串数组的内存
//     String.freeDynamicStringArray(&dynamicStringArray);
//     return 0;
// }