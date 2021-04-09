// 线性表的链式实现
#include <stdio.h>
#include <stdlib.h>

#define MAXN 10

typedef struct LNode *List;
struct LNode
{
    double Data;
    List Next;
};

int Length(List Ptrl)
{
    List p = Ptrl;
    int j = 0;
    while (p)
    {
        p = p->Next;
        j++;
    }
    return j;
}

List FindKth(int K, List Ptrl)
{
    List p = Ptrl;
    int i = 1;
    while (p != NULL && i < K)
    {
        p = p->Next;
        i++;
    }
    if (i == K)
    {
        return p;
    }
    else
    {
        return NULL;
    }
}

List Find(double X, List Ptrl)
{
    List p = Ptrl;
    while (p != NULL && p->Data != X)
    {
        p = p->Next;
    }
    return p;
}

List Insert(double X, int i, List Ptrl)
{
    List p, s;
    if (i == 1)
    {
        s = (List)malloc(sizeof(struct LNode));
        s->Data = X;
        s->Next = Ptrl;
        return s;
    }
    p = FindKth(i - 1, Ptrl);
    if (p == NULL)
    {
        printf("序号i有误");
        return NULL;
    }
    else
    {
        s = (List)malloc(sizeof(struct LNode));
        s->Data = X;
        s->Next = p->Next;
        p->Next = s;
        return Ptrl;
    }
}

List Delete(int i, List Ptrl)
{
    List p, s;
    if (i == 1)
    {
        s = Ptrl;
        if (Ptrl != NULL)
        {
            Ptrl = Ptrl->Next;
        }
        else
        {
            return NULL;
        }
        free(s);
        return Ptrl;
    }
    p = FindKth(i - 1, Ptrl);
    if (p == NULL)
    {
        printf("第%d个结点不存在", i - 1);
        return NULL;
    }
    else if (p->Next == NULL)
    {
        printf("第%d个节点不存在", i);
        return NULL;
    }
    else
    {
        s = p->Next;
        p->Next = s->Next;
        free(s);
        return Ptrl;
    }
}

void PrintList(List Ptrl)
{
    List p = Ptrl;
    int i = 1;
    while (p)
    {
        printf("第%d个元素：%.2f\n", i, p->Data);
        i++;
        p = p->Next;
    }
    printf("\n");
}

int main()
{
    List Ptrl = NULL;
    for (int i = 1; i <= 5; i++)
    {
        Ptrl = Insert((double)i * 1.2, i, Ptrl);
    }
    PrintList(Ptrl);
    Ptrl = Delete(1, Ptrl);
    PrintList(Ptrl);
    Ptrl = Delete(4, Ptrl);
    PrintList(Ptrl);
}