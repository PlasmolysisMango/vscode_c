// 采用Kruskal算法，使用边集合表示图

#include <stdio.h>
#include <stdlib.h>

#define MaxN 3001 //最大N
#define INF 65535 //正无穷

typedef struct ENode
{
    int v1, v2;
    int weight;
} * Edge;

/* 堆定义开始 */
typedef struct HNode //定义最小堆
{
    Edge Data[MaxN + 1];
    int Size;
} * MinHeap;

void PercDown(MinHeap H, int p) // 从下标p开始的堆下滤
{
    int c;
    Edge tmp = H->Data[p];
    for (; p * 2 <= H->Size; p = c)
    {
        c = p * 2;
        if (c != H->Size && H->Data[c]->weight > H->Data[c + 1]->weight)
        {
            c++;
        }
        if (H->Data[c]->weight < tmp->weight)
        {
            H->Data[p] = H->Data[c];
        }
        else
        {
            break;
        }
    }
    H->Data[p] = tmp;
}

MinHeap BuildHeap(int M)
{
    MinHeap H = malloc(sizeof(struct HNode));
    H->Data[0] = malloc(sizeof(struct ENode));
    H->Data[0]->weight = -1; // 最小堆的哨兵

    for (int i = 1; i <= M; i++) // 读入边
    {
        H->Data[i] = malloc(sizeof(struct ENode));
        scanf("%d %d %d", &H->Data[i]->v1, &H->Data[i]->v2, &H->Data[i]->weight);
    }
    H->Size = M;

    for (int p = H->Size / 2; p > 0; p--) //下滤建立最小堆
    {
        PercDown(H, p);
    }

    return H;
}

Edge DeleteMin(MinHeap H) //返回堆顶元素
{
    Edge res = H->Data[1];
    H->Data[1] = H->Data[H->Size--];
    PercDown(H, 1);
    return res;
}
/* 堆定义结束 */

/* 并查集定义开始 */
typedef int ESet[MaxN]; // 使用下标映射，根节点值为-1

int FindRoot(ESet S, int x) // 返回任意结点的根下标
{
    if (S[x] < 0)
    {
        return x;
    }
    else
    {
        return S[x] = FindRoot(S, S[x]); //路径压缩，结点直接连接最终根节点
    }
}

int Merge(ESet S, int x1, int x2) // 合并两个集合，按秩归并，若同属一个集合返回0，反之为1
{
    int r1 = FindRoot(S, x1), r2 = FindRoot(S, x2); // 返回两个结点所属集合的根节点下标(0~N-1)
    if (r1 != r2) // 若分属两个集合
    {
        if (S[r1] < S[r2]) // 注意，负数小的则元素多，将2并入1
        {
            S[r1] += S[r2];
            S[r2] = r1;
        }
        else
        {
            S[r2] += S[r1];
            S[r1] = r2;
        }
        return 1;
    }
    else // 若同属一个集合
    {
        return 0;
    }
}

void InitESet(ESet S, int N) // 初始化
{
    for (int i = 0; i < N; i++)
    {
        S[i] = -1;
    }
}

/* 并查集定义结束 */

void Kruskal(MinHeap H, int N) // 该问题下不需要返回最小生成树
{
    ESet S; 
    InitESet(S, N); // 初始化并查集
    int ECount = 0; // 记录收录的边数
    int TotalWeight = 0;
    while (ECount != N - 1 && H->Size) // 若生成树边数小于N-1，且还有边未收录
    {
        Edge E = DeleteMin(H); // 返回权重最小的边
        if (Merge(S, E->v1, E->v2)) //若v1, v2分属两个集合，则说明可以收录
        {
            TotalWeight += E->weight;
            ECount++;
        }
    }
    if (ECount != N - 1)
    {
        printf("-1\n");
    }
    else
    {
        printf("%d\n", TotalWeight);
    }
}

int main()
{
    int Nv, Ne;
    scanf("%d %d", &Nv, &Ne);
    MinHeap H = BuildHeap(Ne);
    Kruskal(H, Nv);
    return 0;
}