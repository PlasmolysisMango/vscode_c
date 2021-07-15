// 未验证
// 思路： I操作即为建立集合；C操作即为判断两个元素是否属于同一集合；如果所有元素都在一个集合，输出全部连接，否则输出已有的集合数量。
#include <stdio.h>
#include <stdlib.h>

#define MaxSize 10000

typedef int ComputerType;
typedef struct 
{
    ComputerType Data;
    int Parent;
} ElementType;

typedef struct SetType *Set;
struct SetType
{
    ElementType *Elements;
    int Size;
};

Set CreateSet()
{
    Set S = malloc(sizeof(struct SetType));
    S->Elements = malloc(MaxSize * sizeof(ElementType));
    S->Size = -1;
    return S;
}

int FindRoot(Set S, ComputerType X)
{
    int i;
    for (i = 0; i <= S->Size; i++)
    {
        if (X == S->Elements[i].Data)
        {
            break;
        }
    }
    if (i > S->Size)
    {
        return -1;
    }
    while (S->Elements[i].Parent >= 0)
    {
        i = S->Elements[i].Parent;
    }
    return i;
}

void InsertConnection(Set S, ComputerType A, ComputerType B)
{
    int IndexA, IndexB;
    IndexA = FindRoot(S, A);
    IndexB = FindRoot(S, B);
    if (IndexA < 0 && IndexB < 0)
    {
        S->Elements[++S->Size].Data = A;
        S->Elements[S->Size].Parent = -2;
        S->Elements[++S->Size].Data = B;
        S->Elements[S->Size].Parent = S->Size - 1;
    }
    else if (IndexA >= 0 && IndexB >= 0)
    {
        if (IndexA != IndexB)
        {
            if (S->Elements[IndexA].Parent > S->Elements[IndexB].Parent)
            {
                S->Elements[IndexB].Parent += S->Elements[IndexA].Parent;
                S->Elements[IndexA].Parent = IndexB;
            }
            else
            {
                S->Elements[IndexA].Parent += S->Elements[IndexB].Parent;
                S->Elements[IndexB].Parent = IndexA;
            }
        }
    }
    else if (IndexA >= 0)
    {
        S->Elements[++S->Size].Data = B;
        S->Elements[S->Size].Parent = IndexA;
        S->Elements[IndexA].Parent--;
    }
    else if (IndexB >= 0)
    {
        S->Elements[++S->Size].Data = A;
        S->Elements[S->Size].Parent = IndexB;
        S->Elements[IndexB].Parent--;
    }
    return;
}

int Check(Set S, ComputerType A, ComputerType B)
{
    int IndexA, IndexB;
    IndexA = FindRoot(S, A);
    IndexB = FindRoot(S, B);
    if (IndexA < 0 || IndexB < 0)
    {
        return 0;
    }
    else if (IndexA == IndexB)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int ConnectNum(Set S, int N)
{
    int Count = 0;
    for (int i = 0; i <= S->Size; i++)
    {
        if (S->Elements[i].Parent < 0)
        {
            Count++;
        }
    }
    Count += (N - S->Size - 1);
    return Count;
}

int main()
{
    int N;
    char C;
    ComputerType A, B;
    Set S = CreateSet();
    scanf("%d", &N);
    while (1)
    {
        scanf("\n%c", &C);
        if (C == 'I')
        {
            scanf("%d %d", &A, &B);
            InsertConnection(S, A, B);
        }
        else if (C == 'C')
        {
            scanf("%d %d", &A, &B);
            if (Check(S, A, B))
            {
                printf("yes\n");
            }
            else
            {
                printf("no\n");
            }
        }
        else if (C == 'S')
        {
            int Count = ConnectNum(S, N);
            if (Count == 1)
            {
                printf("The network is connected.\n");
            }
            else
            {
                printf("There are %d components.\n", Count);
            }
            break;
        }
    }
    return 0;
}
