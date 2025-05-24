int Compare(const void* a, const void* b) {
    long long x = *(long long*)a;
    long long y = *(long long*)b;
    if (x > y) {
        return -1;
    }
    else if (x < y) {
        return 1;
    }
    else {
        return 0;
    }
}
bool Is_prime(long long n) {
    if (n <= 1) return false;
    for (long long i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }
    return true;
}

void Add_prime(long long num, long long** primes, int *size, int *capacity) {
    for (int i = 0; i < *size; i++) {
        if ((*primes)[i] == num) return;
    }
    if (!Is_prime(num)) return;

    if (*size == *capacity) {
        *capacity *= 2;
        *primes = realloc(*primes, sizeof(long long) * (*capacity));
    }
    (*primes)[(*size)++] = num;
}

long long sumOfLargestPrimes(char* s) {
    int len = strlen(s);
    long long* primes = malloc(sizeof(long long) * len);
    int size = 0;
    int capacity = len;

    for (int i = 0; i < len; i++) {
        long long num = 0;
        for (int j = i; j < len; j++) {
            if (s[j] >= '0' && s[j] <= '9') {
                num = num * 10 + (s[j] - '0');
                Add_prime(num, &primes, &size, &capacity);
            }
        }
    }

    qsort(primes, size, sizeof(long long), Compare);

    long long sum = 0;
    int count = 0;
    for (int i = 0; i < size && count < 3; i++, count++) {
        sum += primes[i];
    }

    return sum;
}