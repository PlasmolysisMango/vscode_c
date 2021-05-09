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
    scanf("%d\n", &N);
    for (int i = 0; i < N; i++)
    {
        A[i] = (BinTree)malloc(sizeof(struct TreeNode));
    }
    for (int i = 0; i < N; i++)
    {
        printf("%d\n", i);
        R += i;
        char cleft, cright;
        scanf("%c %c %c\n", &(A[i]->Data), &cleft, &cright); 
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
    if (!N)
    {
        return NULL;
    }
    else
    {
        return A[R];
    }
    
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

BinTree AvilBTree(BinTree B1, BinTree B2)
{
    if (!B1 && B2)
    {
        return B2;
    }
    if (B1 && !B2)
    {
        return B1;
    }
    return NULL;
}

int isSameStruct(BinTree B1, BinTree B2)
{
    if (!B1 && !B2)
    {
        return 1;
    }
    if ((B1 && !B2) || (!B1 && B2))
    {
        return 0;
    }
    if (B1->Data != B2->Data)
    {
        return 0;
    }
    if ((!(B1->Left && B1->Right) || !(B2->Left && B2->Right)))
    {
        return isSameStruct(AvilBTree(B1->Left, B1->Right), 
        AvilBTree(B2->Left, B2->Right));
    }
    else if (B1->Left->Data == B2->Left->Data)
    {
        return (isSameStruct(B1->Left, B2->Left) &&
                isSameStruct(B1->Right, B2->Right));
    }
    else if (B1->Left->Data == B2->Right->Data)
    {
        return (isSameStruct(B1->Left, B2->Right) &&
                isSameStruct(B1->Right, B2->Left));
    }
    else
    {
        return 0;
    }

    
}

int main()
{
    BinTree B1, B2;
    B1 = ReadTree();
    B2 = ReadTree();
    if (isSameStruct(B1, B2))
    {
        printf("Yes\n");
    }
    else
    {
        printf("No\n");
    }
    return 0;
}