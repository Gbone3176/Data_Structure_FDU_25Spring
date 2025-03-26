// 代价最小的路径问题

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include <stdio.h>
#include <limits.h>

#define MAX_SIZE 102

int cost[MAX_SIZE][MAX_SIZE];    // 存储每个格子的代价
int dist[MAX_SIZE][MAX_SIZE];    // 存储到每个格子的最小代价

typedef struct {
    int x, y;
} Point;

Point queue[1000000];            // 队列用于BFS
int front = 0, rear = 0;

int main() {
    //读取M N
    int M,N;
    scanf("%d %d", &M, &N);

    //初始化cost数组
    for (int i = 0; i < M + 2; i++) {
        for(int j = 0; j < N + 2; j++) {
            scanf("%d", &cost[i][j]);
        }
    }
    //初始化dist数组
    for (int i = 0; i < M + 2; i++) {
        for(int j = 0; j < N + 2; j++) {
            dist[i][j] = INT_MAX;
        }
    }
    //初始化入口代价
    dist[1][1] = cost[1][1];

    //将起点加入队列
    queue[rear].x = 1;
    queue[rear].y = 1;
    rear++;

    //设定移动方向
    int dx[4] = {0, 0, 1, -1};
    int dy[4] = {1, -1, 0, 0};

    //处理节点
    while(front < rear) {
        Point p = queue[front];
        if (p.x == M && p.y == N) break;
        front++;

        //遍历四个方向
        for (int i = 0; i < 4; i++) {
            int nx = p.x + dx[i];
            int ny = p.y + dy[i];

            //判断是否越界
            if (nx < 1 || nx > M || ny < 1 || ny > N) {
                continue;
            }

            //判断是否更新
            if (dist[nx][ny] > dist[p.x][p.y] + cost[nx][ny]) {
                dist[nx][ny] = dist[p.x][p.y] + cost[nx][ny];
                queue[rear].x = nx;
                queue[rear].y = ny;
                rear++;
            }
        }
    }
    
    //输出结果
    printf("%d\n", dist[M][N]);

    return 0;
}