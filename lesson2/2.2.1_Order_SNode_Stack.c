#include <stdio.h>

#define MAXN 10

#define ERROR NULL

typedef int ElementType;

typedef struct SNode *Stack;
struct SNode
{
    ElementType Data[MAXN];
    int Top;
};

void Push(Stack Ptrs, ElementType item)
{
    if (Ptrs->Top == MAXN - 1)
    {
        printf("堆栈满\n");
        return;
    }
    else
    {
        Ptrs->Data[++(Ptrs->Top)] = item;
        return;
    }
}

ElementType Pop(Stack Ptrs)
{
    if (Ptrs->Top == -1)
    {
        printf("堆栈空\n");
        return ERROR;
    }
    else
    {
        return Ptrs->Data[(Ptrs->Top--)];
    }
}