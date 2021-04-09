#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 10
#define NotFound 0
typedef int ElementType;

typedef int Position;
typedef struct LNode *List;
struct LNode
{
    ElementType Data[MAXSIZE];
    Position Last; /* 保存线性表中最后一个元素的位置 */
};

List ReadInput(); /* 裁判实现，细节不表。元素从下标1开始存储 */
Position BinarySearch(List L, ElementType X);
void PrintList(List L);

int main()
{
    List L;
    ElementType X;
    Position P;

    L = ReadInput();
    // PrintList(L);
    scanf("%d", &X);
    P = BinarySearch( L, X );
    printf("%d\n", P);

    return 0;
}

void PrintList(List L)
{
    for (int i = 1; i <= L->Last; i++)
    {
        printf("%d\n", L->Data[i]);
    }
    return;
}

List ReadInput()
{
    List L;
    L = (List)malloc(sizeof(struct LNode));
    L->Last = 0;
    do
    {
        scanf("%d", &L->Data[L->Last + 1]);
        L->Last++;
    } while (getchar() != '\n');
    return L;
}

Position BinarySearch(List L, ElementType X)
{
    // ElementType s;
    // for (Position i = 1; i < L->Last; i++)
    // {
    //     for (Position j = i; j < L->Last; j++)
    //     {
    //         if (L->Data[j] > L->Data[j + 1])
    //         {
    //             s = L->Data[j + 1];
    //             L->Data[j + 1] = L->Data[j];
    //             L->Data[j] = s;
    //         }
    //     }
    // }
    Position left = 1, right = L->Last, mid;
    while (left <= right)
    {
        mid = (int)((left + right) / 2);
        if (mid < 1 || mid > L->Last)
        {
            break;
        }
        if (X > L->Data[mid])
        {
            left = mid + 1;
        }
        else if(X < L->Data[mid])
        {
            right = mid - 1;
        }
        else
        {
            return mid;
        }
    }
    return NotFound;
}