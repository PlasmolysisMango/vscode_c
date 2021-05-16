#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode *BinTree;
typedef BinTree Position;
typedef int ElementType;
struct TreeNode
{
    ElementType Data;
    BinTree Left;
    BinTree Right;
    int flag; // 标记是否访问过。
};

BinTree Insert(ElementType X, BinTree BT)
{
    if (!BT)
    {
        BT = (BinTree)malloc(sizeof(struct TreeNode));
        BT->Data = X;
        BT->Left = BT->Right = NULL;
        BT->flag = 0;
    }
    else
    {
        if (X > BT->Data)
        {
            BT->Right = Insert(X, BT->Right);
        }
        else if (X < BT->Data)
        {
            BT->Left = Insert(X, BT->Left);
        }
    }
    return BT;
}

int SingleTest(int m, BinTree BT)
{
    while (BT)
    {
        if (BT->flag)
        {
            if (m > BT->Data)
            {
                BT = BT->Right;
            }
            else if (m < BT->Data)
            {
                BT = BT->Left;
            }
            else if (m == BT->Data)
            {
                return 0;
            }
        }
        else
        {
            if (m == BT->Data)
            {
                BT->flag = 1;
                return 1;
            }
            else
            {
                return 0;
            }
        }
    }
    return 0;
}

int Judge(int N, BinTree BT)
{
    int m, r = 1;
    while (N--)
    {
        scanf("%d", &m);
        if (r)
        {
            r = SingleTest(m, BT);
        }
    }
    return r;
}

BinTree ReadTree(int N)
{
    BinTree BT = NULL;
    ElementType x;
    while (N--)
    {
        scanf("%d", &x);
        BT = Insert(x, BT);
    }
    return BT;
}

void ResetFlag(BinTree BT)
{
    if (BT)
    {
        ResetFlag(BT->Left);
        BT->flag = 0;
        ResetFlag(BT->Right);
    }
}

void FreeTree(BinTree BT)
{
    if (BT)
    {
        FreeTree(BT->Left);
        FreeTree(BT->Right);
        free(BT);
    }
}

int main()
{
    int N, L;
    BinTree BT = NULL;
    while (1)
    {
        scanf("%d", &N);
        if (!N)
        {
            break;
        }
        scanf("%d", &L);
        BT = ReadTree(N);
        while (L--)
        {
            if (Judge(N, BT))
            {
                printf("Yes\n");
            }
            else
            {
                printf("No\n");
            }
            ResetFlag(BT);
        }
        FreeTree(BT);
        BT = NULL;
    }
}

