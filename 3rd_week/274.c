int Compare(const void* a, const void* b) {
    return *(int*) a - *(int*) b;
}

int Max(int a, int b) {
    return a > b ? a : b;
}

int Min(int a, int b) {
    return a < b ? a : b;
}

int hIndex(int* citations, int citationsSize) {
    int res = 0; // 存储结果
    int remain = 0; // 数组中剩余的元素个数
    int hIndex = 0; // 存储当前h指数
    int elementSize = sizeof(citations[0]); // 每个元素的大小
    qsort(citations, citationsSize, elementSize, Compare);

    for (int i = 0; i < citationsSize; i++) {
        remain = citationsSize - i; // 计算剩余元素个数
        hIndex = Min(citations[i], remain); // h指数为当前元素和剩余元素中较小的那个
        res = Max(res, hIndex); // 更新结果，保留最大的h指数
    }

    return res;
}