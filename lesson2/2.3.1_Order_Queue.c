#include <stdio.h>

#define MAXN 10

typedef int ElementType;

typedef struct QNode *Queue;
struct QNode
{
    ElementType Data[MAXN];
    int rear;
    int front;
};
