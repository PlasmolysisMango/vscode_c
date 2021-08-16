// 本题用于测试各种排序算法
// 所有排序采用统一接口：ElementType A[], int N
// 结果统一采取从小到大

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MaxN 100001

typedef int ElementType;

ElementType A[MaxN];
int N;

/* 通用输入输出函数定义开始 */
void Read()
{
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &A[i]);
    }
}

void Print()
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
        printf("%d", A[i]);
    }
}
/* 通用输入输出函数定义结束 */

/* 提前定义函数开始 */

void BubbleSort();
void InsertSort();
void ShellSort();
void HeapSort();
void MergeSort1(); // 递归 
void MergeSort2(); // 非递归

/* 提前定义函数结束 */

int main()
{
    Read();
    // BubbleSort();
    // InsertSort();
    // ShellSort();
    // HeapSort();
    // MergeSort1();
    MergeSort2();
    Print();
    return 0;
}

// 冒泡排序
void BubbleSort()
{
    for (int i = N - 1; i > 0; i--) //外循环N-1次
    {
        int flag = 0;
        for (int j = 0; j < i; j++)
        {
            if (A[j] > A[j + 1])
            {
                ElementType tmp = A[j];
                A[j] = A[j + 1];
                A[j + 1] = tmp;
                flag = 1;
            }
        }
        if (!flag) //全程无交换，说明序列已有序
        {
            break;
        }
    }
}

// 插入排序
void InsertSort()
{
    int P, i;
    ElementType tmp;
    for (P = 1; P < N; P++) // [0, P-1]序列为有序
    {
        tmp = A[P]; // 取出未排序序列中第一个元素
        for (i = P; A[i - 1] > tmp && i > 0; i--) // 从有序序列右边开始，如果比待排元素大，则右移
        {
            A[i] = A[i - 1];
        }
        A[i] = tmp; // 跳出位置为0或者待排元素小于等于某元素的时候
    }
}

// 希尔排序
void ShellSort()
{
    int Sedgewick[] = {929, 505, 209, 109, 41, 19, 5, 1, 0}; // Sedgewick序列
    // int Hibberd = 2 ^ k - 1; // Hibberd序列

    int Si, D, P, i;
    ElementType tmp;

    for ( Si=0; Sedgewick[Si]>=N; Si++ ) 
         ; /* 初始的增量Sedgewick[Si]不能超过待排序列长度 */

    for (D = Sedgewick[Si]; D > 0; D = Sedgewick[++Si]) // Sedgewick序列
    // for (int Hi = log2(N + 1); Hi > 0; Hi--) // Hibberd序列
    {
        // D = pow(2, Hi) - 1; // Hibberd序列
        for (P = D; P < N; P++) // 对每隔D个元素进行排序, [P-N*D, P-D, D]序列为有序
        {
            tmp = A[P]; //取出未排序序列的第一个元素
            for (i = P; i >= D && A[i - D] > tmp; i -= D) // i >= D 应放在最前面，防止数组越界
            {
                A[i] = A[i - D];
            }
            A[i] = tmp;
        }
    }
}

// 堆排序
void PercDown(int p, int Size) // 从下标P开始下滤，调整为最大堆
{
    ElementType tmp = A[p];
    int c;
    for (; p * 2 + 1 < Size; p = c)
    {
        c = p * 2 + 1;
        if (c != Size - 1 && A[c + 1] > A[c])
        {
            c++;
        }
        if (A[c] > tmp)
        {
            A[p] = A[c];
        }
        else
        {
            break;
        }
    }
    A[p] = tmp;
}

void HeapSort()
{
    for (int i = (N - 2) / 2; i >= 0; i--)
    {
        PercDown(i, N); // 将数组调整为最大堆
    }
    ElementType tmp;
    for (int i = N - 1; i > 0; i--) // 从N-1元素开始
    {
        tmp = A[0];
        A[0] = A[i];
        A[i] = tmp;
        PercDown(0, i);
    }
}

// 归并排序（递归）
void Merge(ElementType TmpA[], int Left, int Right, int RightEnd) // 将A[]中的两个相邻有序序列归并到原来的位置
{
    int LeftEnd = Right - 1;
    int Num = RightEnd - Left + 1;
    int TmpIndex = Left;
    while (Left <= LeftEnd && Right <= RightEnd)
    {
        if (A[Left] <= A[Right])
        {
            TmpA[TmpIndex++] = A[Left++];
        }
        else
        {
            TmpA[TmpIndex++] = A[Right++];
        }
    }
    while (Left <= LeftEnd)
    {
        TmpA[TmpIndex++] = A[Left++];
    }
    while (Right <= RightEnd)
    {
        TmpA[TmpIndex++] = A[Right++];
    }
    while (Num--)
    {
        A[RightEnd] = TmpA[RightEnd];
        RightEnd--;
    }
}

void MSort(ElementType TmpA[], int Left, int RightEnd) // 递归主函数，初始值（TmpA, 0, N-1）
{
    int Center = (Left + RightEnd) / 2;
    if (Left < RightEnd)
    {
        MSort(TmpA, Left, Center);
        MSort(TmpA, Center + 1, RightEnd);
        Merge(TmpA, Left, Center + 1, RightEnd);
    }
}

void MergeSort1()
{
    ElementType *TmpA = malloc(N * sizeof(ElementType)); // 动态分配空间
    if (!TmpA)
    {
        printf("空间不足！");
        return;
    }
    MSort(TmpA, 0, N - 1);
    free(TmpA);
}

// 归并排序（非递归）
void Merge2(ElementType TmpA[], ElementType TmpB[], int Left, int Right, int RightEnd) // 将A[]中的两个相邻有序序列归并到B[]
{
    int LeftEnd = Right - 1;
    int TmpIndex = Left;
    while (Left <= LeftEnd && Right <= RightEnd)
    {
        if (TmpA[Left] <= TmpA[Right])
        {
            TmpB[TmpIndex++] = TmpA[Left++];
        }
        else
        {
            TmpB[TmpIndex++] = TmpA[Right++];
        }
    }
    while (Left <= LeftEnd)
    {
        TmpB[TmpIndex++] = TmpA[Left++];
    }
    while (Right <= RightEnd)
    {
        TmpB[TmpIndex++] = TmpA[Right++];
    }
}

void MergePass(ElementType TmpA[], ElementType TmpB[], int length) // 将A归并至B，有序子列长度为length
{
    int i;
    for (i = 0; i <= N - 2 * length; i += 2 * length)
    {
        Merge2(TmpA, TmpB, i, i + length, i + 2 * length - 1);
    }
    if (i + length < N) // 若最终剩余超过一个有序子列
    {
        Merge2(TmpA, TmpB, i, i + length, N - 1);
    }
    else // 若最终升序不到一个有序子列
    {
        for (; i < N; i++)
        {
            TmpB[i] = TmpA[i];
        }
    }
}

void MergeSort2()
{
    ElementType *TmpA = malloc(N * sizeof(ElementType)); // 动态分配空间
    if (!TmpA)
    {
        printf("空间不足！");
        return;
    }
    int length = 1;
    while (length < N)
    {
        MergePass(A, TmpA, length);
        length *= 2;
        MergePass(TmpA, A, length); // 执行两次，确保最终导回到A[]
        length *= 2;
    }
    free(TmpA);
}