// 统计工龄，即为桶排序

#include <stdlib.h>
#include <stdio.h>

void Bucket(int A[], int N)
{
    int age;
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &age);
        A[age]++;
    }
}

void Print(int A[])
{
    for (int i = 0; i < 51; i++)
    {
        if (A[i])
        {
            printf("%d:%d\n", i, A[i]);
        }
    }
}

int main()
{
    int A[51] = {0}, N;
    scanf("%d", &N);
    Bucket(A, N);
    Print(A);
    return 0;
}