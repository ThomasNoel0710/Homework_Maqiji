int Compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int findPairs(int* nums, int numsSize, int k) {
    qsort(nums, numsSize, sizeof(int), Compare);
    int sum = 0;

    for (int i = 0; i < numsSize - 1; i++) {
        // 去重：如果当前元素和前一个一样，跳过
        if (i > 0 && nums[i] == nums[i - 1]) continue;

        if (k == 0) {
            // 查找是否有与当前 nums[i] 相等的后继元素
            int j = i + 1;
            while (j < numsSize && nums[j] == nums[i]) {
                j++;
            }
            if (j > i + 1) { // 至少有两个相同的数
                sum++;
            }
            // 跳过所有相同元素
            while (i + 1 < numsSize && nums[i] == nums[i + 1]) {
                i++;
            }
        } else {
            // 暴力查找是否存在 nums[i] + k
            for (int j = i + 1; j < numsSize; j++) {
                if (nums[j] - nums[i] == k) {
                    sum++;
                    break;
                }
            }
        }
    }

    return sum;
}