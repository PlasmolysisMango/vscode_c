#include <stdio.h>
#include <stdlib.h>

typedef struct AVLNode *AVLTree;
typedef AVLTree Position;
typedef int ElementType;
struct AVLNode
{
    ElementType Data;
    AVLTree Left;
    AVLTree Right;
    int Height;
};

int GetHeight(AVLTree A)
{
    if (!A)
    {
        return 0;
    }
    else
    {
        return A->Height;
    }
}

int Max(int a, int b)
{
    return a > b ? a : b;
}

AVLTree SingleRightRotation(AVLTree A)
{
    AVLTree B = A->Right;
    A->Right = B->Left;
    B->Left = A;
    A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;
    B->Height = Max(GetHeight(B->Right), A->Height) + 1;
    return B;
}

AVLTree SingleLeftRotation(AVLTree A)
{
    AVLTree B = A->Left;
    A->Left = B->Right;
    B->Right = A;
    A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;
    B->Height = Max(GetHeight(B->Left), A->Height) + 1;
    return B;
}

AVLTree DoubleRightLeftRotation(AVLTree A)
{
    A->Right = SingleLeftRotation(A->Right);
    return SingleRightRotation(A);
}

AVLTree DoubleLeftRightRotation(AVLTree A)
{
    A->Left = SingleRightRotation(A->Left);
    return SingleLeftRotation(A);
}

AVLTree Insert(ElementType X, AVLTree A)
{
    if (!A)
    {
        A = (AVLTree)malloc(sizeof(struct AVLNode));
        A->Data = X;
        A->Left = A->Right = NULL;
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
                else
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
                if (X < A->Left->Data)
                {
                    A = SingleLeftRotation(A);
                }
                else
                {
                    A = DoubleLeftRightRotation(A);
                }
            }
        }
    }
    A->Height = Max(GetHeight(A->Left), GetHeight(A->Right)) + 1;
    return A;
}

int main()
{
    int N, m;
    AVLTree A = NULL;
    scanf("%d", &N);
    while (N--)
    {
        scanf("%d", &m);
        A = Insert(m, A);
    }
    if (A)
    {
        printf("%d", A->Data);
    }
    return 0;
}