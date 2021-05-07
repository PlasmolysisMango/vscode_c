#include <stdio.h>
#include <stdlib.h>

#define MAXN 10

typedef char ElementType;
typedef struct TreeNode *BinTree;
struct TreeNode
{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

BinTree ReadTree()
{
    int N, R = 0;
    BinTree Root, A[MAXN];
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
    {
        R += i;
        char left, right;
        A[i] = (BinTree)malloc(sizeof(struct TreeNode));
        scanf("%c %c %c", A[i]->Data, left, right);
        if (left != '-')
        {
            A[i]->Left = A[(int)left];
            R -= (int)left;
        }
        else
        {
            A[i]->Left = NULL;
        }
        if (right != '-')
        {
            A[i]->Right = A[(int)right];
            R -= (int)right;
        }
        else
        {
            A[i]->Right = NULL;
        }
    }
    return A[R];
}