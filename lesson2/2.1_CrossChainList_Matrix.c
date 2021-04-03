// 十字链表实现（稀疏）矩阵的存储

#include <stdio.h>
#include <stdlib.h>

typedef struct CNode *CList;
struct CNode
{
    int Tag; // 标志域，0为头结点，1则为非零元素结点, 2为起始节点。
    int Row, Col; //行列信息
    union //子表指针域和单元素数据域共用存储空间
    {
        double Value;
        int Num;
        CList Next;
    } URegion;
    CList Down, Right; //指向后续结点
};

int max(int i, int j)
{
    return i > j ? i : j;
}

CList Init(int row, int col)
{
    CList Ptrl, p;
    int i = 0;
    Ptrl = (CList)malloc(sizeof(struct CNode));
    Ptrl->Tag = 2;
    Ptrl->Row = row;
    Ptrl->Col = col;
    Ptrl->URegion.Num = 0;
    p = Ptrl;
    while (1)
    {
        CList head = (CList)malloc(sizeof(struct CNode));
        head->Tag = 0;
        head->Down = head;
        head->Right = head;
        if (p->Tag == 2)
        {
            p->Down = head;
            p->Right = head;
            p = p->Right;
        }
        else
        {
            p->URegion.Next = head;
            p = p->URegion.Next;
        }
        i++;
        if (i > row && i > col)
        {
            p->URegion.Next = Ptrl;
            break;
        }   
    }
    return Ptrl;
}

void PrintList(CList Ptrl)
{
    int i, j;
    CList p = Ptrl->Right, q;
    for (i = 0; i < Ptrl->Row; i++)
    {
        q = p->Down;
        for (j = 0; j < Ptrl->Col; j++)
        {
            if (q != p && q->Row == i && q->Col == j)
            {
                printf("%.2f ", q->URegion.Value);
                q = q->Down;
            }
            else
            {
                printf("%d ", 0);
            }     
        }
        printf("\n");
        p = p->URegion.Next;
    }
}

CList Findij(int i, int j, CList Ptrl)
{
    CList p = Ptrl;
    int l = 0;
    while (p != NULL && l <= i)
    {
        p = p->URegion.Next;
        l++;
    }
    if (l != i)
    {
        return NULL;
    }
    else
    {
        l = 0;
        while (p != NULL && l <= j)
        {
            p = p->Down;
        }
        if (l == j)
        {
            return p;
        }
        else
        {
            return NULL;
        }
    }
}

CList Insert(int i, int j, double X, CList Ptrl) //向(i, j)填入X
{
    int ij_max = max(i, j), l = 0;
    CList p = Ptrl->Right;
    while (l <= ij_max)
    {
        if (p->URegion.Next == Ptrl)
        {
            CList newhead = (CList)malloc(sizeof(struct CNode));
            newhead->Tag = 0;
            p->URegion.Next = newhead;
        }
        if (l == i)
        {

        }
        p = p->URegion.Next;
    }
    if (ij_max > max(Ptrl->Row, Ptrl->Col))
    {
        p->URegion.Next = Ptrl;
    }

    return Ptrl;
}

int main()
{
    CList Ptrl = Init(3, 4);
    PrintList(Ptrl);
    return 0;
}