#include <stdio.h>
#include <stdlib.h>

#define MAXN 10
typedef char ElementType;
#define Null -1

typedef struct TreeNode Tree;
struct TreeNode
{
    ElementType Data;
    int left;
    int right;
} T1[MAXN], T2[MAXN];

int BuildTree(Tree T[])
{
    int N, Root = 0;
    ElementType cl, cr;
    scanf("%d\n", &N);
    for (int i = 0; i < N; i++)
    {
        Root += i;
        scanf("%c %c %c\n", &T[i].Data, &cl, &cr);
        if (cl != '-')
        {
            T[i].left = cl - '0';
            Root -= T[i].left;
        }
        else
        {
            T[i].left = Null;
        }
        if (cr != '-')
        {
            T[i].right = cr - '0';
            Root -= T[i].right;
        }
        else
        {
            T[i].right = Null;
        }
    }
    return Root;
}

int isOmorphic(int R1, int R2)
{
    if ((R1 == Null) && (R2 == Null))
    {
        return 1;
    }
    if (((R1 == Null) && (R2 != Null)) || ((R1 != Null) && (R2 == Null)))
    {
        return 0;
    }
    if (T1[R1].Data != T2[R2].Data)
    {
        return 0;
    }
    if ((T1[R1].left == Null) && (T2[R2].left == Null))
    {
        return isOmorphic(T1[R1].right, T2[R2].right);
    }
    if (((T1[R1].left != Null) && (T2[R2].left != Null) && 
    (T1[T1[R1].left].Data) == (T2[T2[R2].left].Data)))
    {
        return (isOmorphic(T1[R1].left, T2[R2].left) &&
                isOmorphic(T1[R1].right, T2[R2].right));
    }
    else
    {
        return (isOmorphic(T1[R1].left, T2[R2].right) &&
                isOmorphic(T1[R1].right, T2[R2].left));
    }
}