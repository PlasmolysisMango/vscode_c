#include <stdio.h>
#include <stdlib.h>

/*思路：利用堆栈，实现链表的倒序输出。*/

typedef struct ChainNode *Stack;
typedef struct ChainNode *List;
typedef int Address;
struct ChainNode
{
    Address Addr;
    int Data;
    Address NextAddr;
    struct ChainNode *Link;
};

Stack CreateStack()
{
    Stack S;
    S = (Stack)malloc(sizeof(struct ChainNode));
    S->Link = NULL;
    S->NextAddr = -1;
    return S;
}

void Push(Stack p, Stack S)
{
    p->Link = S->Link;
    S->Link = p;
}

Stack Pop(Stack S)
{
    Stack p;
    p = S->Link;
    S->Link = p->Link;
    return p;
}

void AppendList(List X, List *Rear)
{
    (*Rear)->Link = X;
    (*Rear)->NextAddr = X->Addr;
    (*Rear) = X;
    (*Rear)->NextAddr = -1;
}

List ReadList(int *N, Address FAddr)
{
    List L, Rear, newnode, R;
    Rear = L = (List)malloc(sizeof(struct ChainNode));
    while ((*N)--)
    {
        newnode = (List)malloc(sizeof(struct ChainNode));
        scanf("%d %d %d", &newnode->Addr, &newnode->Data, &newnode->NextAddr);
        newnode->Link = NULL;
        Rear->Link = newnode;
        Rear = newnode;
    }
    (*N)++;
    // printf("n=%d\n", *N);
    Rear = R = (List)malloc(sizeof(struct ChainNode));
    while (FAddr != -1)
    {
        List p = L;
        while (p->Link)
        {
            if (FAddr == p->Link->Addr)
            {
                newnode = p->Link;
                FAddr = newnode->NextAddr;
                p->Link = newnode->Link;
                newnode->Link = NULL;
                Rear->Link = newnode;
                Rear = newnode;
                (*N)++;
                break;
            }
            p = p->Link;
        }
    }
    free(L);
    return R;
}

void PrintList(List R)
{
    while (R->Link)
    {
        if (R->Link->NextAddr == -1)
        {
            printf("%05d %d %d\n", R->Link->Addr, R->Link->Data, R->Link->NextAddr);
        }
        else
        {
            printf("%05d %d %05d\n", R->Link->Addr, R->Link->Data, R->Link->NextAddr);
        }
        R = R->Link;
    }
}

int main()
{
    int N, K, j = 0;
    Address FAddr;
    List L;
    Stack S;
    List R, Rear, tmpnode;
    Rear = R = (List)malloc(sizeof(struct ChainNode));
    Rear->Link = NULL;
    scanf("%d %d %d", &FAddr, &N, &K);
    L = ReadList(&N, FAddr);
    S = CreateStack();
    while (j < N)
    {
        for (int i = 0; i < K && L->Link; i++, j++)
        {
            if (j >= N / K * K)
            {
                tmpnode = L->Link;
                L->Link = tmpnode->Link;
                AppendList(tmpnode, &Rear);
            }
            else
            {
                tmpnode = L->Link;
                L->Link = tmpnode->Link;
                Push(tmpnode, S);
            }
        }
        while (S->Link)
        {
            AppendList(Pop(S), &Rear);
        }
    }
    PrintList(R);
}