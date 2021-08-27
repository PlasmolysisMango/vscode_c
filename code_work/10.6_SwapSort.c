// 限定操作为 Swap(0, *)
// 即为统计独立的环及元素个数，每一个独立的环（K个元素）若包含0，则需要K-1次即可消除；若不包含0，则需要K+1次才可以消除

#include <stdlib.h>
#include <stdio.h>

#define MaxN 100000

int A[MaxN], N;

void Read()
{
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &A[i]);
    }
}

void Count()
{
    int TCount = 0;
    for (int i = 0; i < N; i++)
    {
        if (A[i] != i) // 即为独立的环开始
        {
            int count = 1;
            int j = i;
            while (A[j] != i)
            {
                count++;
                int next = A[j];
                A[j] = j;
                j = next;
            }
            A[j] = j;
            if (i == 0)
            {
                TCount += count - 1;
            }
            else
            {
                TCount += count + 1;
            }
        }
    }
    printf("%d\n", TCount);
}

int main()
{
    Read();
    Count();
    return 0;
}