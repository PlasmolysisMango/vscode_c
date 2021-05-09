#include <stdio.h>
#include <stdlib.h>

#define MAXN 10

typedef struct TreeNode Tree;
struct TreeNode
{
    int Data;
    int Left;
    int Right;
};

typedef struct QueueNode *Queue;
struct Node
{
    Tree Element;
    struct Node *Link;
};
struct QueueNode
{
    struct Node *front;
    struct Node *rear;
};

Queue CreateQ()
{
    Queue Q = (Queue)malloc(sizeof(struct QueueNode));
    Q->front = Q->rear = NULL;
    return Q;
}

void AddQ(Tree T, Queue Q)
{
    struct Node *newnode = (struct Node *)malloc(sizeof(struct Node));
    newnode->Element = T;
    newnode->Link = NULL;
    if (Q->front)
    {
        Q->rear->Link = newnode;
        Q->rear = newnode;
    }
    else
    {
        Q->front = Q->rear = newnode;
    }
}

Tree DeleteQ(Queue Q)
{
    struct Node *tmpnode = Q->front;
    Tree T = tmpnode->Element;
    if (Q->front != Q->rear)
    { 
        Q->front = tmpnode->Link;
    }
    else
    {
        Q->front = Q->rear = NULL;
    }
    free(tmpnode);
    return T;
}

int ReadTree(Tree T[])
{
    int N, R = 0;
    char cleft, cright;
    scanf("%d", &N); //避免写%d\n，这会导致后面必须跟一个非空字符才能继续线程。
    for (int i = 0; i < N; i++)
    {
        // printf("%d", i);
        R += i;
        T[i].Data = i;
        scanf("\n%c %c", &cleft, &cright);
        if (cleft != '-')
        {
            T[i].Left = cleft - '0';
            R -= T[i].Left;
        }
        else
        {
            T[i].Left = -1;
        }
        if (cright != '-')
        {
            T[i].Right = cright - '0';
            R -= T[i].Right;
        }
        else
        {
            T[i].Right = -1;
        }
    }
    if (!N)
    {
        return -1;
    }
    else
    {
        return R;
    }
}

void PrintLeaves(Tree T[], int R)
{
    if (R == -1)
    {
        return;
    }
    Queue Q = CreateQ();
    Tree tmptree;
    int flag = 0;
    AddQ(T[R], Q);
    while (Q->front)
    {
        tmptree = DeleteQ(Q);
        if (tmptree.Left == -1 && tmptree.Right == -1)
        {
            if (!flag)
            {
                flag = 1;
            }
            else
            {
                printf(" ");
            }
            printf("%d", tmptree.Data);
        }
        if (tmptree.Left != -1)
        {
            AddQ(T[tmptree.Left], Q);
        }
        if (tmptree.Right != -1)
        {
            AddQ(T[tmptree.Right], Q);
        }
    }
    free(Q);
}

int main()
{
    Tree T[MAXN];
    int R = ReadTree(T);
    PrintLeaves(T, R);
    return 0;
}
