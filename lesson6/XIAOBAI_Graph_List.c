#include <stdio.h>
#include <stdlib.h>

#define MaxVertexNum 100

typedef int WeightType;
typedef int Vertex;
// typedef int DataType; // 数据域，可省略

typedef struct AdjVNode *PtrToAdjVNode; //邻接表结点类型
struct AdjVNode
{
    Vertex AdjV; //边的出点下标
    WeightType Weight;
    PtrToAdjVNode Next;
};

typedef struct VNode
{
    PtrToAdjVNode FirstEdge;
    // DataType Data; //数据域，可省略
} AdjList[MaxVertexNum]; //邻接表类型

typedef struct LNode *PtrToLNode;
struct LNode
{
    int Nv, Ne;
    AdjList G; //邻接表
};
typedef PtrToLNode LGraph;

typedef struct ENode *PtrToENode;
struct ENode
{
    Vertex V1, V2; //有向边<V1, V2>
    WeightType Weight; //权重, 默认为1
};
typedef PtrToENode Edge; //清晰表明Edge由Pointer表示

LGraph CreateGraph(int VertexNum)
{
    LGraph Graph = malloc(sizeof(struct LNode));
    Graph->Nv = VertexNum;
    Graph->Ne = 0;
    for (Vertex i = 0; i < VertexNum; i++)
    {
        Graph->G[i].FirstEdge = NULL;
    }
    return Graph;
}

void InsertEdge(LGraph Graph, Edge E)
{
    PtrToAdjVNode NewNode = malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V2;
    NewNode->Weight = E->Weight;
    NewNode->Next = Graph->G[E->V1].FirstEdge;
    Graph->G[E->V1].FirstEdge = NewNode; //插入有向边<V1, V2>

    NewNode = malloc(sizeof(struct AdjVNode));
    NewNode->AdjV = E->V1;
    NewNode->Weight = E->Weight;
    NewNode->Next = Graph->G[E->V2].FirstEdge;
    Graph->G[E->V2].FirstEdge = NewNode; //若为无向图，还需要插入有向边<V2, V1>
}

LGraph BuildGraph()
{
    int Nv, Ne;
    scanf("%d %d", &Nv, &Ne);
    LGraph Graph = CreateGraph(Nv);
    Graph->Ne = Ne;
    while (Ne--)
    {
        Edge E = malloc(sizeof(struct ENode));
        scanf("%d %d %d", &E->V1, &E->V2, &E->Weight);
        InsertEdge(Graph, E);
    }
    return Graph;
}