#include <stdio.h>

#define MAXN 10
#define ERROR NULL

typedef int ElementType;

typedef struct DSNode *DStack;
struct DSNode
{
    ElementType Data[MAXN];
    int Top1;
    int Top2;
}; 

void Push(DStack Ptrs, ElementType item, int Tag)
{
    if (Ptrs->Top2 - Ptrs->Top1 == 1)
    {
        printf("堆栈满\n");
        return;
    }
    if (Tag == 1)
    {
        Ptrs->Data[++(Ptrs->Top1)] = item;
    }
    else
    {
        Ptrs->Data[--(Ptrs->Top2)] = item;
    }
    return;
}

ElementType Pop(DStack Ptrs, int Tag)
{
    if (Tag == 1)
    {
        if (Ptrs->Top1 == -1)
        {
            printf("堆栈1空\n");
            return ERROR;
        }
        else
        {
            return Ptrs->Data[Ptrs->Top1--];
        }
    }
    else
    {
        if (Ptrs->Top2 == MAXN)
        {
            printf("堆栈2空\n");
            return ERROR;
        }
        else
        {
            return Ptrs->Data[Ptrs->Top2++];
        }
    }
}