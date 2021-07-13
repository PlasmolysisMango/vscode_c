// 二叉搜索树的各种操作
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct TreeNode *BinTree;
typedef BinTree Position;
struct TreeNode
{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

Position Find(BinTree BST, ElementType X)
{
    if (!BST)
    {
        return NULL;
    }
    if (X > BST->Data)
    {
        return Find(X, BST->Right);
    }
    else if (X < BST->Data)
    {
        return Find(X, BST->Left);
    }
    else
    {
        return BST;
    }
}

Position IterFind(ElementType X, BinTree BST) //迭代方式实现查找
{
    while (BST)
    {
        if (X > BST->Data)
        {
            BST = BST->Right;
        }
        else if (X < BST->Data)
        {
            BST = BST->Left;
        }
        else
        {
            return BST;
        }
    }
    return NULL;
}

Position FindMin(BinTree BST)
{
    if (!BST)
    {
        return NULL;
    }
    if (!BST->Left)
    {
        return BST;
    }
    else
    {
        return FindMin(BST->Left);
    }
}

Position FindMax(BinTree BST)
{
    if (!BST)
    {
        return NULL;
    }
    if (!BST->Right)
    {
        return BST;
    }
    else
    {
        return FindMax(BST->Right);
    }
}

Position IterFindMin(BinTree BST)
{
    while (BST)
    {
        if (BST->Left)
        {
            BST = BST->Left;
        }
        else
        {
            return BST;
        }
    }
    return NULL;
}

Position IterFindMax(BinTree BST)
{
    if (BST)
    {
        while (BST->Right)
        {
            BST = BST->Right;
        }
    }
    return BST;
}

BinTree Insert(BinTree BST, ElementType X)
{
    if (!BST)
    {
        BST = (BinTree)malloc(sizeof(struct TreeNode));
        BST->Data = X;
        BST->Left = BST->Right = NULL;
    }
    else
    {
        if (X > BST->Data)
        {
            BST->Right = Insert(X, BST->Right);
        }
        else if (X < BST->Data)
        {
            BST->Left = Insert(X, BST->Left);
        }
    }
    return BST;
}

BinTree Delete(BinTree BST, ElementType X)
{
    BinTree tmpnode;
    if (!BST)
    {
        printf("Not Found\n");
    }
    else if (X > BST->Data)
    {
        BST->Right = Delete(BST->Right, X);
    }
    else if (X < BST->Data)
    {
        BST->Left = Delete(BST->Left, X);
    }
    else
    {
        if (BST->Left && BST->Right)
        {
            tmpnode = FindMin(BST->Right);
            BST->Data = tmpnode->Data;
            BST->Right = Delete(BST->Right, BST->Data);
        }
        else
        {
            tmpnode = BST;
            if (!BST->Left)
            {
                BST = BST->Right;
            }
            else if (!BST->Right)
            {
                BST = BST->Left;
            }
            free(tmpnode);
        }
    }
    return BST;
}

void InOrderTraversal(BinTree BST)
{
    if (BST)
    {
        InOrderTraversal(BST->Left);
        printf("%d ", BST->Data);
        InOrderTraversal(BST->Right);
    }
}

int main()
{
    int N, tmp;
    BinTree BST = NULL;
    scanf("%d", &N);
    while (N--)
    {
        scanf("%d", &tmp);
        BST = Insert(tmp, BST);
    }
    InOrderTraversal(BST);
    scanf("%d", &tmp);
    BST = Delete(tmp, BST);
    InOrderTraversal(BST);
}