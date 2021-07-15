#include <stdio.h>
#include <stdlib.h>

#define MaxN 1000
#define MaxE MaxN * 33

typedef struct ANode
{
    int V;
    struct ANode *Next;
} *AdjNode;

AdjNode GList[MaxN]; //全局变量构造图虽然便利，但调试不方便。
int Nv, Ne;

void CreateGraph()
{
    for (int i = 0; i < Nv; i++)
    {
        GList[i] = malloc(sizeof(struct ANode));
        GList[i]->Next = NULL;
    }
}

void InsertEdge(int i, int j)
{
    AdjNode newnode = malloc(sizeof(struct ANode));
    newnode->V = j;
    newnode->Next = GList[i]->Next;
    GList[i]->Next = newnode;

    newnode = malloc(sizeof(struct ANode));
    newnode->V = i;
    newnode->Next = GList[j]->Next;
    GList[j]->Next = newnode;
}

int Queue[MaxN];
int rear, front;
int visited[MaxN];

void InitQueue()
{
    rear = front = -1;
}

void AddQ(int v)
{
    rear = (rear + 1) % MaxN;
    Queue[rear] = v;
}

int DeleteQ()
{
    front = (front + 1) % MaxN;
    return Queue[front];
}

void Initvisit()
{
    for (int i = 0; i < Nv; i++)
    {
        visited[i] = 0;
    }
}

int BFS(int v)
{
    InitQueue();
    Initvisit();
    AddQ(v);
    int count = 1, end = v, tempend = 0, level = 1;
    visited[v] = 1;
    while (rear != front)
    {
        int w = DeleteQ();
        AdjNode p = GList[w];
        while(p->Next)
        {
            if (!visited[p->Next->V]) //访问某些结点必定经过访问过的结点，因此条件不能写到一起
            {
                tempend = p->Next->V;
                AddQ(tempend);
                visited[tempend] = 1;
                count++;
            }
            p = p->Next;
        }
        if (w == end)
        {
            level++;
            end = tempend;
        }
        if (level > 6)
        {
            break;
        }
    }
    return count;
}

int main()
{
    scanf("%d %d", &Nv, &Ne);
    CreateGraph();
    while (Ne--)
    {
        int i, j;
        scanf("%d %d", &i, &j);
        InsertEdge(i - 1, j - 1);
    }
    for (int i = 0; i < Nv; i++)
    {
        int count = BFS(i);
        printf("%d: %.2f%%\n", i + 1, (double)count / Nv * 100);
    }
}


