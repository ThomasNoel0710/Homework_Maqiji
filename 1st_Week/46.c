/* 整体思路：利用回溯法，将数组元素作为一个排列，依次取出元素，将其放入临时数组，然后递归调用，直到数组长度为1。最后返回临时数组。 */

int **g_res; // 全局变量，保存所有排列
int g_resSize; // 全局变量，保存排列数量

void BackTracking(int *nums, int numsSize, int *tem, int temSize, bool *used)
{
    if (temSize == numsSize) {
        // 排列长度等于数组长度，保存排列
        g_res[g_resSize] = (int *)malloc(numsSize * sizeof(int));

        for (int i = 0; i < numsSize; i++) {
            // 保存排列
            g_res[g_resSize][i] = tem[i];
        }
        g_resSize++; // 排列数量+1
        return;
    }

    for (int i = 0; i < numsSize; i++) {
        if (used[i]) {
            // 已经使用过的元素，跳过
            continue;
        }
        used[i] = true; // 标记元素已使用
        tem[temSize] = nums[i]; // 将元素放入临时数组
        BackTracking(nums, numsSize, tem, temSize + 1, used);//递归调用

        used[i] = false;  // 回溯
    }
}

int **Permute(int *nums, int numsSize, int *returnSize, int **returnColumnSizes) 
{
    g_resSize = 0; // 初始化排列数量
    int finalLen = 1;

    for (int i = 1; i <= numsSize; i++) {
        // 排列数量为数组长度的阶乘
        finalLen *= i;
    }
    
    g_res = (int **)malloc(finalLen * sizeof(int *)); // 申请排列数组空间
    
    int *tem = (int *)malloc(numsSize * sizeof(int));//申请临时数组空间
    bool *used = (bool *)malloc(numsSize * sizeof(bool));//申请使用标记数组空间
    memset(used, 0, numsSize * sizeof(bool)); // 初始化使用标记数组为 false

    BackTracking(nums, numsSize, tem, 0, used);//调用回溯函数

    *returnColumnSizes = (int *)malloc(finalLen * sizeof(int));//申请排列长度数组空间

    for (int i = 0; i < g_resSize; i++) {
        (*returnColumnSizes)[i] = numsSize;//排列长度为数组长度
    }

    free(tem);  
    free(used); 

    *returnSize = g_resSize;
    return g_res;
}
