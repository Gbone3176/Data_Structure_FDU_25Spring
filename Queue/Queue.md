# 队列

## 定义
### 循环队列

```c
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 5  // 定义队列的最大容量

typedef struct {
    int items[MAX_SIZE];
    int front;
    int rear;
} Queue;

// 初始化队列
void initQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

// 检查队列是否为空
bool isEmpty(Queue *q) {
    return q->front == -1;
}


// 检查队列是否已满
bool isFull(Queue *q) {
    return (q->rear + 1) % MAX_SIZE == q->front;
}

// 入队操作
void enqueue(Queue *q, int value) {
    if (isFull(q)) {
        printf("队列已满，无法入队\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = 0;
    }
    q->rear = (q->rear + 1) % MAX_SIZE;
    q->items[q->rear] = value;
    printf("入队元素: %d\n", value);
}

// 出队操作
int dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("队列为空，无法出队\n");
        return -1;
    }
    int value = q->items[q->front];
    if (q->front == q->rear) { //剩下最后一个队员，出队后，将q->front和q->rear置为-1
        q->front = -1;
        q->rear = -1;
    } else {
        q->front = (q->front + 1) % MAX_SIZE;
    }
    printf("出队元素: %d\n", value);
    return value;
}

// 获取队列的大小
int size(Queue *q) {
    if (isEmpty(q)) {
        return 0;
    }
    if (q->rear >= q->front) {
        return q->rear - q->front + 1;
    } else {
        return MAX_SIZE - q->front + q->rear + 1;
    }
}

// 打印队列中的元素
void printQueue(Queue *q) {
    if (isEmpty(q)) {
        printf("队列为空\n");
        return;
    }
    printf("队列中的元素: ");
    int i = q->front;
    while (i != q->rear) {
        printf("%d ", q->items[i]);
        i = (i + 1) % MAX_SIZE;
    }
    printf("%d\n", q->items[i]);
}

int main() {
    Queue q;
    initQueue(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    enqueue(&q, 40);
    enqueue(&q, 50);
    enqueue(&q, 60);  // 队列已满，无法入队

    printQueue(&q);

    dequeue(&q);
    dequeue(&q);

    printQueue(&q);

    enqueue(&q, 70);
    enqueue(&q, 80);

    printQueue(&q);

    printf("队列的大小: %d\n", size(&q));

    return 0;
}
```


## 例题

1. OJ1：maze



2. OJ2：

### Description

#### 题目背景
某物联网（IoT）数据监控系统需要对传感器发送过来的数值流进行实时分析。已获取最近一段时间内n个测量值（存放于整数数组nums中），并希望以固定大小k的“滑动窗口”逐个移动来判断每个窗口中的最大测量值，以便及时发现异常。由于系统需要处理海量数据且追求低延迟，要求算法在整体上达成O(n)时间复杂度，并明确规定使用队列（queue）来完成对最大值的维护。

#### 题目描述
给定一个长度为n的整数数组nums和一个窗口大小k（其中1≤k≤n），请依次将大小为k的窗口从数组左端向右端移动，每移动一次仅右移一格。每移动到一个新位置时，求出当前窗口中所有元素的最大值。请你使用队列（可采用双端队列deque）来完成对最大值的快速更新，并保证整个过程的时间复杂度为O(n)。

### Input

#### 输入格式
第一行输入一个整数n，表示数组的长度。  
第二行输入n个整数，作为数组nums的元素。  
第三行输入一个整数k，表示滑动窗口的大小。  

#### 限制条件
1≤k≤n  
1<n<100  
nums[i]无限制  

### Output

#### 输出格式
输出一行共(n−k+ 1)个整数，每个整数表示当滑动窗口位于相应位置时的最大值数值间以单个空格分隔。

**input**
```
8
1 3 -1 -3 5 3 6 7
3
```

**output**
```
3 3 5 5 6 7
```

