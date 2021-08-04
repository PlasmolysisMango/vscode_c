// Prim算法，使用邻接矩阵表示图

#include <stdio.h>
#include <stdlib.h>

#define MaxN 1001 //最大N
#define INF 65535 //正无穷

typedef struct GNode
{
    int Nv, Ne; 
    int G[MaxN][MaxN]; //直接全局变量建立邻接矩阵可能会在大数据时出错，原因未知
} * MGraph;

MGraph CreateGraph() // 初始化图
{
    int N, M;
    scanf("%d %d", &N, &M);

    MGraph Graph = (MGraph)malloc(sizeof(struct GNode));
    Graph->Nv = N;
    Graph->Ne = M;

    for (int i = 0; i < Graph->Nv; i++)
    {
        for (int j = 0; j < Graph->Nv; j++)
        {
            Graph->G[i][j] = INF;
        }
    }

    for (int i = 0; i < Graph->Ne; i++)
    {
        int v1, v2, weight;
        scanf("%d %d %d", &v1, &v2, &weight);
        Graph->G[v1-1][v2-1] = Graph->G[v2-1][v1-1] = weight;
    }

    return Graph;
}

int FindMinDist(MGraph Graph, int dist[]) //返回未收录顶点中dist最小的下标，-1表示不存在
{
    int minindex = -1, mindist = INF;
    for (int i = 0; i < Graph->Nv; i++)
    {
        if (dist[i] && dist[i] < mindist) // 非0表示未收录
        {
            mindist = dist[i];
            minindex = i;
        }
    }
    return minindex;
}

void Prim(MGraph Graph)
{
    int totalweight = 0, edgenum = 1;
    int dist[MaxN];
    for (int i = 0; i < Graph->Nv; i++)
    {
        dist[i] = Graph->G[0][i]; //初始化dist为起点0到某点的直接权重，若不相连则为INF
    }
    dist[0] = 0;
    while (1)
    {
        int v = FindMinDist(Graph, dist); // 未收录顶点中dist最小的下标
        if (v == -1) // 若不存在则退出
        {
            break;
        }
        totalweight += dist[v]; // 累加权重和
        dist[v] = 0; // 收录v
        edgenum++;
        for (int i = 0; i < Graph->Nv; i++) // 收录v后更新所有未收录点的dist
        {
            if (dist[i] && Graph->G[v][i] < dist[i]) // 新收录点到未收录点的距离更小，此处不需要再次判断是否有边相连，因为图初始化时不相连用INF表示
            {
                dist[i] = Graph->G[v][i];   
            }
        }
    } // while 结束
    if (edgenum < Graph->Nv)
    {
        totalweight = -1;
    }
    printf("%d\n", totalweight);
}

int main()
{
    MGraph Graph = CreateGraph();
    Prim(Graph);
    return 0;
}