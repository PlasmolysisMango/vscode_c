#include <stdio.h>
#include <stdlib.h>

typedef struct PolyNode *Polynomial;
struct PolyNode
{
    int coef;
    int expon;
    Polynomial link;
};

void Attach(int coef, int expon, Polynomial *rear) // 为了修改rear指针的值，必须传递指向rear指针的指针
{
    if (!coef)
    {
        return;
    }
    Polynomial newcell;
    newcell = (Polynomial)malloc(sizeof(struct PolyNode));
    newcell->coef = coef;
    newcell->expon = expon;
    newcell->link = NULL;
    (*rear)->link = newcell;
    *rear = newcell;
}

Polynomial ReadPoly()
{
    int N, c, e;
    Polynomial Rear, P, First;
    P = (Polynomial)malloc(sizeof(struct PolyNode));
    Rear = First = P;
    scanf("%d", &N);
    while (N--)
    {
        scanf("%d %d", &c, &e);
        Attach(c, e, &Rear);
    }
    P = First->link;
    free(First);
    return P;
}

void PrintPoly(Polynomial P)
{
    int flag = 0;
    if (!P)
    {
        printf("0 0");
        return;
    }
    else
    {
        while (P)
        {
            if (!flag)
            {
                flag = 1;
            }
            else
            {
                printf(" ");
            }
            printf("%d %d", P->coef, P->expon);
            P = P->link;
        }
    }
}

Polynomial Add(Polynomial P1, Polynomial P2)
{
    Polynomial P, First, Rear;
    P = (Polynomial)malloc(sizeof(struct PolyNode));
    Rear = First = P;
    while (P1 && P2)
    {
        if (P2->expon > P1->expon)
        {
            Attach(P2->coef, P2->expon, &Rear);
            P2 = P2->link;
        }
        else if (P2->expon < P1->expon)
        {
            Attach(P1->coef, P1->expon, &Rear);
            P1 = P1->link;
        }
        else if (P1->expon == P2->expon)
        {
            Attach(P1->coef + P2->coef, P1->expon, &Rear);
            P1 = P1->link;
            P2 = P2->link;
        }
    }
    while (P1)
    {
        Attach(P1->coef, P1->expon, &Rear);
        P1 = P1->link;
    }
    while (P2)
    {
        Attach(P2->coef, P2->expon, &Rear);
        P2 = P2->link;
    }
    P = First->link;
    free(First);
    return P;
}

Polynomial Mult(Polynomial P1, Polynomial P2)
{
    Polynomial P, q, Res = NULL;
    P = (Polynomial)malloc(sizeof(struct PolyNode));
    while (P1)
    {
        q = P2;
        while (q)
        {
            P->coef = P1->coef * q->coef;
            P->expon = P1->expon + q->expon;
            P->link = NULL;
            Res = Add(Res, P);
            q = q->link;
        }
        P1 = P1->link;
    }
    free(P);
    return Res;
}

int main()
{
    Polynomial P1, P2, PP, PS;

    P1 = ReadPoly();
    P2 = ReadPoly();
    PS = Add(P1, P2);
    PP = Mult(P1, P2);
    PrintPoly(PP);
    printf("\n");
    PrintPoly(PS);
    return 0;
}