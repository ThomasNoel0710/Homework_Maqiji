/* 总体思想：利用环形队列，将数组元素循环右移k-1位，然后将最后一个元素放到第一个位置，然后再将数组元素循环右移k-1位，直到数组长度为1。最后返回第一个元素。 */
int FindTheWinner(int n, int k) 
{
    int *arr = (int *)malloc(n * sizeof(int)); // 申请数组空间
    if (arr == NULL) {
        return -1;
    }

    for (int i = 0; i < n; i++) {
        // 初始化数组
        arr[i] = i + 1;
    }
    
    int pointer1 = 0; // 环形队列的第一个指针
    int len = n; // 环形队列的长度

    while (len > 1) {
        int pointer2 = (pointer1 + k - 1) % len; // 计算指针2的位置
        
        for (int i = pointer2; i < len - 1; i++) {
            // 循环右移指针2之后的元素
            arr[i] = arr[i + 1];
        }
        len--; // 队列长度减1

        if (pointer2 >= len) {
             // 当指针2指向最后一个元素时
            pointer1 = 0;
        }
        else {
            // 指针2指向中间元素
            pointer1 = pointer2;
        }
    }

    int res = arr[0]; // 返回第一个元素
    free(arr);
    return res;
}
