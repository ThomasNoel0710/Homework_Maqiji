#include "logger.h"
#include <stdio.h>
#include <unistd.h>

int main() {
    log_init(); // 初始化日志系统

    // 测试正常打印
    log_record(LOG_LEVEL_INFO, "This is an info message.");
    log_record(LOG_LEVEL_WARNING, "This is a warning message.");
    log_record(LOG_LEVEL_ERROR, "This is an error message.");

    // 测试过滤打印
    for (int i = 0; i < 100; ++i) { // 超过60次以测试海量日志功能
        if (log_filter_print("This is a test message.")) {
            printf("Message printed.\n");
        } else {
            printf("Message filtered.\n");
        }
        usleep(100000); // 等待0.1秒
    }

    return 0;
}