int Max(int a, int b) {
    return a > b ? a : b;
}
int maxProfitAssignment(int* difficulty, int difficultySize, int* profit, int profitSize, int* worker, int workerSize) {
    int res = 0; // 结果
    int cur = 0; // 当前的值
    int len = workerSize;
    int lenOfTask = profitSize;

    for (int i = 0; i < len; i++) {
        // 对每一个worker进行遍历
        cur = 0;
        for (int j = 0; j < lenOfTask; j++) {
            // 如果该任务在能力范围内，更新利益最大值
            if (difficulty[j] <= worker[i]) {
                cur = Max(cur, profit[j]);
            }
        }
        res += cur;
    }

    return res;
    
}