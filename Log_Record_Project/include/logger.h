// logger.h
#ifndef LOGGER_H
#define LOGGER_H

#include <time.h>

typedef enum {
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_ERROR
} LogLevel;

// 初始化日志系统
void log_init();

// 记录一条日志（正常打印）
void log_record(LogLevel level, const char* format, ...);

// 过滤打印接口（根据规则决定是否打印）
int log_filter_print(const char* message);

#endif // LOGGER_H