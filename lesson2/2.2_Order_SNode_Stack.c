#include <stdio.h>

#define MAXN 10

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
