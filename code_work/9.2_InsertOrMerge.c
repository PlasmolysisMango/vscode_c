// 判断题设给出的序列是插入排序还是归并排序，并在此基础上继续进行一步
// 考虑异常点（前>后）只可能发生在插入排序的有序序列末尾和归并排序的子列末尾，在这之后区分两种排序只能通过后续序列是否与原序列相同
#include <stdio.h>
#include <stdlib.h>

int *A, *B, N;
void Read();
int Insert();
void Merge(int MaxLength);
void Print();

int main()
{
    scanf("%d", &N);
    A = malloc(N * sizeof(int));
    B = malloc(N * sizeof(int));
    Read();
    int judge = Insert();
    if (judge >= 0) // 是插入排序
    {
        printf("Insertion Sort\n");
    }
    else
    {
        printf("Merge Sort\n");
        Merge(-judge + 1);
    }
    Print(B);
    return 0;
}

void Read()
{
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

void Print(int *x)
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
        printf("%d", x[i]);
    }
    printf("\n");
}

int JudgeOrder(int Left, int Right) // 判断B[Left, Right]是否有序，有序则返回-1，无序返回异常点下标
{
    for (; Left < Right; Left++)
    {
        if (B[Left] > B[Left + 1])
        {
            return Left;
        }
    }
    return -1;
}

int Insert() // 判断序列是否是插入排序，若是则执行下一步，并返回异常点下标; 非插入排序则返回负数
{
    int judge = JudgeOrder(0, N - 1); // 返回B序列中有序序列的最后一个元素下标
    for (int i = judge + 1; i < N; i++)
    {
        if (A[i] != B[i]) // 若后续元素与原序列不相等，则不是插入排序
        {
            judge = -judge;
            break;
        }
    }
    if (judge > 0)
    {
        int tmp = B[judge + 1], i;
        for (i = judge + 1; i > 0 && B[i - 1] > tmp; i--)
        {
            B[i] = B[i - 1];
        }
        B[i] = tmp;
    }
    return judge;
}

void _SingleMerge(int Left, int Right, int RightEnd) // 将B[]中相邻的两个序列归并至A[]
{
    int tmp = Left, LeftEnd = Right - 1;
    while (Left <= LeftEnd && Right <= RightEnd)
    {
        if (B[Left] < B[Right])
        {
            A[tmp++] = B[Left++];
        }
        else
        {
            A[tmp++] = B[Right++];
        } 
    }
    while (Left <= LeftEnd)
    {
        A[tmp++] = B[Left++];
    }
    while (Right <= RightEnd)
    {
        A[tmp++] = B[Right++];
    }
}

void Merge(int MaxLength) // 由于先判定插入排序，返回异常点的下标即为归并排序目前可能的最大区间长度
{
    int i, j, judge;
    while (1)
    {
        judge = 1; // 判断是否需要减半区间
        for (i = 0; i < N; i += MaxLength)
        {
            if (i <= N - MaxLength)
            {
                j = i + MaxLength - 1;
            }
            else
            {
                j = N - 1;
            }
            if (JudgeOrder(i, j) > 0) // 即该区间无序
            {
                MaxLength /= 2;
                judge = 0;
                break;
            }
        }
        if (judge) // 若全部有序
        {
            break;
        }
    }
    // 此时按MaxLength进行一次归并即可
    for (i = 0; i < N; i += 2 * MaxLength)
    {
        if (i + 2 * MaxLength - 1 < N) // 若有完整的两个区间
        {
            _SingleMerge(i, i + MaxLength, i + 2 * MaxLength - 1);
        }
        else if (i + MaxLength < N) // 若有完整的第一个区间和不完整的第二个区间
        {
            _SingleMerge(i, i + MaxLength, N - 1);
        }
        // Print(A);
    }
    for (j = 0; j < i && j < N; j++)
    {
        B[j] = A[j];
    }
}