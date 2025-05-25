int Min(int a, int b) {
    return a > b ? b : a;
}

int maxScore(int* cardPoints, int cardPointsSize, int k) {
    int len = cardPointsSize; // 数组长度
    int res = 0; // 记录最大分数
    int sum = 0; // 记录数组元素之和
    int tem = 0; // 记录当前分数
    int remain = len - k; // 记录剩余数组长度
    int sum = 0; // 记录数组元素之和

    for (int i = 0; i < len; i++) {
        sum += cardPoints[i];
    }

    for (int i = 0; i < remain; i++) {
        // 计算当前分数
        tem += cardPoints[i];
    }
    res = tem;
    for (int i = remain; i < len; i++) {
        // 使用滑动窗口更新最大分数
        tem -= cardPoints[i - remain];
        tem += cardPoints[i];
        res = Min(res, tem); // 更新能够得到的最小的子数组
    }

    res = sum - res;
    return res;
}
