bool Solution(int maxChoosableInteger, int desiredTotal, int *nums, int *dp) {
    if (desiredTotal <= 0) {
        // 如果总和小于等于0，则当前玩家输
        return false;
    }
    if (dp[desiredTotal] != -1) {
        // 如果已经计算过，则直接返回结果
        return dp[desiredTotal];
    }

    for (int i = 0; i < maxChoosableInteger; i++) {
        if (nums[i] != 0) {
            // 如果当前数字没选择过，则选择
            int newValue = desiredTotal - (i + 1); // 新的值为总和减去当前数字
            nums[i] = 0; // 选择当前数字
            if (!Solution(maxChoosableInteger, newValue, nums, dp)) {
                // 如果当前玩家输，则返回true
                dp[desiredTotal] = 1;
                nums[i] = 1;
                return true;
            }
            nums[i] = 1;
        }
    }
    return false;
}

bool canIWin(int maxChoosableInteger, int desiredTotal) {
    if (desiredTotal <= 0) {
        return true;
    }
    if (maxChoosableInteger * (maxChoosableInteger + 1) / 2 < desiredTotal) {
        return false;
    }
    int dp[desiredTotal + 1]; // 定义dp数组
    memset(dp, -1, sizeof(dp));
    int nums[maxChoosableInteger]; // 定义数字数组
    memset(nums, 1, sizeof(nums));

    return Solution(maxChoosableInteger, desiredTotal, nums, dp);
}