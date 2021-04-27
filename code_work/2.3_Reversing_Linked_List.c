#include <stdio.h>
#include <stdlib.h>

//思路：利用堆栈，避免对链表的重复修改。

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

void SearchPush(Address A, List L, Stack S)
{
    while (L->Link)
    {
        if (A == L->Link->Addr)
        {
            List tmpnode;
            tmpnode = L->Link;
            L->Link = tmpnode->Link;
            L->NextAddr = tmpnode->NextAddr;
            tmpnode->Link = S->Link;
            tmpnode->NextAddr = S->NextAddr;
            S->Link = tmpnode;
            S->NextAddr = tmpnode->Addr;
            return;
        }
        L = L->Link;
    }
}

void PopPrint(Stack S)
{
    Stack p;
    int d;
    p = S->Link;
    S->Link = p->Link;
    d = p->Data;
    if (!p->Link)
    {
        printf("%05d %d %d\n", p->Addr, p->Data, p->NextAddr);
    }
    else
    {
        printf("%05d %d %05d\n", p->Addr, p->Data, p->NextAddr);
    }     
    free(p);
}

List ReadList(int N)
{
    List L, Rear, newnode;
    Rear = L = (List)malloc(sizeof(struct ChainNode));
    while (N--)
    {
        newnode = (List)malloc(sizeof(struct ChainNode));
        scanf("%d %d %d", &newnode->Addr, &newnode->Data, &newnode->NextAddr);
        newnode->Link = NULL;
        newnode->NextAddr = -1;
        Rear->Link = newnode;
        Rear->NextAddr = newnode->Addr;
        Rear = newnode;
    }
    return L;
}

int main()
{
    int N, K;
    Address FAddr;
    List L;
    Stack S;
    scanf("%d %d %d", &FAddr, &N, &K);
    L = ReadList(N);
    S = CreateStack();
    while (FAddr != -1)
    {
        for (int i = 0; i < K; i++)
        {
            if (!L->Link)
            {
                break;
            }
            SearchPush(FAddr, L, S);
            FAddr = S->Link->NextAddr;
        }
        while (S->Link)
        {
            PopPrint(S);
        }
    }
}


