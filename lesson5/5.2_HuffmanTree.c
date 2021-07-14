#include <stdio.h>
#include <stdlib.h>

#define MaxSize 20
#define MinWeight -1

typedef struct TreeNode *HuffmanTree;
typedef HuffmanTree ElementType;
struct TreeNode
{
    int Weight;
    HuffmanTree Left, Right;
};

typedef struct HeapNode
{
    ElementType *Elements;
    int Size;
} * MinHeap;

ElementType NewElement()
{
    ElementType E = malloc(sizeof(struct TreeNode));
    E->Left = E->Right = NULL;
    E->Weight = MinWeight;
    return E;
}

MinHeap CreateHeap()
{
    MinHeap H = malloc(sizeof(struct HeapNode));
    H->Elements =malloc(MaxSize * sizeof(ElementType));
    H->Size = 0;
    H->Elements[0] = NewElement();
    return H;
}

MinHeap ReadHeap()
{
    int N;
    MinHeap H = CreateHeap();
    scanf("%d", &N);
    while (N--)
    {
        H->Elements[++H->Size] = NewElement();
        scanf("%d", &H->Elements[H->Size]->Weight);
    }
    return H;
}

void PercDown(MinHeap H, int p) //下标为p的堆下滤，最小堆化
{
    int Parent, Child;
    ElementType temp;
    temp = H->Elements[p];
    for (Parent = p; Parent * 2 <= H->Size; Parent = Child)
    {
        Child = Parent * 2;
        if (Child != H->Size && 
        H->Elements[Child]->Weight > H->Elements[Child + 1]->Weight)
        {
            Child++;
        }
        if (H->Elements[Child]->Weight < temp->Weight)
        {
            H->Elements[Parent] = H->Elements[Child];
        }
        else
        {
            break;
        }
    }
    H->Elements[Parent] = temp;
}

void BuildMinHeap(MinHeap H)
{
    for (int i = H->Size / 2; i > 0; i--)
    {
        PercDown(H, i);
    }
}

void Insert(MinHeap H, ElementType E)
{
    int i;
    if (H->Size > MaxSize)
    {
        printf("最大堆已满\n");
        return;
    }
    i = ++H->Size;
    for (; H->Elements[i / 2]->Weight > E->Weight; i /= 2)
    {
        H->Elements[i] = H->Elements[i / 2];
    }
    H->Elements[i] = E;
}

ElementType DeleteMin(MinHeap H)
{
    ElementType MinItem = H->Elements[1];
    ElementType temp = H->Elements[H->Size--];
    int Parent, Child;
    for (Parent = 1; Parent * 2 <= H->Size; Parent = Child)
    {
        Child = Parent * 2;
        if (Child != H->Size && 
        H->Elements[Child]->Weight > H->Elements[Child + 1]->Weight)
        {
            Child++;
        }
        if (H->Elements[Child]->Weight < temp->Weight)
        {
            H->Elements[Parent] = H->Elements[Child];
        }
        else
        {
            break;
        }
    }
    H->Elements[Parent] = temp;
    return MinItem;
}

HuffmanTree Huffman(MinHeap H)
{
    int i, N = H->Size;
    HuffmanTree T;
    BuildMinHeap(H);
    for (i = 1; i < N; i++) //N - 1次循环
    {
        T = NewElement();
        T->Left = DeleteMin(H);
        T->Right = DeleteMin(H);
        T->Weight = T->Left->Weight + T->Right->Weight;
        Insert(H, T);
    }
    T = DeleteMin(H);
    return T;
}

void _InOrderTraversal(HuffmanTree T)
{
    if (T)
    {
        _InOrderTraversal(T->Left);
        printf("%d ", T->Weight);
        _InOrderTraversal(T->Right);
    }
}

void InOrderTraversal(HuffmanTree T)
{
    _InOrderTraversal(T);
    printf("\n");
}

void LevelOrderTraversal(MinHeap H)
{
    for (int i = 1; i <= H->Size; i++)
    {
        printf("%d ", H->Elements[i]->Weight);
    }
    printf("\n");
}

int main()
{
    MinHeap H = ReadHeap();
    // ElementType E = NewElement();
    // E->Weight = 0;
    // Insert(H, E);
    // LevelOrderTraversal(H);
    // E = DeleteMin(H);
    // LevelOrderTraversal(H);
    // Insert(H, E);
    // LevelOrderTraversal(H);
    // LevelOrderTraversal(H);
    // BuildMinHeap(H);
    // LevelOrderTraversal(H);
    HuffmanTree T = Huffman(H);
    // LevelOrderTraversal(H);
    InOrderTraversal(T);
    return 0;
}