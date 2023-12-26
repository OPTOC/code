#ifndef __FUSE_FUN_H
#define __FUSE_FUN_H
// #include <fuse.h>

#ifdef HAVE_LIBULOCKMGR
#include <ulockmgr.h>
#endif
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>
#include <time.h>
#include "demo_02.h"
#include <sys/file.h> /* flock(2) */
//定义一个结构体表示动态字符串数组
typedef struct {
    char **data;     // 指向字符串数组的指针
    size_t size;      // 数组当前的元素个数
    size_t capacity;  // 数组当前分配的内存空间大小
} DynamicStringArray;

struct string_fun { /********************这种是在定义接口********************/
	void (*appendString)(DynamicStringArray *array, const char *value);
	void (*freeDynamicStringArray)(DynamicStringArray *array);
    void (*initializeDynamicStringArray)(DynamicStringArray *array, size_t initialCapacity);
    void (*print)(void);
}; 

void initializeDynamicStringArray(DynamicStringArray *array, size_t initialCapacity);
void appendString(DynamicStringArray *array, const char *value);
void freeDynamicStringArray(DynamicStringArray *array);
int append_to_file(const char *filename, const char *command,const char *path,const char *state, const char* content_conut);
void print(void);

static const struct string_fun String = {
  .appendString = appendString,
  .freeDynamicStringArray = freeDynamicStringArray,
  .initializeDynamicStringArray = initializeDynamicStringArray, 
  .print = print, 
};

#endif