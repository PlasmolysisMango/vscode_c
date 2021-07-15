// 未验证
// 思路： I操作即为建立集合；C操作即为判断两个元素是否属于同一集合；如果所有元素都在一个集合，输出全部连接，否则输出已有的集合数量。
// 简化思路：直接用数组下标来映射并查集数据(X-1)，用数组存储父节点下标，再用按秩归并和路径压缩优化算法。
#include <stdio.h>
#include <stdlib.h>

#define MaxSize 10000

typedef int ComputerType;

typedef ComputerType SetType[MaxSize];

void InitSet(SetType S, int N)
{
    for (int i = 0; i < N; i++)
    {
        S[i] = -1;
    }
}

int FindRoot(SetType S, ComputerType X) //返回目标数据（需提前-1）根节点的下标。使用路径压缩。
{
    if (S[X] < 0)
    {
        return X;
    }
    else
    {
        return S[X] = FindRoot(S, S[X]);
    }
}

void InsertConnection(SetType S, ComputerType A, ComputerType B)
{
    int IndexA, IndexB;
    IndexA = FindRoot(S, A - 1);
    IndexB = FindRoot(S, B - 1);
    if (S[IndexA] > S[IndexB]) // -3 > -4 按秩归并
    {
        S[IndexB] += S[IndexA];
        S[IndexA] = IndexB;
    }
    else
    {
        S[IndexA] += S[IndexB];
        S[IndexB] = IndexA;
    }
    return;
}

int Check(SetType S, ComputerType A, ComputerType B)
{
    int IndexA, IndexB;
    IndexA = FindRoot(S, A - 1);
    IndexB = FindRoot(S, B - 1);
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

int ConnectNum(SetType S, int N)
{
    int Count = 0;
    for (int i = 0; i < N; i++)
    {
        if (S[i] < 0)
        {
            Count++;
        }
    }
    return Count;
}

int main()
{
    int N;
    char C;
    ComputerType A, B;
    SetType S;
    scanf("%d", &N);
    InitSet(S, N);
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
