#include <stdlib.h>
#include <stdio.h>

#define MinData -10001
#define MaxSize 1000
typedef int ElementType;
typedef struct HeapNode
{
    ElementType *Elements;
    int Size;
} * MinHeap;

MinHeap CreateHeap()
{
    MinHeap H = malloc(sizeof(struct HeapNode));
    H->Elements = malloc((MaxSize + 1) * sizeof(ElementType));
    H->Size = 0;
    H->Elements[0] = MinData;
    return H;
}

