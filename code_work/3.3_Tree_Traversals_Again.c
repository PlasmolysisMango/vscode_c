#include <stdio.h>
#include <stdlib.h>

#define MAXN 30

typedef struct TreeNode *Tree;
struct TreeNode
{
    int Data;
    Tree left;
    Tree right;
};

typedef Tree ElementType;
typedef struct StackNode *Stack;
struct StackNode
{
    ElementType Element;
    Stack Link;
};

Stack CreateStack()
{
    Stack S = (Stack)malloc(sizeof(struct StackNode));
    S->Link = NULL;
    return S;
}

void Push(ElementType T, Stack S)
{
    Stack newnode = (Stack)malloc(sizeof(struct StackNode));
    newnode->Element = T;
    newnode->Link = S->Link;
    S->Link = newnode;
}

ElementType Pop(Stack S)
{
    Stack tmpnode = S->Link;
    ElementType T = tmpnode->Element;
    S->Link = tmpnode->Link;
    free(tmpnode);
    return T;
}

Tree ReadTreeRoot()
{
    int N;
    char c[4], tmpc = '-'; // c[1]和tmpc存储上次和本次读入的命令
    Tree N1, N2, R = NULL; // N1、N2存储上次和本次操作的结点
    Stack S = CreateStack();
    scanf("%d", &N);
    for (int i = 0; i < (2 * N); i++)
    {
        scanf("\n%s", c);
        if (tmpc == '-') // 第一次读入
        {
            R = N2 = (Tree)malloc(sizeof(struct TreeNode));
            scanf("%d", &N2->Data);
            Push(N2, S);
        }
        else if (c[1] == 'u') //本次命令为Push
        {
            N2 = (Tree)malloc(sizeof(struct TreeNode));
            scanf("%d", &N2->Data);
            Push(N2, S);
            if (tmpc == 'u') // Push + Push
            {
                N1->left = N2;
            }
            else // Pop + Push
            {
                N1->right = N2;
            }
        }
        else if (c[1] == 'o') //本次命令为Pop
        {
            N2 = Pop(S);
            if (tmpc == 'u') // Push + Pop
            {
                N1->left = NULL;
            }
            else // Pop + Pop
            {
                N1->right = NULL;
            }
        }
        N1 = N2;
        tmpc = c[1];
    }
    N2->right = NULL;
    free(S);
    if (R)
    {
        return R;
    }
    else
    {
        return NULL;
    }
}

void PostTraversal(Tree T)
{
    Stack S = CreateStack();
    Tree tmpnode = NULL;
    int flag = 0;
    while (T || S->Link)
    {
        while (T)
        {
            Push(T, S);
            T = T->left;
        }
        if (S->Link)
        {
            T = Pop(S);
            if (T->right && T->right != tmpnode)
            {
                Push(T, S);
                T = T->right;
            }
            else
            {
                tmpnode = T;
                if (!flag)
                {
                    flag = 1;
                }
                else
                {
                    printf(" ");
                }
                printf("%d", T->Data);
                T = NULL;
            }
        }
    }
}

int main()
{
    Tree T;
    T = ReadTreeRoot();
    // printf("%d %d", T->Data, T->left->Data);
    PostTraversal(T);
}