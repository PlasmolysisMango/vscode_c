#include <stdio.h>
#include <stdlib.h>

/*思路：利用堆栈，避免对链表的重复修改。但此法是在整理链表前直接输出结果的，
如果给出的链表实际结点小于N，则会导致结果出错。*/

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

Address SearchPush(Address A, List L, Stack S)
{
    while (L->Link)
    {
        if (A == L->Link->Addr)
        {
            List tmpnode;
            Address Next;
            tmpnode = L->Link;
            Next = tmpnode->NextAddr;
            L->Link = tmpnode->Link;
            tmpnode->Link = S->Link;
            S->Link = tmpnode;
            return Next;
        }
        L = L->Link;
    }
    return -1;
}

List Search(Address A, List L)
{
    while (L->Link)
    {
        if (A == L->Link->Addr)
        {
            List p;
            p = L->Link;
            L->Link = p->Link;
            return p;
        }
        L = L->Link;
    }
    return NULL;
}

Stack Pop(Stack S)
{
    Stack p;
    p = S->Link;
    S->Link = p->Link;
    return p;
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
        // newnode->NextAddr = -1;
        Rear->Link = newnode;
        // Rear->NextAddr = newnode->Addr;
        Rear = newnode;
    }
    return L;
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
    L = ReadList(N);
    S = CreateStack();
    while (FAddr != -1)
    {
        for (int i = 0; i < K; i++, j++)
        {
            if (!L->Link)
            {
                break;
            }
            if (j >= N / K * K)
            {
                tmpnode = Search(FAddr, L);
                FAddr = tmpnode->NextAddr;
                Rear->Link = tmpnode;
                Rear->NextAddr = tmpnode->Addr;
                Rear = tmpnode;
                Rear->Link = NULL;
                Rear->NextAddr = -1;
            }
            else
            {
                FAddr = SearchPush(FAddr, L, S);
            }    
        }
        while (S->Link)
        {
            tmpnode = Pop(S);
            Rear->Link = tmpnode;
            Rear->NextAddr = tmpnode->Addr;
            Rear = tmpnode;
            Rear->Link = NULL;
            Rear->NextAddr = -1;
        }
    }
    PrintList(R);
}