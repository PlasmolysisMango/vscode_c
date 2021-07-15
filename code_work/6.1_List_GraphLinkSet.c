#include <stdio.h>
#include <stdlib.h>

#define MaxN 20

int Nv, Ne; //快速建立图
int G[MaxN][MaxN];
int visited[MaxN];

void BuildGraph()
{
    scanf("%d %d", &Nv, &Ne);
    int V1, V2;
    for (int i = 0; i < Ne; i++)
    {
        scanf("%d %d", &V1, &V2);
        G[V1][V2] = G[V2][V1] = 1;
    }
}

void InitVisit()
{
    for (int i = 0; i < Nv; i++)
    {
        visited[i] = 0;
    }
}

void DFS(int v) //从小到大
{
    visited[v] = 1;
    printf("%d ", v);
    for (int w = 0; w < Nv; w++)
    {
        if (!visited[w] && G[v][w])
        {
            DFS(w);
        }
    }
}

int QData[MaxN]; //快速建立循环队列
int front, rear;

void InitQueue()
{
    front = rear = -1;
}

void AddQ(int v)
{
    rear = (rear + 1) % MaxN; //rear后移入队
    QData[rear] = v;
}

int DeleteQ()
{
    front = (front + 1) % MaxN; //front后移出队
    return QData[front];
}

void BFS(int v)
{
    AddQ(v);
    visited[v] = 1;
    printf("%d ", v);
    while (front != rear) //循环队列不空
    {
        v = DeleteQ();
        for (int w = 0; w < Nv; w++)
        {
            if (!visited[w] && G[v][w])
            {
                AddQ(w);
                visited[w] = 1;
                printf("%d ", w);
            }
        }
    }
}

int main()
{
    BuildGraph();
    InitVisit();
    for (int i = 0; i < Nv; i++)
    {
        if (!visited[i])
        {
            printf("{ ");
            DFS(i);
            printf("}\n");
        }
    }
    InitVisit();
    for (int i = 0; i < Nv; i++)
    {
        if (!visited[i])
        {
            printf("{ ");
            BFS(i);
            printf("}\n");
        }
    }
}