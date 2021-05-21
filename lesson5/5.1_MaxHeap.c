#include <stdio.h>
#include <stdlib.h>

#define MaxSize 20
#define MaxData 100 // 哨兵元素

typedef int ElementType;
typedef struct HeapNode
{
    ElementType *Elements;
    int Size;
    int Capacity;
} * MaxHeap;

MaxHeap CreateHeap()
{
    MaxHeap H = (MaxHeap)malloc(sizeof(struct HeapNode));
    H->Elements = (ElementType)malloc((MaxSize + 1) * sizeof(ElementType));
    H->Size = 0;
    H->Capacity = MaxSize;
    H->Elements[0] = MaxData;
    return H;
}

int isFull(MaxHeap H)
{
    if (!H)
    {
        return 1;
    }
    else if (H->Size == H->Capacity)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void Insert(MaxHeap H, ElementType item)
{
    int i;
    if (isFull(H))
    {
        printf("最大堆已满");
        return;
    }
    i = ++H->Size;
    for (; H->Elements[i / 2] < item; i /= 2)
    {
        H->Elements[i] = H->Elements[i / 2];
    }
    H->Elements[i] = item;
}

