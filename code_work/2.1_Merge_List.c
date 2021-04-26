#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node 
{
    ElementType Data;
    PtrToNode   Next;
};
typedef PtrToNode List;

List Read(); /* 细节在此不表 */
void Print( List L ); /* 细节在此不表；空链表将输出NULL */

List Merge( List L1, List L2 );

int main()
{
    List L1, L2, L;
    L1 = Read();
    // Print(L1);
    L2 = Read();
    // Print(L2);
    L = Merge(L1, L2);
    Print(L);
    Print(L1);
    Print(L2);
    return 0;
}

List Read()
{
    int N;
    List L, Rear, newnode;
    L = (List)malloc(sizeof(struct Node));
    Rear = L;
    scanf("%d", &N);
    while (N--)
    {
        newnode = (List)malloc(sizeof(struct Node));
        scanf("%d", &newnode->Data);
        newnode->Next = NULL;
        Rear->Next = newnode;
        Rear = newnode;
    }
    return L;
}

void Print(List L)
{
    if (!L->Next || !L)
    {
        printf("NULL\n");
    }
    else
    {
        int flag = 0;
        while (L->Next)
        {
            if (!flag)
            {
                flag = 1;
            }
            else
            {
                printf(" ");
            }
            printf("%d", L->Next->Data);
            L = L->Next;
        }
        printf("\n");
    }
}

//3 1 3 5 5 2 4 6 8 10
List Merge( List L1, List L2 )
{
    List L, Rear;
    L = (List)malloc(sizeof(struct Node));
    Rear = L;
    while ((L1 && L2) && (L1->Next && L2->Next))
    {
        if (L1->Next->Data >= L2->Next->Data)
        {
            Rear->Next = L2->Next;
            Rear = L2->Next;
            L2->Next = L2->Next->Next;
        }
        else
        {
            Rear->Next = L1->Next;
            Rear = L1->Next;
            L1->Next = L1->Next->Next;
        }
    }
    while (L1 && L1->Next)
    {
        Rear->Next = L1->Next;
        Rear = L1->Next;
        L1->Next = L1->Next->Next;
    }
    while (L2 && L2->Next)
    {
        Rear->Next = L2->Next;
        Rear = L2->Next;
        L2->Next = L2->Next->Next;
    }
    return L;
}