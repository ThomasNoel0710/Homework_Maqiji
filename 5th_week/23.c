/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
int Compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    #define maxLength 10000 // 定义最大长度
    int arr[maxLength];  
    int index = 0; // 记录数组的索引

    for (int i = 0; i < listsSize; i++) {
        struct ListNode* node = lists[i]; // 取出每一个链表的开头
        if (node) {
            while (node) {
                // 取出每一个节点的值，放入数组中
                arr[index++] = node->val;
                node = node->next;
            }
        }
    }

    qsort(arr, index, sizeof(int), Compare);

    if (index == 0) {
        return NULL;
    }

    struct ListNode* res = (struct ListNode*)malloc(sizeof(struct ListNode));
    struct ListNode* cur = res;

    for (int i = 0; i < index - 1; i++) {
        // 构造输出链表
        cur->val = arr[i];
        cur->next = (struct ListNode*)malloc(sizeof(struct ListNode));
        cur = cur->next;
    }

    cur->val = arr[index - 1];     // 最后一个节点赋值
    cur->next = NULL;              // 最后一个节点的next设置为null

    return res;
}