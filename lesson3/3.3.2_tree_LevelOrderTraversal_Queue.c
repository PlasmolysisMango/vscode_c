// 使用队列实现层级的二叉树遍历。
#include <stdio.h>
#include <stdlib.h>

#define MAXN 10

typedef char ElementType;
typedef struct TreeNode *BinTree;
struct TreeNode
{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

struct Node 
{
    BinTree Data;
    struct Node *Link;
};

typedef struct QueueNode *Queue;
struct QueueNode
{
    struct Node *front;
    struct Node *rear;
};

Queue CreateQueue()
{
    Queue Q;
    Q = (Queue)malloc(sizeof(struct QueueNode));
    Q->front = Q->rear = NULL;
    return Q;
}

void AddQ(BinTree BT, Queue Q)
{
    struct Node *newnode = (struct Node*)malloc(sizeof(struct Node));
    newnode->Data = BT;
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

BinTree DeleteQ(Queue Q)
{
    if (Q->front == Q->rear)
    {
        if (!Q->front)
        {
            return NULL;
        }
        else
        {
            BinTree B;
            B = Q->front->Data;
            free(Q->front);
            Q->front = Q->rear = NULL;
            return B;
        }
    }
    else
    {
        BinTree B;
        struct Node *tmpnode;
        B = Q->front->Data;
        tmpnode = Q->front;
        Q->front = tmpnode->Link;
        free(tmpnode);
        return B;
    }
}

BinTree ReadTree()
{
    int N, R = 0;
    BinTree A[MAXN];
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
    {
        A[i] = (BinTree)malloc(sizeof(struct TreeNode));
    }
    for (int i = 0; i < N; i++)
    {
        R += i;
        char cleft, cright;
        scanf("\n%c %c %c", &(A[i]->Data), &cleft, &cright); 
        /* scanf在%c格式下会从字符流录入转义字符、空格、回车在内的所有字符。*/
        if (cleft != '-')
        {
            int left = cleft - '0';
            A[i]->Left = A[left];
            R -= left;
        }
        else
        {
            A[i]->Left = NULL;
        }
        if (cright != '-')
        {
            int right = cright - '0';
            A[i]->Right = A[right];
            R -= right;
        }
        else
        {
            A[i]->Right = NULL;
        }
    }
    return A[R];
}

void PreOrderTraversal(BinTree BT)
{
    return;
}

void InOrderTraversal(BinTree BT)
{
    return;
}

void PostOrderTraversal(BinTree BT)
{
    return;
}

void LevelOrderTraversal(BinTree BT)
{
    if (!BT)
    {
        return;
    }
    Queue Q = CreateQueue();
    int flag = 0;
    AddQ(BT, Q);
    while (Q->front)
    {
        BT = DeleteQ(Q);
        if (!flag)
        {
            flag = 1;
        }
        else
        {
            printf(" ");
        }
        printf("%c", BT->Data);
        if (BT->Left)
        {
            AddQ(BT->Left, Q);
        }
        if (BT->Right)
        {
            AddQ(BT->Right, Q);
        }
    }
    free(Q);
    if (flag)
    {
        printf("\n");
    }
}

int main()
{
    BinTree B;
    B = ReadTree();
    LevelOrderTraversal(B);
}