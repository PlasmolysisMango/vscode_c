#include <stdio.h>
#include <stdlib.h>

#define MaxN 1000

typedef int ElementType;
typedef struct 
{
    ElementType Data;
    int Parent;
} SetType;

int Find(SetType S[], ElementType X)
{
    int i;
    for (i = 0; i < MaxN; i++)
    {
        if (S[i].Data == X)
        {
            break;
        }
    }
    if (i == MaxN)
    {
        return -MaxN - 1;
    }
    while (S[i].Parent >= 0)
    {
        i = S[i].Parent;
    }
    return i;
}

void Union(SetType S[], ElementType X1, ElementType X2)
{
    int R1, R2;
    R1 = Find(S, X1);
    R2 = Find(S, X2);
    if (R1 < -MaxN || R2 < -MaxN)
    {
        return;
    }
    if (R1 != R2)
    {
        int R = S[R1].Parent < S[R2].Parent ? R1 : R2;
        S[R1 + R2 - R].Parent = R;
    }
}

int ReadSet(SetType S[], int m) //m为数组可用的序号
{
    int N;
    scanf("%d", &N);
    scanf("%d", &S[m].Data);
    S[m].Parent = -N;
    for (int i = 1; i < N; i++)
    {
        scanf("%d", &S[i + m].Data);
        S[i + m].Parent = m;
    }
    return m + N;
}

void PrintSet(SetType S)
{
    return;
}