// logger.c
#include "logger.h"
#include <stdio.h>
#include <stdarg.h>
#include <time.h>

static FILE* log_file = NULL;

// 写日志到文件
static void write_log_to_file(const char* message) {
    if (!log_file) {
        log_file = fopen("app.log", "a");
    }
    if (log_file) {
        fprintf(log_file, "%s\n", message);
        fflush(log_file); // 确保实时写入
    }
}

// 初始化日志系统
void log_init() {
    // 可以在这里做其他初始化工作
}

// 格式化输出日志并写入文件
void log_record(LogLevel level, const char* format, ...) {
    char buffer[512];
    va_list args;
    va_start(args, format);
    vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);

    // 添加时间戳
    time_t now = time(NULL);
    char timestamp[64];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localtime(&now));

    // 打印等级前缀
    const char* level_str;
    switch (level) {
        case LOG_LEVEL_INFO: level_str = "INFO"; break;
        case LOG_LEVEL_WARNING: level_str = "WARNING"; break;
        case LOG_LEVEL_ERROR: level_str = "ERROR"; break;
    }

    char final_message[600];
    snprintf(final_message, sizeof(final_message), "[%s] [%s] %s", timestamp, level_str, buffer);

    // 输出到控制台（可选）
    printf("%s\n", final_message);

    // 写入日志文件
    write_log_to_file(final_message);
}