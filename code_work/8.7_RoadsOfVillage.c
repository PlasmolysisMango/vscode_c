// Prim算法，使用邻接矩阵表示图

#include <stdio.h>
#include <stdlib.h>

#define MaxN 1001 //最大N
#define INF 65535 //正无穷

typedef struct GNode
{
    int Nv, Ne; 
    int G[MaxN][MaxN];
} * MGraph;

MGraph InitGraph() // 初始化图
{
    int N, M;
    scanf("%d %d", &N, &M);

    MGraph Graph = (MGraph)malloc(sizeof(struct GNode));
    Graph->Nv = N;
    Graph->Ne = M;
    for (int i = 0; i <= Graph->Nv; i++)
    {
        for (int j = 0; j <= Graph->Nv; j++)
        {
            Graph->G[i][j] = INF;
        }
    }
    return Graph;
}

void InsertEdge(MGraph Graph, int v1, int v2, int weight) // 插入无相图的边
{
    Graph->G[v1][v2] = Graph->G[v2][v1] = weight;
}

int dist[MaxN]; //记录距离最小生成树的权重和

int FindMinDist(MGraph Graph) //返回未收录顶点中dist最小的下标，-1表示不存在
{
    int minindex = -1, mindist = INF;
    for (int i = 1; i <= Graph->Nv; i++)
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
    for (int i = 0; i < Graph->Nv; i++)
    {
        dist[i] = Graph->G[0][i]; //初始化dist为起点0到某点的直接权重，若不相连则为INF
    }
    dist[0] = 0; //起点的dist为0
    while (1)
    {
        int v = FindMinDist(Graph); // 未收录顶点中dist最小的下标
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

void ReadGraph(MGraph Graph)
{
    int v1, v2, weight;
    for (int i = 0; i < Graph->Ne; i++)
    {
        scanf("%d %d %d", &v1, &v2, &weight);
        InsertEdge(Graph, v1-1, v2-1, weight);
    }
}

int main()
{
    MGraph Graph = InitGraph();
    ReadGraph(Graph);
    Prim(Graph);
    return 0;

}