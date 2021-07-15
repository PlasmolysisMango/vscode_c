#include <stdio.h>
#include <stdlib.h>

#define MaxSize 100
#define INF 10000
typedef int Vertex;
typedef int WeightType;
typedef struct GNode *PtrToGNode;
struct GNode
{
    int Nv, Ne; //顶点数以及边数
    WeightType G[MaxSize][MaxSize];
};
typedef PtrToGNode MGraph; //清晰表明MGraph由Pointer表示

typedef struct ENode *PtrToENode;
struct ENode
{
    Vertex V1, V2; //有向边<V1, V2>
    WeightType Weight; //权重, 默认为1
};
typedef PtrToENode Edge; //清晰表明Edge由Pointer表示

MGraph CreateGraph(int VertexNum)
{
    MGraph Graph = malloc(sizeof(struct GNode));
    Graph->Nv = VertexNum;
    Graph->Ne = 0;
    for (Vertex i = 0; i < VertexNum; i++)
    {
        for (Vertex j = 0; j < VertexNum; j++)
        {
            Graph->G[i][j] = INF;
        }
    }
    return Graph;
}

void InsertEdge(MGraph Graph, Edge E)
{
    // Graph->Ne++; //已经提前指定了边数，后续插入时要在外部 Ne++
    Graph->G[E->V1][E->V2] = E->Weight;
    Graph->G[E->V2][E->V1] = E->Weight; //无向图的情况，还要插入<V2, V1>
}

MGraph BuildGraph()
{
    int Nv, Ne;
    scanf("%d %d", &Nv, &Ne);
    MGraph Graph = CreateGraph(Nv);
    Graph->Ne = Ne;
    while (Ne--)
    {
        Edge E = malloc(sizeof(struct ENode));
        scanf("%d %d %d", &E->V1, &E->V2, &E->Weight);
        InsertEdge(Graph, E);
    }
    return Graph;
}

