// 玩转二叉树：按先序和中序得到二叉树并交换左右子树
#include <stdio.h>
#include <stdlib.h>

#define MaxN 30

typedef struct TNode
{
    int Data;
    struct TNode *Left, *Right;
} * Tree;

Tree NewNode()
{
    Tree tmp = malloc(sizeof(struct TNode));
    tmp->Left = tmp->Right = NULL;
    return tmp;
}

int Pre[30], In[30];

int N;

Tree BT;

Tree Build(int in_left, int pre_left, int length) //0 0 N BT中序、先序的起始坐标和长度
{
    if (!length) // 退出条件
    {
        return NULL;
    }
    Tree TRoot = NewNode();
    TRoot->Data = Pre[pre_left]; // 为根赋值
    int i;
    for (i = 0; i < length; i++) // 寻找根在中序序列中的位置
    {
        if (TRoot->Data == In[i + in_left])
        {
            break;
        }
    }
    // i 即为左序列长度， Length - i - 1即为右序列长度
    TRoot->Right = Build(in_left, pre_left + 1, i);
    TRoot->Left = Build(in_left + i + 1, pre_left + i + 1, length - i - 1);
    return TRoot;
}

Tree Q[MaxN];
int front, rear;
int qsize;

void InitQ()
{
    front = rear = 0;
    qsize = 5; // 即最多存放4个元素
}

void AddQ(Tree X)
{
    if ((rear + 1) % qsize == front)
    {
        printf("Full!\n");
        return;
    }
    rear = (rear + 1) % qsize;
    Q[rear] = X;
}

Tree DeleteQ()
{
    if (rear == front)
    {
        printf("Empty!\n");
        return NULL;
    }
    front = (front + 1) % qsize;
    return Q[front];
}

void LevelTravelsal()
{
    if (!BT)
    {
        return;
    }
    InitQ();
    AddQ(BT);
    int flag = 0;
    while (rear != front) //当队列不空
    {
        Tree tmp = DeleteQ();
        if (!flag)
        {
            flag = 1;
        }
        else
        {
            printf(" ");
        }
        printf("%d", tmp->Data);
        if (tmp->Left)
        {
            AddQ(tmp->Left);
        }
        if (tmp->Right)
        {
            AddQ(tmp->Right);
        }
    }
}

void Read()
{
    scanf("%d", &N);
    for (int i = 0; i < N * 2; i++)
    {
        if (i < N)
        {
            scanf("%d", &In[i]);
        }
        else
        {
            scanf("%d", &Pre[i - N]);
        }
    }
}

int main()
{
    Read();
    BT = Build(0, 0, N);
    LevelTravelsal();
    return 0;
}
