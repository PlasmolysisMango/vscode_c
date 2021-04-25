#include <stdio.h>
#include <stdlib.h>

#define ERROR 0

typedef struct PolyNode *Polynomial;
struct PolyNode
{
    int coef; // 系数
    int expon; // 指数
    struct PolyNode *link;
};

void Attach(int coef, int expon, Polynomial *rear) // 为了修改rear指针的值，必须传递指向rear指针的指针
{
    Polynomial newcell;
    newcell = (Polynomial)malloc(sizeof(struct PolyNode));
    newcell->coef = coef;
    newcell->expon = expon;
    newcell->link = NULL;
    (*rear)->link = newcell;
    *rear = newcell;
}

Polynomial PolyAdd(Polynomial P1, Polynomial P2)
{
    Polynomial front, rear, temp;
    int sum;
    rear = (Polynomial)malloc(sizeof(struct PolyNode));
    front = rear;
    while (P1 && P2)
    {
        if (P1->expon > P2->expon)
        {
            Attach(P1->coef, P1->expon, &rear);
            P1 = P1->link;
            continue;
        }
        if (P1->expon < P2->expon)
        {
            Attach(P2->coef, P2->expon, &rear);
            P2 = P2->link;
            continue;
        }
        if (P1->expon == P2->expon)
        {
            sum = P1->coef + P2->coef;
            if (sum)
            {
                Attach(sum, P1->expon, &rear);
            }
            P1 = P1->link;
            P2 = P2->link;
            continue;
        }
    }
    for (; P1; P1 = P1->link)
    {
        Attach(P1->coef, P1->expon, &rear);
    }
    for (; P2; P2 = P2->link)
    {
        Attach(P2->coef, P2->expon, &rear);
    }
    rear->link = NULL;
    temp = front;
    front = front->link;
    free(temp);
    return front;
}

Polynomial CreatePoly()
{
    Polynomial PtrP;
    PtrP = (Polynomial)malloc(sizeof(struct PolyNode));
    PtrP->link = NULL;
    PtrP->coef = 0;
    PtrP->expon = 0;
    return PtrP;
}

void PrintPoly(Polynomial PtrP)
{
    Polynomial p = PtrP;
    while (p && p->coef)
    {
        if (p->coef > 0)
        {
            printf("+");
        }
        else
        {
            printf("-");
        }
        printf("%dX^%d", abs(p->coef), p->expon);
        p = p->link;
    }
    printf("\n");
}

void AddItem(int coef, int expon, Polynomial *PtrP)
{
    Polynomial newitem;
    newitem = (Polynomial)malloc(sizeof(struct PolyNode));
    newitem->coef = coef;
    newitem->expon = expon;
    newitem->link = NULL;
    *PtrP = PolyAdd(*PtrP, newitem);
}

Polynomial PolyMulti(Polynomial P1, Polynomial P2)
{
    Polynomial front, rear, temp;
    int sum;
    rear = (Polynomial)malloc(sizeof(struct PolyNode));
    front = rear;
    while (P1 && P2)
    {
        
    }
}

int main()
{
    Polynomial P1, P2, add;
    P1 = CreatePoly();
    P2 = CreatePoly();
    for (int i = 0; i < 5; i++)
    {
        AddItem(-(i + 1), i + 1, &P1);
        AddItem(i + 3, i + 2, &P2);
    }
    PrintPoly(P1);
    PrintPoly(P2);
    add = PolyAdd(P1, P2);
    PrintPoly(add);
}