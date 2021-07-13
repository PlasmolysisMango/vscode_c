/* 1. WPL最小，即与哈夫曼树的WPL相同；
   2. 满足前缀码；
   3. 无度为1的结点（满足1、2自动满足）；
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxLenth 63
#define MaxM 1000

typedef int Frequence; //用于存储字符出现的频率

typedef struct TreeNode //用于存储Huffman树
{
    Frequence Data;
    struct TreeNode *Left;
    struct TreeNode *Right;
} *HuffmanTree;

typedef struct HeapNode
{
    HuffmanTree *Elements;
    int Size;
} * MinHeap;

HuffmanTree NewNode()
{
    HuffmanTree newnode = malloc(sizeof(struct TreeNode));
    newnode->Left = newnode->Right = NULL;
    newnode->Data = -1;
    return newnode;
}

MinHeap CreateHeap()
{
    MinHeap H = malloc(sizeof(struct HeapNode));
    H->Elements = malloc((MaxLenth + 1) * sizeof(HuffmanTree));
    H->Elements[0] = NewNode();
    H->Elements[0]->Data = -1;
    H->Size = 0;
    return H;
}

void Insert(MinHeap H, HuffmanTree T)
{
    int i = ++H->Size;
    for (; H->Elements[i / 2]->Data > T->Data; i /= 2)
    {
        H->Elements[i] = H->Elements[i / 2];
    };
    H->Elements[i] = T;
}

HuffmanTree DeleteMin(MinHeap H)
{
    int Parent, Child;
    HuffmanTree temp = H->Elements[H->Size--], min = H->Elements[1];
    for (Parent = 1; Parent * 2 <= H->Size; Parent = Child)
    {
        Child = Parent * 2;
        if (Child != H->Size && H->Elements[Child]->Data > H->Elements[Child + 1]->Data)
        {
            Child++;
        }
        if (H->Elements[Child]->Data < temp->Data)
        {
            H->Elements[Parent] = H->Elements[Child];
        }
        else
        {
            break;
        }
    }
    H->Elements[Parent] = temp;
    return min;
}

HuffmanTree BuildTree(MinHeap H)
{
    HuffmanTree T;
    int N = H->Size;
    for (int i = 1; i < N; i++)
    {
        T = NewNode();
        T->Left = DeleteMin(H);
        T->Right = DeleteMin(H);
        T->Data = T->Left->Data + T->Right->Data;
        Insert(H, T);
    }
    T = DeleteMin(H);
    return T;
}

int WPL(HuffmanTree H, int Depth) //Depth为当前结点的深度
{
    // 初始值 (H, 0);
    if (!H->Left && !H->Right)
    {
        return Depth * H->Data;
    }
    else
    {
        return WPL(H->Left, Depth + 1) + WPL(H->Right, Depth + 1);
    }
}

MinHeap ReadHeap(Frequence *F, int N)
{
    MinHeap H = CreateHeap();
    HuffmanTree temp;
    for (int i = 0; i < N; i++)
    {
        scanf("\n%*c %d", &F[i]);
        temp = NewNode();
        temp->Data = F[i];
        Insert(H, temp);
    }
    return H;
}

void FreeTree(HuffmanTree T)
{
    if (T)
    {
        FreeTree(T->Left);
        FreeTree(T->Right);
        free(T);
    }
}

int JudgePrefix(HuffmanTree T, char *s, Frequence X)
{
    int L = strlen(s);
    int judge = 1;
    for (int i = 0; i < L; i++)
    {
        if (s[i] == '0')
        {
            if (!T->Left)
            {
                T->Left = NewNode();
            }
            T = T->Left;
        }
        else
        {
            if (!T->Right)
            {
                T->Right = NewNode();
            }
            T = T->Right;
        }
        if (T->Data != -1)
        {
            judge = 0;
            break;
        }
        if (i == L - 1)
        {
            if (T->Left || T->Right)
            {
                judge = 0;
                break;
            }
            T->Data = X;
        }
    }
    return judge;
}

int main()
{
    int N, M;
    scanf("%d", &N);
    Frequence F[MaxLenth];
    MinHeap H = ReadHeap(F, N);
    // for (int i = 0; i < N; i++)
    // {
    //     printf("%d ", H->Elements[i]->Data);
    // }
    HuffmanTree T = BuildTree(H);
    int StandardWPL = WPL(T, 0);
    scanf("%d", &M);
    char s[MaxLenth + 1];
    HuffmanTree TestTree;
    while (M--) // M个提交
    {
        int PathL = 0;
        int Check = 1;
        TestTree = NewNode();
        for (int i = 0; i < N; i++) // 若不正确，也要读完输入，不可break
        {
            scanf("\n%*c%s", s);
            // printf("%s", s);
            if (Check)
            {
                PathL += strlen(s) * F[i];
                if (PathL > StandardWPL)
                {
                    Check = 0;
                }
                else
                {
                    Check = JudgePrefix(TestTree, s, F[i]);
                }
                
            }
        }
        FreeTree(TestTree);
        if (Check)
        {
            printf("Yes\n");
        }
        else
        {
            printf("No\n");
        }
    }
}