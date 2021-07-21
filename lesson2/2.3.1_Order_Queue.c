#include <stdio.h>
#include <stdlib.h>

#define MAXN 10

typedef int ElementType;

typedef struct QNode *Queue;
struct QNode
{
    ElementType Data[MAXN];
    int rear;
    int front;
};

Queue CreateQueue()
{
    Queue PtrQ;
    PtrQ = (Queue)malloc(sizeof(struct QNode));
    PtrQ->front = 0; // 保证只存储N-1个元素
    PtrQ->rear = 0;
    return PtrQ;
}

void AddQ(Queue PtrQ, ElementType item)
{
    if ((PtrQ->rear + 1) % MAXN == PtrQ->front)
    {
        printf("队列满\n");
        return;
    }
    PtrQ->rear = (PtrQ->rear + 1) % MAXN;
    PtrQ->Data[PtrQ->rear] = item;
}

ElementType DeleteQ(Queue PtrQ)
{
    if (PtrQ->front == PtrQ->rear)
    {
        printf("队列空\n");
        return NULL;
    }
    else
    {
        PtrQ->front = (PtrQ->front + 1) % MAXN;
        return PtrQ->Data[PtrQ->front];
    }
}

int main()
{
    Queue PtrQ = CreateQueue();
    for (int i = 0; i < 4; i++)
    {
        AddQ(PtrQ, i + 1);
    }
    for (int i = 0; i < 4; i++)
    {
        printf("%d\n", DeleteQ(PtrQ));
    }

}