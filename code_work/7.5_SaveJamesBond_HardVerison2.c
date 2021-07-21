#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MaxN 200

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

int N, D, dist[MaxN], path[MaxN]; //声明一些会用到的全局变量
Point Plist[MaxN];

int JudgeDistance(Point A, Point B, double Distance) //判断两点是否可以跳到
{
    return pow((A.x - B.x), 2) + pow((A.y - B.y), 2) <= pow(Distance, 2);
}

Point APoint(Point A) // 用于将一个Point转换到第一象限
{
    Point B;
    B.x = abs(A.x);
    B.y = abs(A.y); ////调试很久的bug居然出在这里，乌鱼子..
    return B;
}

int isSafe(Point A) //判断当前点是否可以直接跳出
{
    A = APoint(A);
    Point BX, BY;
    BX.x = BY.y = 50;
    BX.y = A.y;
    BY.x = A.x;
    int j = (JudgeDistance(A, BX, D) || JudgeDistance(A, BY, D));
    return j;
}

double FirstJumpDis(Point A) //判断当前点是否可从小岛跳上，是则返回原点距离，否则返回0.0
{
    double dis = pow((A.x), 2) + pow((A.y), 2);
    if (dis > pow(7.5, 2) && dis <= pow(D + 7.5, 2)) // 保证不在小岛上
    {
        return dis;
    }
    else
    {
        return 0.0; //浮点数
    }
}

void PrintPath(int E) //打印从E到起点的所有点
{
    Stack S = CreateS();
    do
    {
        Push(S, E);
        E = path[E];
    } while (E != -1);
    while (S->Top != -1)
    {
        int i = Pop(S);
        printf("%d %d\n", Plist[i].x, Plist[i].y);
    }
}

double FJDis[MaxN]; //存储第一次直接跳上去的点的距离

int compar(const void *p1, const void *p2) //给qsort函数使用的比较函数
{
    if (FJDis[*(int *)p1] <= FJDis[*(int *)p2])
    {
        return -1;
    }
    else
    {
        return 1;
    }
}

void BFS() //单源最短路径算法(BFS)
{
    for (int i = 0; i < N; i++)
    {
        dist[i] = path[i] = -1; //初始化
    }
    Queue Q = CreateQ();
    int FJIndex[MaxN]; //存储第一次直接跳上去的点的坐标
    for (int i = 0; i < N; i++) //记录所有点坐标及距离
    {
        FJIndex[i] = i;
        FJDis[i] = FirstJumpDis(Plist[i]);
    }
    qsort(FJIndex, N, sizeof(int), compar); //快速排序，序号从小到大
    for (int i = 0; i < N; i++) // 第一次能跳上去的点依次入队
    {
        if (FJDis[FJIndex[i]] != 0.0) //筛选能跳上去的点
        {
            // printf("%d %d\n", Plist[FJIndex[i]].x, Plist[FJIndex[i]].y);
            AddQ(Q, FJIndex[i]);
            dist[FJIndex[i]] = 2; //跳跃次数为2（0->i, i->边界）
        }
    }
    while (Q->front != Q->rear) //如果队列不空
    {
        int V = DeleteQ(Q);
        if (isSafe(Plist[V])) //如果弹出的点直接可以上岸
        {
            printf("%d\n", dist[V]);
            PrintPath(V);
            return;
        }
        for (int i = 0; i < N; i++)
        {
            if (JudgeDistance(Plist[V], Plist[i], D) && dist[i] == -1)
            // 对未访问的能跳上去的点
            {
                dist[i] = dist[V] + 1;
                path[i] = V;
                AddQ(Q, i);
            }
        }
    }
    //进行到这里则跳不出去
    printf("0\n");
}

void ReadList() //读入所有结点
{
    for (int i = 0; i < N; i++)
    {
        scanf("%d %d", &Plist[i].x, &Plist[i].y);
    }
}

int main()
{
    scanf("%d %d", &N, &D);
    ReadList(); // 读入所有点
    if (D >= 50 - 7.5) //一步跳出去的特殊情况
    {
        printf("1\n");
        return 0;
    }
    BFS(); //主逻辑
    return 0;
}