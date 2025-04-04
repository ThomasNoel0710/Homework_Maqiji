/* 整体思路：利用动态规划思想，遍历每个位置，保存到当前位置的最小值，最后返回最后一行的最小值。 */
int Min(int a, int b)
{
    return a > b ? b : a;
}

int MinimumTotal(int **triangle, int triangleSize, int *triangleColSize) 
{
    if (triangleSize == 1) {
        return triangle[0][0]; // 只有一行，直接返回该行的最小值
    }
    for (int i = 1; i < triangleSize; i++) {
        // 从第二行开始遍历
        for (int j = 0; j < triangleColSize[i]; j++) {
            if (j == 0) {
                // 第一列
                triangle[i][j] = triangle[i][j] + triangle[i - 1][j];
            }
            else if (j == triangleColSize[i] - 1) {
                // 最后一列
                triangle[i][j] = triangle[i][j] + triangle[i - 1][j - 1];
            }
            else {
                // 中间列
                triangle[i][j] = triangle[i][j] + Min(triangle[i - 1][j - 1], triangle[i - 1][j]);
            }
        }
    }

    int finalRow = triangleSize - 1; // 最后一行的索引
    int res = INT_MAX; // 初始化最小值

    for (int i = 0; i < triangleColSize[finalRow]; i++) {
        res = Min(res, triangle[finalRow][i]); // 更新最小值
    }

    return res;
}