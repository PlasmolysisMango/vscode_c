/* 邻接表存储 - 无权图的单源最短路算法 */
#include <stdio.h>
#include <stdlib.h>

#define MaxN 100
#define INF 65535

typedef int WeightType;
typedef int VertexType;

typedef struct LNode
{

    WeightType Weight;
    VertexType V;
    struct LNode *Next;
} * PtrToLNode;

typedef PtrToLNode GList[MaxN];

typedef struct GNode
{
    int Nv, Ne;
    GList G;
} * LGraph;

typedef struct QNode
{
    VertexType Data[MaxN];
    int front, rear;
} * Queue;

typedef struct ENode
{
    VertexType v1, v2;
    WeightType Weight;
} * Edge;

PtrToLNode NewNode()
{
    PtrToLNode N = malloc(sizeof(struct LNode));
    N->Weight = INF;
    N->Next = NULL;
    return N;
}

LGraph CreateGraph(int N)
{
    LGraph Graph = malloc(sizeof(struct GNode));
    Graph->Nv = N;
    Graph->Ne = 0;
    for (int i = 0; i < Graph->Nv; i++)
    {
        Graph->G[i] = NULL;
    }
        return Graph;
}

Edge CreateEdge(VertexType i, VertexType j, WeightType weight)
{
    Edge E = malloc(sizeof(struct ENode));
    E->v1 = i;
    E->v2 = j;
    E->Weight = weight;
    return E;
}

void InsertEdge(LGraph Graph, Edge E)
{
    PtrToLNode newnode = NewNode();
    newnode->V = E->v2;
    newnode->Next = Graph->G[E->v1];
    Graph->G[E->v1] = newnode;

    newnode = NewNode(); // 若为无向图
    newnode->V = E->v1;
    newnode->Next = Graph->G[E->v2];
    Graph->G[E->v2] = newnode;
}

Queue CreateQueue()
{
    Queue Q = malloc(sizeof(struct QNode));
    Q->front = Q->rear = -1;
    return Q;
}

void EnQueue(Queue Q, VertexType V)
{
    Q->rear = (Q->rear + 1) % MaxN;
    Q->Data[Q->rear] = V;
}

VertexType DeQueue(Queue Q)
{
    Q->front = (Q->front + 1) % MaxN;
    return Q->Data[Q->front];
}

void Unweight(LGraph Graph, int dist[], int path[], VertexType S)
{
    Queue Q = CreateQueue();
    dist[0] = 0; 
    EnQueue(Q, S);
    while (Q->front != Q->rear)
    {
        VertexType V = DeQueue(Q);
        PtrToLNode p = Graph->G[V];
        while (p)
        {
            if (dist[p->V] == -1) // 若p未被访问过
            {
                dist[p->V] = dist[V] + 1;
                path[p->V] = V;
                EnQueue(Q, p->V);
            }
            p = p->Next;
        }
    }
}

