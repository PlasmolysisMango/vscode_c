// 尚未测试...
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

void Insert(MinHeap H, ElementType X)
{
    int i = ++H->Size;
    for (; i / 2; i /= 2)
    {
        if (X < H->Elements[i / 2])
        {
            H->Elements[i] = H->Elements[i / 2];
        }
        else
        {
            break;
        }
    }
    H->Elements[i] = X;
}

MinHeap OrderBuildHeap(int N)
{
    MinHeap H = CreateHeap();
    ElementType temp;
    while (N--)
    {
        scanf("%d", &temp);
        Insert(H, temp);
    }
    return H;
}

// void PercDown(MinHeap H, int p)
// {
//     int Parent, Child;
//     ElementType temp = H->Elements[p];
//     for (Parent = p; Parent * 2 <= H->Size; Parent = Child)
//     {
//         Child = Parent * 2;
//         if (Child != H->Size && H->Elements[Child] > H->Elements[Child + 1])
//         {
//             Child++;
//         }
//         if (H->Elements[Child] < temp)
//         {
//             H->Elements[Parent] = H->Elements[Child];
//         }
//         else
//         {
//             break;
//         }
//     }
//     H->Elements[Parent] = temp;
// }

// MinHeap BuildHeap(int N)
// {
//     MinHeap H = CreateHeap();
//     while (N--)
//     {
//         scanf("%d", &H->Elements[++H->Size]);
//     }
//     for (int i = H->Size / 2; i; i--)
//     {
//         PercDown(H, i);
//     }
//     return H;
// }

void LevelOrderTraversal(MinHeap H)
{
    for (int i = 1; i <= H->Size; i++)
    {
        printf("%d ", H->Elements[i]);
    }
}

void PathPrint(MinHeap H, int p)
{
    int flag = 0;
    for (; p; p /= 2)
    {
        if (!flag)
        {
            flag = 1;
        }
        else
        {
            printf(" ");
        }
        printf("%d", H->Elements[p]);
    }
}

int main()
{
    int N, M, flag = 0, tempn;
    scanf("%d %d", &N, &M);
    MinHeap H = OrderBuildHeap(N);
    while (M--)
    {
        scanf("%d", &tempn);
        if (tempn > 0 && tempn <= H->Size)
        {
            if (!flag)
            {
                flag = 1;
            }
            else
            {
                printf("\n");
            }
            PathPrint(H, tempn);
        }
    }
    return 0;
}
