#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

#define ERROR 0;

struct Node
{
    ElementType Data;
    struct Node *Next;
};

typedef struct QNode *Queue;
struct QNode
{
    struct Node *rear;
    struct Node *front;
};

Queue CreateQueue()
{
    Queue PtrQ;
    PtrQ = (Queue)malloc(sizeof(struct QNode));
    PtrQ->front = PtrQ->rear = NULL;
    return PtrQ;
}

ElementType DeleteQ(Queue PtrQ)
{
    struct Node *FrontCell;
    ElementType FrontElem;

    if (PtrQ->front == NULL)
    {
        printf("队列空\n");
        return ERROR;
    }
    FrontCell = PtrQ->front;
    if (PtrQ->front == PtrQ->rear)
    {
        PtrQ->front = PtrQ->rear = NULL;
    }
    else
    {
        PtrQ->front = PtrQ->front->Next;
    }
    FrontElem = FrontCell->Data;
    free(FrontCell);
    return FrontElem;
}

void AddQ(ElementType item, Queue PtrQ)
{
    struct Node *newcell;
    newcell = (struct Node*)malloc(sizeof(struct Node));
    newcell->Data = item;
    newcell->Next = NULL;
    if (PtrQ->front == NULL)
    {
        PtrQ->front = PtrQ->rear = newcell;
    }
    else
    {
        PtrQ->rear->Next = newcell;
        PtrQ->rear = newcell;
    }
}

int main()
{
    Queue PtrQ = CreateQueue();
    for (int i = 0; i < 4; i++)
    {
        AddQ(i + 1, PtrQ);
    }
    for (int i = 0; i < 4; i++)
    {
        printf("%d\n", DeleteQ(PtrQ));
    }
}