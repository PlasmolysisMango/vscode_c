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
    A->Left = C->Right;
    B->Right = C->Left;
    C->Left = B;
    C->Right = A;
    A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;
    B->Height = Max(GetHeight(B->Left), GetHeight(B->Right)) + 1;
    C->Height = Max(A->Height, B->Height) + 1;
    return C;
}


AVLTree SDoubleLeftRightRotation ( AVLTree A )
{  
    A->Left = SingleRightRotation(A->Left);
    return SingleLeftRotation(A);
}

AVLTree SDoubleRightLeftRotation ( AVLTree A )
{  
    A->Right = SingleLeftRotation(A->Right);
    return SingleRightRotation(A);
}

AVLTree DoubleRightLeftRotation(AVLTree A) //右左双旋RL
{
    //A必须有右子树B，B必须有左子树C
    AVLTree B = A->Right, C = B->Left;
    A->Right = C->Left;
    B->Left = C->Right;
    C->Left = A;
    C->Right = B;
    A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;
    B->Height = Max(GetHeight(B->Left), GetHeight(B->Right)) + 1;
    C->Height = Max(A->Height, B->Height) + 1;
    return C;
}

AVLTree Insert(ElementType X, AVLTree A)
{
    if (!A)
    {
        A = (AVLTree)malloc(sizeof(struct AVLNode));
        A->Left = A->Right = NULL;
        A->Data = X;
        A->Height = 0;
    }
    else
    {
        if (X > A->Data)
        {
            A->Right = Insert(X, A->Right);
            if (GetHeight(A->Left) - GetHeight(A->Right) == -2)
            {
                if (X > A->Right->Data)
                {
                    A = SingleRightRotation(A);
                }
                else if (X < A->Right->Data)
                {
                    A = DoubleRightLeftRotation(A);
                }
            }
        }
        else if (X < A->Data)
        {
            A->Left = Insert(X, A->Left);
            if (GetHeight(A->Left) - GetHeight(A->Right) == 2)
            {
                if (X > A->Left->Data)
                {
                    A = DoubleLeftRightRotation(A);
                }
                else if (X < A->Left->Data)
                {
                    A = SingleLeftRotation(A);
                }
            }
        }
    }
    A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;
    return A;
}

void InorderTraversal(AVLTree A)
{
    if (A)
    {
        InorderTraversal(A->Left);
        printf("%d ", A->Data);
        InorderTraversal(A->Right);
    }
}

int main()
{
    int N, num;
    AVLTree A = NULL;
    scanf("%d", &N);
    while (N--)
    {
        scanf("%d", &num);
        A = Insert(num, A);
    }
    InorderTraversal(A);
    return 0;
}