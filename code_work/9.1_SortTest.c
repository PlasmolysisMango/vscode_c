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
void QuickSort_Mine(); // 自己实现
void QuickSort_Machine(); // 库函数
void RadixSort(); // 基数排序

/* 提前定义函数结束 */

int main()
{
    Read();
    // BubbleSort();
    // InsertSort();
    // ShellSort();
    // HeapSort();
    // MergeSort1();
    // MergeSort2();
    // QuickSort_Mine();
    // QuickSort_Machine();
    RadixSort();
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

// 快速排序（自实现）
void Swap(ElementType *a, ElementType *b) // 交换a、b实参的值
{
    ElementType tmp = *a;
    *a = *b;
    *b = tmp;
}

void _InSort(int Left, int Right) // 直接插入排序
{
    int P, i;
    ElementType tmp;
    for (P = Left + 1; P <= Right; P++) // [Left, P-1]序列为有序
    {
        tmp = A[P]; // 取出未排序序列中第一个元素
        for (i = P; A[i - 1] > tmp && i > Left; i--) // 从有序序列右边开始，如果比待排元素大，则右移
        {
            A[i] = A[i - 1];
        }
        A[i] = tmp; // 跳出位置为0或者待排元素小于等于某元素的时候
    }
}

int Median3(int Left, int Right) // 传入序列左右下标（包含），从头、中、尾选出合适基准并排列好
{
    int Center = (Left + Right) / 2;
    if (A[Left] > A[Center])
    {
        Swap(&A[Left], &A[Center]);
    }
    if (A[Center] > A[Right])
    {
        Swap(&A[Center], &A[Right]);
    }
    if (A[Left] > A[Center])
    {
        Swap(&A[Left], &A[Center]);
    }
    // 最终A[Left] <= A[Center] <= A[Right]，事实上是一次简单的冒泡排序
    Swap(&A[Center], &A[Right - 1]); // 将基准存放在Right - 1位置，最终快排只需要考虑[Left + 1, Right - 2]
    return A[Right - 1];
}

void _QSort(int Left, int Right) // 快速排序主递归函数，初始值(0, N-1)
{
    int CutOff = 100; // 当序列长度小于此值时采用直接插入排序
    if (Right - Left >= CutOff)
    {
        int Pivot = Median3(Left, Right);
        int i = Left, j = Right - 1; // 初始指针
        while (1)
        {
            while (A[++i] < Pivot)
                ;
            while (A[--j] > Pivot)
                ;
            if (i < j)
            {
                Swap(&A[i], &A[j]);
            }
            else
            {
                break;
            }
        }
        Swap(&A[i], &A[Right - 1]); // 将基准直接放到最终位置
        _QSort(Left, i - 1);
        _QSort(i + 1, Right);
    }
    else
    {
        _InSort(Left, Right);
    }
}

void QuickSort_Mine() // 统一接口
{
    _QSort(0, N - 1);
}

// 快速排序（调用库函数）
int compar(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b); // a < b则返回负整数
}

void QuickSort_Machine()
{
    qsort(A, N, sizeof(int), compar);
}

// 基数排序，数字规模按32位长整型计
#define MaxDigit 10 // 最大位数
#define Radix 10 // 基数

typedef struct RNode
{
    long long Key;
    struct RNode *Next;
} * PtrToRNode; // 桶内元素结点

typedef struct BNode
{
    PtrToRNode head, tail;
} Bucket[Radix]; // 桶结构

int GetDigit(long long X, int D) // 返回相应位数的数字，X为待提取数字，D为位数（最次位个位=1）
{
    int di = 0;
    for (int i = 1; i <= D; i++)
    {
        di = X % Radix;
        X /= Radix;
    }
    return di;
}

void RadixSort()
{
    // 针对有负数的情况，预处理数据
    int min = 0;
    for (int i = 0; i < N; i++)
    {
        if (A[i] < min)
        {
            min = A[i]; // 找到最小的负数，若均非负，则为0
        }
    }
    PtrToRNode List = NULL, tmp;
    // 初次收录
    for (int i = 0; i < N; i++) // 逆序收录
    {
        tmp = malloc(sizeof(struct RNode));
        tmp->Key = (long long)A[i] - min; // 所有数据减去最小负数，从而非负化。（右边必须先转换格式，否则int可能溢出）
        tmp->Next = List;
        List = tmp;
    }
    Bucket B;
    for (int i = 0; i < Radix; i++)
    {
        B[i].head = B[i].tail = NULL; // 初始化桶
    }
    PtrToRNode p;
    int di;
    for (int D = 1; D <= MaxDigit; D++) // 次位优先，对每一位
    {
        p = List;
        // 分配过程
        while (p) 
        {
            di = GetDigit(p->Key, D);
            tmp = p;
            p = p->Next;
            tmp->Next = NULL;
            if (!B[di].head) // 无头结点的情况
            {
                B[di].head = B[di].tail = tmp;
            }
            else // 已有头结点，则插入表尾
            {
                B[di].tail->Next = tmp;
                B[di].tail = tmp;
            }
        }
        // 收集过程
        List = NULL;
        for (di = Radix - 1; di >= 0; di--)
        {
            if (B[di].head) // 如果桶非空
            {
                B[di].tail->Next = List;
                List = B[di].head;
                B[di].head = B[di].tail = NULL;
            }
        }
    }
    // 排序完成后导入A[]
    for (int i = 0; i < N; i++)
    {
        tmp = List;
        A[i] = List->Key + min; // 恢复原数据
        List = List->Next;
        free(tmp); // 释放空间
    }
}
