// AOE(Activity On Edge)问题

#include <stdio.h>
#include <stdlib.h>

#define MaxN 101

/* 图定义开始 */
typedef struct GNode
{
    int Nv, Ne;
    int G[MaxN][MaxN];
} * MGraph;

MGraph CreateGraph(int N, int M)
{
    MGraph Graph = malloc(sizeof(struct GNode));
    Graph->Nv = N;
    Graph->Ne = M;

    for (int i = 0; i < Graph->Nv; i++) // 初始化
    {
        for (int j = 0; j < Graph->Nv; j++)
        {
            Graph->G[i][j] = -1; // 用负数表示两个检查点之间不存在活动
        }
    }

    int v1, v2, weight; // 录入边
    for (int i = 0; i < Graph->Ne; i++)
    {
        scanf("%d %d %d", &v1, &v2, &weight);
        Graph->G[v1][v2] = weight; // 有向图
    }

    return Graph;
}
/* 图定义结束 */

/* 队列定义开始 */
typedef struct QNode
{
    int front, rear;
    int Data[MaxN];
} * Queue;

Queue CreateQ()
{
    Queue Q = malloc(sizeof(struct QNode));
    Q->front = Q->rear = 0;
    return Q;
}

void AddQ(Queue Q, int x)
{
    if ((Q->front + 1) % MaxN == Q->rear) //已满
    {
        printf("Full!\n");
        return;
    }
    Q->front = (Q->front + 1) % MaxN;
    Q->Data[Q->front] = x;
}

int DeleteQ(Queue Q)
{
    if (Q->rear == Q->front)
    {
        printf("Empty!\n");
        return -1;
    }
    Q->rear = (Q->rear + 1) % MaxN;
    return Q->Data[Q->rear];
}
/* 队列定义结束 */

void HowLong(MGraph Graph)
{
    int InDegree[MaxN];   // 某点的入度
    Queue Q = CreateQ(); // 创建循环队列

    for (int j = 0; j < Graph->Nv; j++) // 计算所有点的入度
    {
        InDegree[j] = 0;
        for (int i = 0; i < Graph->Nv; i++)
        {
            if (Graph->G[i][j] != -1) // 若有连接<i, j>的边
            {
                InDegree[j]++;
            }
        }
        if (!InDegree[j]) // 将所有入度为零的点入队
        {
            AddQ(Q, j);
        }
    }

    int Earliest[MaxN] = {0}; // 存储到达某检查点的最早时间
    int VCount = 0; //记录已经计算过的检查点个数
    int V; // 记录入度为零的点
    int LastTime = 0;

    while (Q->front != Q->rear)
    {
        V = DeleteQ(Q); // 出队一个入度为0的点作为活动起始点
        VCount++;
        int OutDegree = 0;
        for (int W = 0; W < Graph->Nv; W++)
        {
            if (Graph->G[V][W] != -1) // 到下一个检查点之间有活动
            {
                OutDegree++;
                if (Earliest[V] + Graph->G[V][W] > Earliest[W])
                {
                    Earliest[W] = Earliest[V] + Graph->G[V][W]; // 取所有上级检查点中最大的完成时间
                }
                if (!--InDegree[W]) // 若入度变为0则入队
                {
                    AddQ(Q, W);
                }
            }
        }
        if (!OutDegree && Earliest[V] > LastTime) // 若V无出度，即已经到达终点（其中之一）
        {
            LastTime = Earliest[V];
        }
    } // while结束

    if (VCount < Graph->Nv) // 说明还未完成所有检查点
    {
        printf("Impossible\n");
    }
    else
    {
        printf("%d\n", LastTime);
    }
}

int main()
{
    int N, M;
    scanf("%d %d", &N, &M);
    MGraph Graph = CreateGraph(N, M);
    HowLong(Graph);
    return 0;
}