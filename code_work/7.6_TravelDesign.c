// Dijkstra算法（单源最短路径）的修改
#include <stdio.h>
#include <stdlib.h>

#define MaxN 1000

typedef struct CNode
{
    int length; // 首要的权重
    int price; // 距离相等时考虑的次要权重
} City;

typedef struct GNode
{
    int Nv, Ne;
    City C[MaxN][MaxN];
} * MGraph;

MGraph CreateGraph(int N)
{
    MGraph Graph = malloc(sizeof(struct GNode));
    Graph->Nv = N;
    for (int i = 0; i < Graph->Nv; i++)
    {
        for (int j = 0; j < Graph->Nv; j++)
        {
            Graph->C[i][j].length = Graph->C[i][j].price = MaxN;
            //不排除会有免费高速公路的情况2333
        }
    }
    return Graph;
}

void InsertEdge(MGraph Graph, int v1, int v2, int length, int price)
{
    Graph->C[v1][v2].length = length;
    Graph->C[v1][v2].price = price;
 
    Graph->C[v2][v1].length = length; // 无向图
    Graph->C[v2][v1].price = price; 
}

int FindMin(MGraph Graph, int dist[], int collected[]) //正常返回最小的dist下标，反之返回-1
{
    int min = MaxN, minindex = -1;
    for (int i = 0; i < Graph->Nv; i++)
    {
        if (dist[i] < min && !collected[i])
        {
            min = dist[i];
            minindex = i;
        }
    }
    return minindex;
}

void Dijkstra(MGraph Graph, int S, int D)
{
    int dist[MaxN], price[MaxN], collected[MaxN]; //不需要记录路径
    for (int i = 0; i < Graph->Nv; i++) // 初始化
    {
        dist[i] = Graph->C[S][i].length; //<S, i>之间有公路连接
        collected[i] = 0;
        price[i] = Graph->C[S][i].price;
    }
    dist[S] = 0; // 起点
    price[S] = 0;
    collected[S] = 1; // 将起点先收入集合
    /* 1. 由于可能存在多条路径前往终点的情况，且每条路径长度相同的情况下可能价格不同；
       2. 首先仅考虑最短路径，当最短路径相同时，考虑总价最低，依次记录每个点的最短路径dist、price；*/
    while (1)
    {
        int V = FindMin(Graph, dist, collected); // V为未被收录顶点中dist最小者
        if (V == D) // 结束条件：当收录的结点为终点时
        {
            break;
        }
        collected[V] = 1; // 收录V
        //结论：当V被收录时，所有路径能到V的路径点都已经被访问过了，若非如此，dist最小的不会是V
        for (int W = 0; W < Graph->Nv; W++) // 对于V的每个邻接点
        {
            if (!collected[W] && Graph->C[V][W].length < MaxN) // 若W未收录且<V, W>存在路径
            { 
                // 不存在负边的情况
                int newlength = dist[V] + Graph->C[V][W].length;
                int newprice = price[V] + Graph->C[V][W].price;
                if (newlength < dist[W] || //若收录V使得dist[W]变小
                (newlength == dist[W] && newprice < price[W])) //若dist[W]不变则使price[W]变小
                // dist、price初始值均为最大
                {
                    dist[W] = newlength; // 更新dist和price
                    price[W] = newprice;
                }
            }
        }
    }
    //由于题目保证解存在，直接输出即可
    printf("%d %d\n", dist[D], price[D]);
}

void ReadGraph(MGraph Graph) //读入边
{
    int v1, v2, length, price;
    for (int i = 0; i < Graph->Ne; i++)
    {
        scanf("%d %d %d %d", &v1, &v2, &length, &price);
        InsertEdge(Graph, v1, v2, length, price);
    }
}

int main()
{
    int N, S, D;
    scanf("%d", &N);
    MGraph Graph = CreateGraph(N);
    scanf("%d", &Graph->Ne);
    scanf("%d %d", &S, &D);
    ReadGraph(Graph);
    Dijkstra(Graph, S, D);
    return 0;
}