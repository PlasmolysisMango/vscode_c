#include <stdio.h>
#include <stdlib.h>

#define MaxSize 30

typedef int ElementType;
typedef struct StackNode 
{
    ElementType Data;
    struct StackNode *Link;
} * Stack;

ElementType Pre[MaxSize], In[MaxSize], Post[MaxSize];

Stack CreateStack()
{
    Stack S = malloc(sizeof(struct StackNode));
    S->Link = NULL;
    return S;
}

void Push(Stack S, ElementType X)
{
    Stack newnode = malloc(sizeof(struct StackNode));
    newnode->Data = X;
    newnode->Link = S->Link;
    S->Link = newnode;
}

ElementType Pop(Stack S)
{
    Stack tmpnode = S->Link;
    S->Link = tmpnode->Link;
    ElementType X = tmpnode->Data;
    free(tmpnode);
    return X;
}

void ReadInput(int N)
{
    char s[5];
    int pre_i = -1, in_i = -1;
    Stack S = CreateStack();
    for (int i = 0; i < 2 * N; i++)
    {
        scanf("\n%s", s);
        if (s[1] == 'u') // Push的情况，在中序遍历算法中，Push的顺序即为先序遍历的顺序；
        {
            scanf("%d", &Pre[++pre_i]);
            Push(S, Pre[pre_i]);
        }
        else // Pop的情况
        {
            In[++in_i] = Pop(S);
        }
    }
    free(S);
}

void PostTra(int pre_Left, int in_left, int post_Left, int N)
{
    // 初始值 0, 0, 0, N 
    if (N == 0)
    {
        return;
    }
    if (N == 1)
    {
        Post[post_Left] = Pre[pre_Left];
        return;
    }
    int i;
    ElementType root = Pre[pre_Left];
    Post[post_Left + N - 1] = root;
    for (i = 0; i < N; i++)
    {
        if (In[in_left + i] == root)
        {
            break;
        }
    }
    PostTra(pre_Left + 1, in_left, post_Left, i);
    PostTra(pre_Left + i + 1, in_left + i + 1, post_Left + i, N - i - 1);
}

void PrintList(ElementType *p, int N)
{
    for (int i = 0; i < N; i++)
    {
        printf("%d ", p[i]);
    }
    printf("\n");
}

int main()
{
    int N;
    scanf("%d", &N);
    ReadInput(N);
    PrintList(Pre, N);
    PrintList(In, N);
    PostTra(0, 0, 0, N);
    PrintList(Post, N);
}