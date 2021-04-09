// 线性表的顺序存储实现
#include <stdio.h>
#include <stdlib.h>

#define MAXN 10

typedef struct LNode *List;
struct LNode
{
    double Data[MAXN];
    int Last;
};

List EmptyList()
{
    List Ptrl = (List)malloc(sizeof(struct LNode));
    Ptrl->Last = -1;
    return Ptrl;
}

int Length(List Ptrl)
{
    return Ptrl->Last + 1;
}

int Find(double X, List Ptrl)
{
    int i = 0;
    while (i <= Ptrl->Last && Ptrl->Data[i] != X)
    {
        i++;
    }
    if (i > Ptrl->Last)
    {
        return -1;
    }
    else
    {
        return i;
    }
}

void Insert(double X, int i, List Ptrl)
{
    int j;
    if (Ptrl->Last >= MAXN - 1)
    {
        printf("表满");
        return;
    }
    if (i < 1 || i > Ptrl->Last + 2)
    {
        printf("位置有误");
        return;
    }
    for (j = Ptrl->Last; j >= i - 1; j--)
    {
        Ptrl->Data[j + 1] = Ptrl->Data[j];
    }
    Ptrl->Data[i - 1] = X;
    Ptrl->Last++;
    return;
}

void Delete(int i, List Ptrl)
{
    int j;
    if (Ptrl->Last == -1)
    {
        printf("表空");
        return;
    }
    if (i < 1 || i > Ptrl->Last + 1)
    {
        printf("不存在第%d个元素", i);
        return;
    }
    for (j = i - 1; j <= Ptrl->Last - 1; j++)
    {
        Ptrl->Data[j] = Ptrl->Data[j + 1];
    }
    Ptrl->Last--;
    return;
}

void PrintList(List Ptrl)
{
    for (int i = 0; i <= Ptrl->Last; i++)
    {
        printf("第%d个元素：%.2f\n", i + 1, Ptrl->Data[i]);
    }
    return;
}

int main()
{
    List Ptrl = EmptyList();
    Insert(1.2, 1, Ptrl);
    PrintList(Ptrl);
    Insert(2.3, 1, Ptrl);
    PrintList(Ptrl);
    Delete(2, Ptrl);
    PrintList(Ptrl);
}