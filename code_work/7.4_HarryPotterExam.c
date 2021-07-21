#include <stdio.h>
#include <stdlib.h>

#define MaxN 100
#define INFINITY 10000

typedef struct GNode 
{
    int Nv, Ne;
    int G[MaxN][MaxN];
} * MGraph;

typedef struct ENode
{
    int V1, V2;
    int Weight;
} * Edge;

MGraph CreateGraph(int N)
{
    MGraph Graph = malloc(sizeof(struct GNode));
    Graph->Nv = N;
    Graph->Ne = 0;
    for (int i = 0; i < Graph->Nv; i++)
    {
        for (int j = 0; j < Graph->Nv; j++)
        {
            Graph->G[i][j] = INFINITY;
        }
    }
    return Graph;
}

void InsertEdge(MGraph Graph, Edge E)
{
    Graph->G[E->V1][E->V2] = E->Weight;
    Graph->G[E->V2][E->V1] = E->Weight; //若为无向图；
}

void ReadGraph(MGraph Graph)
{
    Edge E = malloc(sizeof(struct ENode));
    for (int i = 0; i < Graph->Ne; i++)
    {
        scanf("%d %d %d", &E->V1, &E->V2, &E->Weight);
        E->V1--; //读入参数从1开始
        E->V2--;
        InsertEdge(Graph, E);
    }
    free(E);
}

void Floyd(MGraph Graph, int D[][MaxN]) //返回邻接矩阵中所有点的最短距离矩阵
{
    int i, j, k;
    for (i = 0; i < Graph->Nv; i++)
    {
        for (j = 0; j < Graph->Nv; j++)
        {
            D[i][j] = Graph->G[i][j]; //初始化，将无法到达的点设为无穷大；
            // path[i][j] = -1;
        }
    }
    for (k = 0; k < Graph->Nv; k++)
    {
        for (i = 0; i < Graph->Nv; i++)
        {
            for (j = 0; j < Graph->Nv; j++)
            {
                if (D[i][k] + D[k][j] < D[i][j])
                {
                    D[i][j] = D[i][k] + D[k][j]; // 不断更新距离更短的路径
                    // if ( i == j && D[i][j] < 0 ) /* 若发现负值圈 */
                    // {
                    //     return 0; /* 不能正确解决，返回错误标记 */
                    // }    
                    // path[i][j] = k;
                }
            }
        }
    }
}

void GetRes(int D[][MaxN], int N) //从距离矩阵中分析得到最后结果
{
    int RowMin = INFINITY, ColMax, MinIndex, i, j; 
    //需要找到每一行的最大值（最长的魔咒），以及魔咒最短的行
    for (i = 0; i < N; i++)
    {
        ColMax = 0;
        for (j = 0; j < N; j++)
        {
            if (i != j && D[i][j] > ColMax)
            {
                if (D[i][j] == INFINITY) //存在无法变形的点
                {
                    printf("0");
                    return;
                }
                ColMax = D[i][j];
            }
        }
        if (ColMax < RowMin)
        {
            MinIndex = i;
            RowMin = ColMax;
        }
    }
    printf("%d %d", MinIndex + 1, RowMin);
}

void PrintGraph(int D[][MaxN], int N)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            printf("%d ", D[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    int nv;
    scanf("%d", &nv);
    MGraph Graph = CreateGraph(nv);
    scanf("%d", &Graph->Ne); //读入第一行的Nv, Ne
    ReadGraph(Graph); //读入边并建立图
    int D[MaxN][MaxN];
    Floyd(Graph, D);
    // PrintGraph(D, Graph->Nv);
    GetRes(D, Graph->Nv);
    return 0;
}