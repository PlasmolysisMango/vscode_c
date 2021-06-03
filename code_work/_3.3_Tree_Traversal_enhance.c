#include <stdio.h>
#include <stdlib.h>

#define MaxSize 30

typedef int ElementType;
typedef struct StackNode 
{
    ElementType Data;
    struct StackNode *Link;
} * Stack;

Stack CreateStack()
{
    Stack S = malloc(sizeof(struct StackNode));
    S->Link = NULL;
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
    
}