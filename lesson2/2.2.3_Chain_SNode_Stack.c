#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct SNode *Stack;
struct SNode
{
    ElementType Data;
    struct SNode *Next;
};

Stack CreateStack()
{
    Stack S;
    S = (Stack)malloc(sizeof(struct SNode));
    S->Next = NULL;
    return S;
}

int isEmpty(Stack S)
{
    return (S->Next == NULL);
}

void Push(ElementType item, Stack S)
{
    Stack TmpCell;
    TmpCell = (Stack)malloc(sizeof(struct SNode));
    TmpCell->Data = item;
    TmpCell->Next = S->Next;
    S->Next = TmpCell;
}

ElementType Pop(Stack S)
{
    if (isEmpty(S))
    {
        printf("堆栈空\n");
        return NULL;
    }
    else
    {
        Stack PopCell = S->Next;
        ElementType PopData = PopCell->Data;
        S->Next = PopCell->Next;
        free(PopCell);
        return PopData;
    }
}