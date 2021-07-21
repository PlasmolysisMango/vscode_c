#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MaxN 200

typedef struct GNode
{
    int Nv;
    int G[MaxN][MaxN]; //在图中存储任意两点之间是否可以跳跃，1 or 0
} *MGraph;

typedef struct PointNode
{
    int x, y;
} Point; //用来存储所有点的坐标

typedef struct QNode //循环队列
{
    int front, rear;
    int Data[MaxN];
} * Queue;

typedef struct SNode // 数组堆栈
{
    int Top;
    int Data[MaxN];
} * Stack;

Stack CreateS()
{
    Stack S = malloc(sizeof(struct SNode));
    S->Top = -1;
    return S;
}

void Push(Stack S, int x)
{
    S->Data[++S->Top] = x;
}

int Pop(Stack S)
{
    return S->Data[S->Top--];
}

Queue CreateQ()
{
    Queue Q = malloc(sizeof(struct QNode));
    Q->front = Q->rear = 0; //保证最多只存储N-1个元素
    return Q;
}

void AddQ(Queue Q, int x)
{
    Q->rear = (Q->rear + 1) % MaxN;
    Q->Data[Q->rear] = x;
}

int DeleteQ(Queue Q)
{
    Q->front = (Q->front + 1) % MaxN;
    return Q->Data[Q->front];
}

MGraph CreateGraph(int N)
{
    MGraph Graph = malloc(sizeof(struct GNode));
    Graph->Nv = N;
    return Graph;
}

void SingleSource(MGraph Graph, int S, int dist[], int path[]) //单源最短路径算法
{
    for (int i = 0; i < Graph->Nv; i++)
    {
        dist[i] = path[i] = -1; //dist[]初始化
    }
    dist[S] = 0;
    Queue Q = CreateQ();
    AddQ(Q, S);
    while (Q->front != Q->rear) //如果队列不空
    {
        int V = DeleteQ(Q);
        for (int i = 0; i < Graph->Nv; i++)
        {
            if (Graph->G[V][i] && dist[i] == -1) // 对V的未访问过的邻接点
            {
                dist[i] = dist[V] + 1;
                path[i] = V;
                AddQ(Q, i);
            }
        }
    }
}

int JudgeDistance(Point A, Point B, double D)
{
    return pow((A.x - B.x), 2) + pow((A.y - B.y), 2) <= pow(D, 2);
}

Point APoint(Point A) //调试很久的bug居然出在这里，乌鱼子..
{
    Point B;
    B.x = abs(A.x);
    B.y = abs(A.y);
    return B;
}

void BuildEdge(MGraph Graph, Point Plist[], int SafeList[], int D) // 根据距离构建图
{
    Point bx, by;
    bx.x = by.y = 50;
    for (int i = 0; i < Graph->Nv; i++)
    {
        bx.y = abs(Plist[i].y);
        by.x = abs(Plist[i].x);
        SafeList[i] = JudgeDistance(APoint(Plist[i]), bx, D) || JudgeDistance(APoint(Plist[i]), by, D);
        // 标记是否可以直接跳出的点
        for (int j = 0; j < Graph->Nv; j++) // 可以跳跃则为1，反之则为0
        {
            if (i == 0) //对于起点的情况
            {
                Graph->G[i][j] = JudgeDistance(Plist[i], Plist[j], 7.5 + D);
            }
            else
            {
                Graph->G[i][j] = JudgeDistance(Plist[i], Plist[j], D);
            }
            if (i == j)
            {
                Graph->G[i][j] = 0;
            }
        }
    }
}

void ReadList(Point Plist[], int N)
{
    Plist[0].x = Plist[0].y = 0; //初始点
    for (int i = 1; i < N; i++)
    {
        scanf("%d %d", &Plist[i].x, &Plist[i].y);
    }
}

void PrintPath(int Path[], Point Plist[], int E) //打印从E到起点的所有点
{
    Stack S = CreateS();
    while (Path[E] != -1)
    {
        Push(S, E);
        E = Path[E];
    }
    while (S->Top != -1)
    {
        int i = Pop(S);
        printf("%d %d\n", Plist[i].x, Plist[i].y);
    }
}

void PrintGraph(MGraph Graph)
{
    for (int i = 0; i < Graph->Nv; i++)
    {
        for (int j = 0; j < Graph->Nv; j++)
        {
            printf("%d ", Graph->G[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int N, D;
    scanf("%d %d", &N, &D);
    N++;
    MGraph Graph = CreateGraph(N);
    Point Plist[MaxN];
    int SafeList[MaxN], dist[MaxN], path[MaxN];
    ReadList(Plist, N); // 读入所有点
    BuildEdge(Graph, Plist, SafeList, D); // 根据距离建立图
    // PrintGraph(Graph);
    SingleSource(Graph, 0, dist, path); // 单源最短距问题
    int MinDist = MaxN + 1, MinIndex = -1;
    double MinDisPath = pow(MaxN, 2);
    for (int i = 0; i < N; i++)
    {
        if (SafeList[i] && dist[i] != -1)
        {
            if (dist[i] < MinDist)
            {
                MinDist = dist[i];
                MinIndex = i;
            }
            else if (dist[i] == MinDist) //此为几个距离相同点的情况
            {
                double tdis = sqrt(pow(Plist[i].x, 2) + pow(Plist[i].y, 2));
                if (tdis < MinDisPath)
                {
                    MinDisPath = tdis;
                    MinIndex = i;
                }
            }
        }
    }
    if (MinIndex != -1)
    {
        printf("%d\n", dist[MinIndex] + 1);
        PrintPath(path, Plist, MinIndex);
    }
    else
    {
        printf("0\n");
    }
    return 0;
}