#define MaxValue 1000

typedef struct BrowserHistory {
    char *history[MaxValue];  // 历史记录数组
    int index;                // 当前页的索引
    int historySize;          // 历史记录的数量
} BrowserHistory;

// 创建 BrowserHistory 实例
BrowserHistory* browserHistoryCreate (char* homepage) {
    BrowserHistory *obj = (BrowserHistory *) malloc(sizeof(BrowserHistory));
    obj -> index = 0;
    obj -> historySize = 1;  // 初始化时主页已经是一个记录
    obj -> history[0] = homepage;  // 将主页作为历史记录存储
    return obj;
}

// 访问新页面
void browserHistoryVisit(BrowserHistory* obj, char* url) {
    obj -> index++;  // 将当前页索引增加
    obj -> history[obj -> index] = url;  // 将新页面添加到历史记录
    if (obj -> index < obj -> historySize) {
        obj -> historySize = obj -> index + 1;  // 更新历史记录大小
    } else {
        obj -> historySize++;  // 增加历史记录的数量
    }
}

char* browserHistoryBack(BrowserHistory* obj, int steps) {
    obj -> index -= steps;  // 回退 steps 步
    if (obj -> index < 0) {
        obj -> index = 0;  // 如果回退到负数，则返回最开始的页面
    }
    return obj -> history[obj -> index];
}

char* browserHistoryForward(BrowserHistory* obj, int steps) {
    obj -> index += steps;  // 前进 steps 步
    if (obj -> index >= obj -> historySize) {
        obj -> index = obj - >historySize - 1;  // 如果前进超出历史记录总大小，停留在最后一个页面
    }
    return obj -> history[obj -> index];
}

void browserHistoryFree(BrowserHistory* obj) {
    free(obj);
}