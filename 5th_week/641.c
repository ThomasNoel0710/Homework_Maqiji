#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int size;       // 最大容量
    int curSize;    // 当前元素个数
    int front;      // 指向队头元素的位置
    int rear;       // 指向下一个要插入的位置（队尾之后）
    int* arr;
} MyCircularDeque;

MyCircularDeque* myCircularDequeCreate(int k) {
    MyCircularDeque* obj = (MyCircularDeque*)malloc(sizeof(MyCircularDeque));
    obj->size = k + 1;  // 多留一个空间便于判断满
    obj->curSize = 0;
    obj->front = 0;
    obj->rear = 0;
    obj->arr = (int*)calloc(obj->size, sizeof(int));
    return obj;
}

bool myCircularDequeInsertFront(MyCircularDeque* obj, int value) {
    if (myCircularDequeIsFull(obj)) {
        return false;
    }
    obj->front = (obj->front - 1 + obj->size) % obj->size; // 指向队首的位置
    obj->arr[obj->front] = value; // 添加值
    obj->curSize++;
    return true;
}

bool myCircularDequeInsertLast(MyCircularDeque* obj, int value) {
    if (myCircularDequeIsFull(obj)) {
        return false;
    }
    obj->arr[obj->rear] = value; // 添加到末尾的位置
    obj->rear = (obj->rear + 1) % obj->size; // 指向下一个位置
    obj->curSize++;
    return true;
}

bool myCircularDequeDeleteFront(MyCircularDeque* obj) {
    if (myCircularDequeIsEmpty(obj)) {
        return false;
    }
    obj->front = (obj->front + 1) % obj->size; // 将下一个指向的值作为开始
    obj->curSize--;
    return true;
}

bool myCircularDequeDeleteLast(MyCircularDeque* obj) {
    if (myCircularDequeIsEmpty(obj)) {
        return false;
    }
    obj->rear = (obj->rear - 1 + obj->size) % obj->size; // 将队尾指向上一个位置
    obj->curSize--;
    return true;
}

int myCircularDequeGetFront(MyCircularDeque* obj) {
    if (myCircularDequeIsEmpty(obj)) {
        return -1;
    }
    return obj->arr[obj->front];
}

int myCircularDequeGetRear(MyCircularDeque* obj) {
    if (myCircularDequeIsEmpty(obj)) {
        return -1;
    }
    return obj->arr[(obj->rear - 1 + obj->size) % obj->size];
}

bool myCircularDequeIsEmpty(MyCircularDeque* obj) {
    return obj->curSize == 0;
}

bool myCircularDequeIsFull(MyCircularDeque* obj) {
    return (obj->rear + 1) % obj->size == obj->front;
}

void myCircularDequeFree(MyCircularDeque* obj) {
    free(obj->arr);
    free(obj);
}