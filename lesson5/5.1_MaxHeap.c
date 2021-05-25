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
    H->Elements = (ElementType*)malloc((MaxSize + 1) * sizeof(ElementType));
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

int isEmpty(MaxHeap H)
{
    if (!H)
    {
        return 0;
    }
    else if (H->Size == 0)
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

ElementType DeleteMax(MaxHeap H)
{
    int Parent, Child;
    ElementType MaxItem, temp;
    if (isEmpty(H))
    {
        printf("最大堆已空");
        return -1;
    }
    MaxItem = H->Elements[1];
    temp = H->Elements[H->Size--];
    for (Parent = 1; Parent * 2 <= H->Size; Parent = Child)
    {
        Child = Parent * 2;
        if ((Child != H->Size && H->Elements[Child] < H->Elements[Child + 1]))
        {
            Child++;
        }
        if (temp < H->Elements[Child])
        {
            H->Elements[Parent] = H->Elements[Child];
        }
        else
        {
            break;
        }
    }
    H->Elements[Parent] = temp;
    return MaxItem;
}

void PercDown(MaxHeap H, int p) //下标为p的根节点对应树的最大堆化
{
    ElementType temp = H->Elements[p];
    int Parent, Child;
    for (Parent = p; Parent * 2 <= H->Size; Parent = Child)
    {
        Child = 2 * Parent;
        if (Child < H->Size && H->Elements[Child] < H->Elements[Child + 1])
        {
            Child++;
        }
        if (H->Elements[Child] <= temp)
        {
            break;
        }
        else
        {
            H->Elements[Parent] = H->Elements[Child];
        }
    }
    H->Elements[Parent] = temp;
}

MaxHeap BuildHeap() //输入字符串来建立最大堆
{
    int N;
    MaxHeap H = CreateHeap();
    scanf("%d", &N);
    while (N--)
    {
        scanf("%d", &H->Elements[++H->Size]);
    }
    for (int i = H->Size / 2; i > 0; i--)
    {
        PercDown(H, i);
    }
    return H;
}

void LevelOrderTraversal(MaxHeap H)
{
    for (int i = 1; i <= H->Size; i++)
    {
        printf("%d ", H->Elements[i]);
    }
    printf("\n");
}

int main()
{
    MaxHeap H = BuildHeap();
    LevelOrderTraversal(H);
    Insert(H, 8);
    LevelOrderTraversal(H);
    ElementType x = DeleteMax(H);
    LevelOrderTraversal(H);
    return 0;
}
