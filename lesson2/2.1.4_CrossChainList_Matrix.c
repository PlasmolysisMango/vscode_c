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
        q = p->Right;
        for (j = 0; j < Ptrl->Col; j++)
        {
            if (q != p && q->Row == i && q->Col == j)
            {
                printf("%2.1f ", q->URegion.Value);
                q = q->Right;
            }
            else
            {
                printf("%3d ", 0);
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

void Insert(int i, int j, double X, CList Ptrl) //向(i, j)填入X
{
    int l = 0;
    CList p = Ptrl->Right, q, term = NULL;
    if (i >= Ptrl->Row || j >= Ptrl->Col || i < 0 || j < 0)
    {
        printf("插入位置有误！\n");
        return;
    }
    while (p != Ptrl)
    {
        if (l == i || l == j)
        {
            if (term == NULL)
            {
                // printf("term指针：%p\n", term);
                term = (CList)malloc(sizeof(struct CNode));
                term->Row = i;
                term->Col = j;
                term->Tag = 1;
                term->URegion.Value = X;
            }
            if (l == i)
            {
                q = p;
                while (1)
                {
                    if ((q == p && j < q->Right->Col) || 
                    (j > q->Col && j < q->Right->Col) || 
                    (j > q->Col && q->Right == p) || 
                    (q == p && q->Right == p))
                    {
                        term->Right = q->Right;
                        q->Right = term;
                        break;
                    }
                    q = q->Right;
                    if (q == p)
                    {
                        printf("插入位置有误！\n");
                        return;
                    }
                }
            }
            if (l == j)
            {
                q = p;
                while (1)
                {
                    if ((q == p && i < q->Down->Row) || 
                    (i > q->Row && i < q->Down->Row) || 
                    (i > q->Row && q->Down == p) || 
                    (q == p && q->Down == p))
                    {
                        term->Down = q->Down;
                        q->Down = term;
                        break;
                    }
                    q = q->Down;
                    if (q == p)
                    {
                        printf("插入位置有误！\n");
                        return;
                    }
                }
            }
        }
        p = p->URegion.Next;
        l++;
    }
    Ptrl->URegion.Num++;
    return;
}

void Delete(int i, int j, CList Ptrl)
{
    int l = 0;
    CList p = Ptrl->Right, q, s = NULL;
    while (p != Ptrl)
    {
        if (l == i)
        {
            q = p;
            while (1)
            {
                if (q->Right->Col == j)
                {
                    s = q->Right;
                    q->Right = s->Right;
                    break;
                }
                q = q->Right;
                if (q == p)
                {
                    printf("未找到对应元素！\n");
                    return;
                }
            }
        }
        if (l == j)
        {
            q = p;
            while (1)
            {
                if (q->Down->Row == i)
                {
                    s = q->Down;
                    q->Down = s->Down;
                    break;
                }
                q = q->Right;
                if (q == p)
                {
                    printf("未找到对应元素！\n");
                    return;
                }
            }
        }
        p = p->URegion.Next;
        l++;
    }
    if (s)
    {
        free(s);
        Ptrl->URegion.Num--;
    }
    return;
}

int main()
{
    CList Ptrl = Init(3, 4);
    // PrintList(Ptrl);
    Insert(0, 0, 1.2, Ptrl);
    Insert(0, 1, 2.3, Ptrl);
    Insert(1, 1, 5.5, Ptrl);
    Insert(2, 3, 15.5, Ptrl);
    Delete(2, 3, Ptrl);
    PrintList(Ptrl);
    printf("Num = %d\n", Ptrl->URegion.Num);
    return 0;
}