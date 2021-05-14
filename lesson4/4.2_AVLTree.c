#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct AVLNode *AVLTree;
typedef AVLTree Position;
struct AVLNode
{
    ElementType Data;
    AVLTree Left;
    AVLTree Right;
    int Height;
};

int Max(int a, int b)
{
    return a > b ? a : b;
}

int GetHeight(AVLTree A)
{
    if (A)
    {
        return A->Height;
    }
    else
    {
        return 0;
    }
}

AVLTree SingleLeftRotation(AVLTree A) //单左旋LL
{
    // A必须有左子树B
    AVLTree B = A->Left;
    A->Left = B->Right;
    B->Right = A;
    A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;
    B->Height = Max(GetHeight(B->Left), GetHeight(A)) + 1;
    return B;
}

AVLTree SingleRightRotation(AVLTree A) //单右旋RR
{
    // A必须有右子树B
    AVLTree B = A->Right;
    A->Right = B->Left;
    B->Left = A;
    A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;
    B->Height = Max(GetHeight(B->Left), GetHeight(A)) + 1;
    return B;
}

AVLTree DoubleLeftRightRotation(AVLTree A) //左右双旋LR
{
    //A必须有左子树B，B必须有右子树C
    AVLTree B = A->Left, C = B->Right;
    
}