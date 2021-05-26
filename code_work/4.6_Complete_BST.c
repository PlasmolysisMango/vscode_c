/* 完全二叉树的构建，思路一：事先排序，后建树；
思路二：直接线性化建树，实现排序，再重新排列二叉树 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MaxSize 10000

typedef int ElementType;
typedef struct TreeNode
{
    ElementType *Elements;
    int Size;
} *CBTree;

CBTree CreateCBTree()
{
    CBTree C = malloc(sizeof(struct TreeNode));
    C->Elements = malloc(MaxSize * sizeof(ElementType));
    C->Size = -1;
    return C;
}

int isEmpty(CBTree C)
{
    if (!C)
    {
        return 0;
    }
    else if (C->Size == -1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void BubbleSort(CBTree C)
{
    if (!C)
    {
        return;
    }
    ElementType temp;
    for (int i = 0; i < C->Size; i++)
    {
        for (int j = 0; j < C->Size - i; j++)
        {
            if (C->Elements[j] > C->Elements[j + 1])
            {
                temp = C->Elements[j];
                C->Elements[j] = C->Elements[j + 1];
                C->Elements[j + 1] = temp;
            }
        }
    }
}

CBTree ReadTree()
{
    CBTree C = CreateCBTree();
    int N;
    scanf("%d", &N);
    while (N--)
    {
        scanf("%d", &C->Elements[++C->Size]);
    }
    return C;
}

int LeftSize(int Lenth)
{
    if (Lenth < 2)
    {
        return 0;
    }
    int i = ceil(log2(Lenth + 1)), j = Lenth - (pow(2, i - 1) - 1);
    if (j > pow(2, i - 2))
    {
        return pow(2, i - 1) - 1;
    }
    else
    {
        return pow(2, i - 2) - 1 + j;
    }
}

void MakeCBTree(CBTree C, CBTree R, int Start, int End, int Root)
{
    // 初始值为C, R, 0, N-1, 0  **N为元素总个数
    int Lenth = End - Start + 1;
    if (!Lenth)
    {
        return;
    }
    int LeftLenth = LeftSize(Lenth);
    R->Elements[Root] = C->Elements[LeftLenth + Start];
    int LeftRoot = Root * 2 + 1, RightRoot = LeftRoot + 1;
    MakeCBTree(C, R, Start, LeftLenth + Start - 1, LeftRoot);
    MakeCBTree(C, R, LeftLenth + Start + 1, End, RightRoot);
}

CBTree BuildCBT(CBTree C)
{
    BubbleSort(C);
    CBTree R = CreateCBTree();
    MakeCBTree(C, R, 0, C->Size, 0);
    R->Size = C->Size;
    return R;
}

void LevelOrderTraversal(CBTree C)
{
    int flag = 0;
    for (int i = 0; i <= C->Size; i++)
    {
        if (!flag)
        {
            flag = 1;
        }
        else
        {
            printf(" ");
        }
        printf("%d", C->Elements[i]);
    }
    // printf("\n");
}

int main()
{
    CBTree C, R;
    C = ReadTree();
    // BubbleSort(C);
    // LevelOrderTraversal(C);
    R = BuildCBT(C);
    LevelOrderTraversal(R);
    return 0;
}