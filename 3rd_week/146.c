#define MAX_VALUE 3000
typedef struct {
    int key;
    int value;
} Node;

typedef struct {
    int capacity; // 总的容量
    int size; // 当前已用容量
    Node* map[MAX_VALUE]; // 哈希表
    int arr[MAX_VALUE];   // 最近最少使用顺序
} LRUCache;


LRUCache* lRUCacheCreate(int capacity) {
    // 初始化obj对象
    LRUCache* obj = (LRUCache*) malloc (sizeof(LRUCache));
    obj -> capacity = capacity;
    obj -> size = 0;
    for(int i = 0; i < capacity; i++) {
        obj -> map[i] = NULL;
        obj -> arr[i] = -1;
    }
    return obj;
}

int lRUCacheGet(LRUCache* obj, int key) {
    for(int i = 0; i < obj -> size; i++) {
        if(obj -> arr[i] == key) {
            // 当找到key时，调整顺序，以让当前key排在最后面
            for(int i = 0; i < obj -> size - 1; i++) {
                obj -> arr[i] = obj -> arr[i + 1]; 
            }
            obj -> arr[obj -> size - 1] = key;
            return obj -> map[key] -> value; // 返回对应的value
        }
    }
    return -1;
}

void lRUCachePut(LRUCache* obj, int key, int value) {
    if (obj -> size < obj -> capacity) {
        // 当容量未满时，直接添加
        obj -> map[key] = (Node*) malloc (sizeof(Node));
        obj -> map[key] -> key = key;
        obj -> map[key] -> value = value;
        obj -> arr[obj -> size++] = key;
    }
    else {
        // 当容量已满时，先删除最久未使用的数据
        int last = obj -> arr[0];
        free(obj -> map[last]);
        for (int i = 0; i < obj -> size - 1; i++) {
            // 调整顺序
            obj -> arr[i] = obj -> arr[i + 1]; 
        }
        obj -> arr[obj -> size - 1] = key; // 让当前key排在最后面

        obj -> map[key] = (Node*) malloc (sizeof(Node));
        obj -> map[key] -> key = key;
        obj -> map[key] -> value = value;
    }
}

void lRUCacheFree(LRUCache* obj) {
    // 释放哈希表和顺序表
    for (int i = 0; i < obj -> size; i++) {
        free(obj -> map[obj -> arr[i]]);
    }
    free(obj);
}

/**
 * Your LRUCache struct will be instantiated and called as such:
 * LRUCache* obj = lRUCacheCreate(capacity);
 * int param_1 = lRUCacheGet(obj, key);
 
 * lRUCachePut(obj, key, value);
 
 * lRUCacheFree(obj);
*/