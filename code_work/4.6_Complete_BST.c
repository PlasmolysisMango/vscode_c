/* 完全二叉树的构建，思路一：事先排序，后建树；
思路二：直接线性化建树，实现排序，再重新排列二叉树 */

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
};

BinTree Insert(ElementType X, BinTree BT)
{
    if (!BT)
    {
        BT = (BinTree)malloc(sizeof(struct TreeNode));
        BT->Data = X;
        BT->Left = BT->Right = NULL;
    }
}

BinTree ReadTree(int N)
{
    ElementType m;
    while (N--)
    {
        scanf("%d", &m);
        
    }
}
