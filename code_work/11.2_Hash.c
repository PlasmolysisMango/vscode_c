// 散列查找的应用

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MaxN 20000

// 哈希表相关定义

typedef struct HNode
{
    int TSize;
    int Data[MaxN];
} *HashTable;

int NextPrime(int N)
{
    if (N == 1)
    {
        return 2;
    }
    int p = (N % 2) ? N + 2 : N + 1, i; // 即为大于N的第一个奇数
    while (1)
    {
        for (i = (int)ceil(sqrt(p)); i > 2; i--)
        {
            if (!(p % i)) // 若p可以被i整除。即不是素数
            {
                break;
            }
        }
        if (i == 2) // 正常结束循环，即p为素数
        {
            break;
        }
        else
        {
            p += 2;
        }
    }
    return p;
}

HashTable CreateHashTable(int N)
{
    HashTable H = malloc(sizeof(struct HNode));
    H->TSize = NextPrime(N);
    for (int i = 0; i < H->TSize; i++)
    {
        H->Data[i] = -1; // 限定的输入均为正数
    }
    return H;
}

int Hash(int key, int Size)
{
    return (key % Size);
}

int Insert(HashTable H, int X) // 采用正向的平方探测
{
    int index = Hash(X, H->TSize), first_index = index;
    for (int i = 1; H->Data[index] != -1; i++) // 若该位置已有元素
    {
        index = Hash(first_index + i * i, H->TSize);
        if (index == first_index)
        {
            return -1; // 若回到最初位置，即找不到插入位置，返回-1
        }
    }
    H->Data[index] = X; // 若正常结束循环，则可以插入，返回插入的下标
    return index;
}

void ReadAndOutput(HashTable H, int N) // 读入N个数据到哈希表，并输出相应位置
{
    int X, index, flag = 0;
    while (N--)
    {
        scanf("%d", &X);
        index = Insert(H, X);
        if (!flag)
        {
            flag = 1;
        }
        else
        {
            printf(" ");
        }
        if (index == -1)
        {
            printf("-");
        }
        else
        {
            printf("%d", index);
        }
    }
}

int main()
{
    int Size, N;
    scanf("%d %d", &Size, &N);
    HashTable H = CreateHashTable(Size);
    ReadAndOutput(H, N);
    return 0;
}