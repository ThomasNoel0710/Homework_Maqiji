bool checkInclusion(char* s1, char* s2) {
    int len1 = strlen(s1); // s1长度
    int len2 = strlen(s2); // s2长度

    if (len1 > len2) {
        // s1长度大于s2长度，肯定不可能包含
        return false;
    }

    int s1Count[256] = {0}; // s1字符出现次数,256为ASCII码个数
    int temCount[256] = {0}; // 临时数组，用于记录s2中s1的子串出现次数

    for (int i = 0; i < len1; i++) {
        s1Count[s1[i]]++; // 记录s1中字符出现次数
        temCount[s2[i]]++; // 记录s2中最开始的滑动窗口中字符出现次数
    }
    if (memcmp(s1Count,temCount,sizeof(s1Count)) == 0) {
        // 如果相同，则结果为真
        return true;
    }

    for (int i = len1; i < len2; i++) {
        // 移动窗口
        temCount[s2[i]]++;
        temCount[s2[i - len1]]--;
        if (memcmp(s1Count,temCount,sizeof(s1Count)) == 0) {
            return true;
        }
    }

    return false;
}