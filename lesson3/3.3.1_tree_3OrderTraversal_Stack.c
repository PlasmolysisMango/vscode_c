// 使用堆栈实现先序、中序、后序的二叉树遍历。
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

typedef struct StackNode *Stack;
struct StackNode
{
    BinTree Data;
    Stack Link;
};

Stack CreateStack()
{
    Stack S;
    S = (Stack)malloc(sizeof(struct StackNode));
    S->Link = NULL;
    return S;
}

void Push(BinTree BT, Stack S)
{
    Stack newnode;
    newnode = (Stack)malloc(sizeof(struct StackNode));
    newnode->Data = BT;
    newnode->Link = S->Link;
    S->Link = newnode;
}

BinTree Pop(Stack S)
{
    if (S->Link)
    {
        Stack p = S->Link;
        BinTree pt = p->Data;
        S->Link = p->Link;
        free(p);
        return pt;
    }
    else
    {
        return NULL;
    }
}

BinTree ReadTree()
{
    int N, R = 0;
    BinTree A[MAXN];
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
    {
        A[i] = (BinTree)malloc(sizeof(struct TreeNode));
    }
    for (int i = 0; i < N; i++)
    {
        R += i;
        char cleft, cright;
        scanf("\n%c %c %c", &(A[i]->Data), &cleft, &cright); 
        /* scanf在%c会录入转义字符在内的所有字符。*/
        if (cleft != '-')
        {
            int left = cleft - '0';
            A[i]->Left = A[left];
            R -= left;
        }
        else
        {
            A[i]->Left = NULL;
        }
        if (cright != '-')
        {
            int right = cright - '0';
            A[i]->Right = A[right];
            R -= right;
        }
        else
        {
            A[i]->Right = NULL;
        }
    }
    // printf("%d", R);
    return A[R];
}

void InOrderTraversal(BinTree BT)
{
    Stack S = CreateStack();
    int flag = 0;
    while (BT || S->Link)
    {
        while (BT)
        {
            Push(BT, S);
            BT = BT->Left;
        }
        if (S->Link)
        {
            if (!flag)
            {
                flag = 1;
            }
            else
            {
                printf(" ");
            }
            BT = Pop(S);
            printf("%c", BT->Data);
            BT = BT->Right;
        }
    }
    if (flag)
    {
        printf("\n");
    }
    free(S);
}

void PreOrderTraversal(BinTree BT)
{
    Stack S = CreateStack();
    int flag = 0;
    while (BT || S->Link)
    {
        while (BT)
        {
            if (!flag)
            {
                flag = 1;
            }
            else
            {
                printf(" ");
            }
            printf("%c", BT->Data);
            Push(BT, S);
            BT = BT->Left;
        }
        if (S->Link)
        {
            BT = Pop(S);
            BT = BT->Right;
        }
    }
    if (flag)
    {
        printf("\n");
    }
    free(S);
}

void PostOrderTraversal(BinTree BT)
{
    Stack S = CreateStack();
    BinTree temptree = NULL;
    int flag = 0;
    while (BT || S->Link)
    {
        while (BT)
        {
            Push(BT, S);
            BT = BT->Left;
        }
        if (S->Link)
        {
            BT = Pop(S);
            if (BT->Right && BT->Right != temptree)
            {
                Push(BT, S);
                BT = BT->Right;
            }
            else
            {
                temptree = BT;
                if (!flag)
                {
                    flag = 1;
                }
                else
                {
                    printf(" ");
                }
                printf("%c", BT->Data);
                BT = NULL;
            }
        }
    }
    if (flag)
    {
        printf("\n");
    }
    free(S);
}

int main()
{
    BinTree B;
    B = ReadTree();
    PostOrderTraversal(B);
}