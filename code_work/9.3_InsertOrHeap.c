// 判断题设给出的序列是插入排序还是堆排序，并在此基础上继续进行一步
// 由于堆排序建立的是最大堆，一定不会出现顺序递增的情况，因此只需要判断插入排序即可。

#include <stdio.h>
#include <stdlib.h>

#define MaxN 100

int A[MaxN], B[MaxN], N;

void Read()
{
    scanf("%d", &N);
    for (int i = 0; i < 2 * N; i++)
    {
        if (i < N)
        {
            scanf("%d", &A[i]);
        }
        else
        {
            scanf("%d", &B[i - N]);
        }
    }
}

void Print(int X[])
{
    int flag = 0;
    for (int i = 0; i < N; i++)
    {
        if (!flag)
        {
            flag = 1;
        }
        else
        {
            printf(" ");
        }
        printf("%d", X[i]);
    }
    printf("\n");
}

int Insert() // 判断序列是否是插入排序，若是则执行下一步并返回1，否则返回0
{
    int i, j;
    for (i = 0; i < N - 1; i++)
    {
        if (B[i] > B[i + 1]) // 若有异常点，即前>后
        {
            break;
        }
    }
    for (j = i + 1; j < N; j++)
    {
        if (A[j] != B[j]) // 若后续元素与原序列不相等，则不是插入排序
        {
            return 0;
        }
    }
    int tmp = B[i + 1];
    for (j = i + 1; j > 0 && B[j - 1] > tmp; j--)
    {
        B[j] = B[j - 1];
    }
    B[j] = tmp;
    return 1;
}

void PercDown(int p, int Size) // 从位置p开始下滤B[]
{
    int c, tmp = B[p];
    for (; p * 2 + 1 < Size; p = c)
    {
        c = p * 2 + 1;
        if (c != Size - 1 && B[c + 1] > B[c])
        {
            c++;
        }
        if (B[c] > tmp)
        {
            B[p] = B[c];
        }
        else
        {
            break;
        }
    }
    B[p] = tmp;
}

void Heap()
{
    int max = B[0], i;
    for (i = N - 1; i > 0; i--)
    {
        if (B[i] < max) // 即异常点，小于max
        {
            break;
        }
    }
    B[0] = B[i];
    B[i] = max;
    PercDown(0, i);
}

int main()
{
    Read();
    if (!Insert())
    {
        printf("Heap Sort\n");
        Heap();
    }
    else
    {
        printf("Insertion Sort\n");
    }
    Print(B);
    return 0;
}