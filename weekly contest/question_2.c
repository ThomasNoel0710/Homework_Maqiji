// 未通过部分用例
int maxSubstrings(char* word) {
    int len = strlen(word);
    if (len < 4) return 0;

    int* arr = calloc(len, sizeof(int));
    int res = 0;

    for (int i = 0; i < len;) {
        if (arr[i] == 1) {
            i++;
            continue;
        }

        bool found = false;
        for (int j = i + 3; j < len; j++) {
            if (arr[j] == 1) {
                break;
            }
            if (word[i] == word[j]) {
                for (int k = i; k <= j; k++) {
                    arr[k] = 1;
                }
                res++;
                i = j + 1;
                found = true;
                break;
            }
        }

        if (!found) {
            arr[i] = 1;
            i++;
        }
    }

    free(arr);
    return res;
}