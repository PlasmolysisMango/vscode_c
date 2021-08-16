// AOE问题，且要求输出关键结点
// 关键活动输出的顺序规则是：任务开始的交接点编号小者优先，起点编号相同时，与输入时任务的顺序相反。
// 这就限定了使用邻接表来实现图的存储，如果输入时按从小到大的排列，输出从大到小即可采用邻接矩阵。
// 本算法采用两个邻接表来存储实现出度入度的查询，实际应用中可以通过记录拓扑序列来避免这一点。

#include <stdio.h>
#include <stdlib.h>

#define MaxN 101
#define INF 65535

/* 图定义开始 */
typedef struct AdjVNode
{
    int AdjV;
    int Weight;
    struct AdjVNode *OutNext, *InNext;
} * PtrToAdjVNode; // 定义邻接点

typedef struct HeaderNode
{
    int InDegree, OutDegree;
    PtrToAdjVNode OutLink, InLink; // 分别指向出、入的邻接点
} * Header; // 定义头结点

typedef struct GNode
{
    int Nv, Ne;
    Header GList[MaxN];
} * LGraph;

LGraph CreateGraph(int N, int M)
{
    LGraph Graph = malloc(sizeof(struct GNode));
    Graph->Nv = N;
    Graph->Ne = M;

    for (int i = 1; i <= Graph->Nv; i++) // 初始化头结点列表
    {
        Graph->GList[i] = malloc(sizeof(struct HeaderNode));
        Graph->GList[i]->InDegree = Graph->GList[i]->OutDegree = 0;
        Graph->GList[i]->OutLink = Graph->GList[i]->InLink = NULL;
    }

    int v1, v2, weight; // 录入边
    for (int i = 0; i < Graph->Ne; i++)
    {
        scanf("%d %d %d", &v1, &v2, &weight);

        PtrToAdjVNode newnode = malloc(sizeof(struct AdjVNode));
        newnode->AdjV = v2;
        newnode->Weight = weight;

        newnode->OutNext = Graph->GList[v1]->OutLink; // 出的邻接点
        Graph->GList[v1]->OutLink = newnode;

        newnode = malloc(sizeof(struct AdjVNode));
        newnode->AdjV = v1;
        newnode->Weight = weight;

        newnode->InNext = Graph->GList[v2]->InLink; // 入的邻接点
        Graph->GList[v2]->InLink = newnode;

        Graph->GList[v1]->OutDegree++; // 更新出入度
        Graph->GList[v2]->InDegree++;
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

void KeyActivity(LGraph Graph)
{
    Queue Q = CreateQ(); // 创建循环队列

    for (int i = 1; i <= Graph->Nv; i++)
    {
        if (!Graph->GList[i]->InDegree)
        {
            AddQ(Q, i); // 初始入度为0的点入队
        }
    }

    int Earliest[MaxN] = {0}; // 存储到达某检查点的最早时间
    int VCount = 0; //记录已经计算过的检查点个数
    int LastTime = 0;

    while (Q->front != Q->rear)
    {
        int V = DeleteQ(Q); // 出队一个入度为0的点作为活动起始点
        VCount++;
        for (PtrToAdjVNode p = Graph->GList[V]->OutLink; p; p = p->OutNext)
        {
            if (Earliest[V] + p->Weight > Earliest[p->AdjV])
            {
                Earliest[p->AdjV] = Earliest[V] + p->Weight; // 取所有上级检查点中最大的完成时间
            }
            if (!--Graph->GList[p->AdjV]->InDegree)
            {
                AddQ(Q, p->AdjV);
            }
        }
        if (!Graph->GList[V]->OutDegree && Earliest[V] > LastTime) // 若V无出度，即已经到达终点（其中之一）
        {
            LastTime = Earliest[V];
        }
    } // while结束

    if (VCount < Graph->Nv) // 说明还未完成所有检查点，即工序无法完成
    {
        printf("0\n");
        return;
    }
    else
    {
        printf("%d\n", LastTime);
    }

    // 开始回推最晚完成时间
    int Latest[MaxN] = {0}; // 定义某检查点最晚的完成时间
    for (int i = 1; i <= Graph->Nv; i++)
    {
        if (!Graph->GList[i]->OutDegree)
        {
            AddQ(Q, i); // 初始出度为0的点入队
            Latest[i] = LastTime; // 关键点！：反推最晚时间的时候必须用全部活动的最早完成时间
        }
        else
        {
            Latest[i] = INF;
        }
    }

    while (Q->front != Q->rear) 
    {
        int V = DeleteQ(Q); // 出队一个出度为0的点作为活动起始点
        for (PtrToAdjVNode p = Graph->GList[V]->InLink; p; p = p->InNext)
        {
            if (Latest[V] - p->Weight < Latest[p->AdjV])
            {
                Latest[p->AdjV] = Latest[V] - p->Weight; // 取最小
            }
            if (!--Graph->GList[p->AdjV]->OutDegree)
            {
                AddQ(Q, p->AdjV);
            }
        }
    } // while结束

    for (int i = 1; i <= Graph->Nv; i++) // 开始输出关键活动
    {
        PtrToAdjVNode p = Graph->GList[i]->OutLink;
        while (p)
        {
            if (Latest[p->AdjV] - Earliest[i] == p->Weight)
            {
                printf("%d->%d\n", i, p->AdjV);
            }
            p = p->OutNext;
        }
    }
}

int main()
{
    int N, M;
    scanf("%d %d", &N, &M);
    LGraph Graph = CreateGraph(N, M);
    KeyActivity(Graph);
    return 0;
}