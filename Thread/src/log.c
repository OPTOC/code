#include "log.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 日志
#include "log.h"
// 日志文件路径
static const char *system_log = "/home/hr/tmnt/log/system_log.txt";       // 系统日志
static const char *operation_log = "/home/hr/tmnt/log/operation_log.txt"; // 操作日志

int system_log_write(const char *problem)
{
    FILE *file;
    file = fopen(system_log, "a");
    if (file == NULL)
    {
        fprintf(stderr, "open file fail\n");
        return -1;
    }

    time_t now = time(NULL);
    struct tm *tm_now = localtime(&now);
    char time_str[20];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", tm_now);

    int ret = fprintf(file, "[%s] %s\n", time_str, problem);
    fclose(file);
    if (ret < 0)
    {
        fprintf(stderr, "Error writing to system log file \n");
        return 1;
    }
    return 0;
}
// 记录错误路径
int system_log_path(const char *problem, const char *path)
{
    FILE *file;
    file = fopen(system_log, "a");
    if (file == NULL)
    {
        fprintf(stderr, "open file fail\n");
        return -1;
    }

    time_t now = time(NULL);
    struct tm *tm_now = localtime(&now);
    char time_str[20];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", tm_now);

    int ret = fprintf(file, "[%s] %s %s\n", time_str, problem, path);
    fclose(file);
    if (ret < 0)
    {
        fprintf(stderr, "Error writing to system log file \n");
        return 1;
    }
    return 0;
}

int operation_revise(const char *filename, const char *modify, const char *state)
{
    // 打开文件
    FILE *file;
    file = fopen(operation_log, "a");
    if (file == NULL)
    {
        fprintf(stderr, "open file fail\n");
        return 1;
    }

    time_t now = time(NULL);
    struct tm *tm_now = localtime(&now);
    char time_str[20];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", tm_now);

    fprintf(file, "[%s] %s %s %s\n", time_str, filename, modify, state);
    fclose(file);
    return 0;
}