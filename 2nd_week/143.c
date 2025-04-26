/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
void reorderList(struct ListNode* head) {
    if (head == NULL || head -> next == NULL) {
        return;
    }

    int arr[50001]; // 利用数组保存链表的元素
    int count = 0; // 记录数组的长度
    struct ListNode* cur = head;

    while (cur != NULL) {
        // 通过遍历，保存链表的元素到数组中
        arr[count] = cur -> val;
        cur = cur -> next;
        count++;
    }

    struct ListNode* iterate = head;
    int i = 0, j = count - 1; // 两个指针，分别指向数组的头和尾

    while (i <= j) {
        // 通过指针，将数组中的元素重新插入到链表中
        if (i == j) {
            iterate -> val = arr[i];
            return;
        }
        else {
            // 交替插入新的值
            iterate -> val = arr[i];
            iterate = iterate -> next;
            iterate -> val = arr[j];
        }
        iterate = iterate -> next;
        i++; // 指针向前移动
        j--; // 指针向后移动
    }

    return;
}