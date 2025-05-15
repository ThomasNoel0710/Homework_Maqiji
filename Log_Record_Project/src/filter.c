// filter.c
#include "logger.h"
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define MAX_LOG_ENTRIES 1000
#define HASH_TABLE_SIZE 128

typedef struct LogEntry {
    char message[512];
    int count;              // 1分钟内出现次数
    time_t first_time;      // 第一次出现的时间
    time_t last_hour_time;  // 上次打印时间（用于1小时去重）
    int is_massive;         // 是否为海量日志
    struct LogEntry* next;
} LogEntry;

// 哈希表存储日志信息
static LogEntry* hash_table[HASH_TABLE_SIZE];

// 哈希函数
unsigned int hash(const char* str) {
    unsigned int hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % HASH_TABLE_SIZE;
}

// 查找或创建日志条目
LogEntry* get_or_create_entry(const char* message) {
    unsigned int index = hash(message);
    LogEntry* entry = hash_table[index];

    while (entry) {
        if (strcmp(entry->message, message) == 0) {
            return entry;
        }
        entry = entry->next;
    }

    // 没找到，新建一个
    entry = (LogEntry*)calloc(1, sizeof(LogEntry));
    strncpy(entry->message, message, sizeof(entry->message) - 1);
    entry->count = 0;
    entry->first_time = time(NULL);
    entry->last_hour_time = 0;
    entry->is_massive = 0;

    // 插入哈希链表头部
    entry->next = hash_table[index];
    hash_table[index] = entry;

    return entry;
}

// 清理旧的计数器（每调用一次检查时间范围）
void cleanup_old_entries() {
    time_t now = time(NULL);
    for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
        LogEntry* prev = NULL;
        LogEntry* curr = hash_table[i];

        while (curr) {
            // 超过1分钟，重置1分钟计数
            if (now - curr->first_time > 60) {
                curr->count = 0;
            }

            // 移动指针
            prev = curr;
            curr = curr->next;
        }
    }
}

// 过滤打印逻辑
int log_filter_print(const char* message) {
    cleanup_old_entries();
    LogEntry* entry = get_or_create_entry(message);
    time_t now = time(NULL);

    // 判断是否是海量日志（1分钟内 >= 60次）
    if (now - entry->first_time <= 60) {
        entry->count++;
        if (entry->count >= 60) {
            entry->is_massive = 1;
        }
    } else {
        entry->count = 1;
        entry->first_time = now;
    }

    // 如果是海量日志，且不是今天第一次打印，则跳过
    if (entry->is_massive) {
        if (now - entry->last_hour_time < 3600) {
            return 0; // 不打印
        } else {
            entry->last_hour_time = now;
            log_record(LOG_LEVEL_INFO, "[FILTERED MASSIVE] %s", message);
            return 1;
        }
    }

    // 非海量日志，但判断1小时内是否已打印过相同消息
    static char last_filtered_message[512] = {0};
    static time_t last_filtered_time = 0;

    if (strcmp(last_filtered_message, message) == 0 && now - last_filtered_time <= 3600) {
        return 0;
    }

    strncpy(last_filtered_message, message, sizeof(last_filtered_message) - 1);
    last_filtered_time = now;

    log_record(LOG_LEVEL_INFO, "[FILTERED] %s", message);
    return 1;
}