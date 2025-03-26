#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 10

// 双端队列结构
typedef struct {
    int data[MAX_SIZE];  // 存储下标
    int front;           // 队头指针
    int rear;            // 队尾指针
} Deque;

// 初始化双端队列
void initDeque(Deque *dq) {
    dq->front = 0;
    dq->rear = -1;
}

// 判断队列是否为空
int isEmpty(Deque *dq) {
    return dq->rear < dq->front;
}

// 从队尾插入
void pushBack(Deque *dq, int value) {
    dq->data[++dq->rear] = value;
}

// 从队头删除
void popFront(Deque *dq) {
    dq->front++;
}

// 从队尾删除
void popBack(Deque *dq) {
    dq->rear--;
}

// 获取队头元素
int getFront(Deque *dq) {
    return dq->data[dq->front];
}

// 获取队尾元素
int getBack(Deque *dq) {
    return dq->data[dq->rear];
}

// 滑动窗口最大值函数
int* maxSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
    if (numsSize == 0 || k == 0) {
        *returnSize = 0;
        return NULL;
    }

    Deque dq;
    initDeque(&dq);

    int *result = (int *)malloc((numsSize - k + 1) * sizeof(int));
    *returnSize = 0;

    for (int i = 0; i < numsSize; i++) {
        // 移除队列中不在窗口范围内的元素
        if (!isEmpty(&dq) && getFront(&dq) < i - k + 1) {
            popFront(&dq);
        }

        // 移除队列中比当前元素小的元素
        while (!isEmpty(&dq) && nums[getBack(&dq)] < nums[i]) {
            popBack(&dq);
        }

        // 将当前元素的下标加入队列
        pushBack(&dq, i);

        // 当窗口形成时，记录最大值
        if (i >= k - 1) {
            result[(*returnSize)++] = nums[getFront(&dq)];
        }
    }

    return result;
}

int main() {
    int len;
    scanf("%d", &len);
    int nums[len];
    for (int i = 0; i < len; i++) {
        scanf("%d", &nums[i]);
    }
    int win_len;
    scanf("%d", &win_len);

    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int k = 3;
    int returnSize;

    int *result = maxSlidingWindow(nums, len, win_len, &returnSize);

    for (int i = 0; i < returnSize; i++) {
        printf("%d ", result[i]);
    }

    free(result);
    return 0;
}