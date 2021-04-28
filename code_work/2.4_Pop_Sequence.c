#include <stdio.h>
#include <stdlib.h>

/*思路：以1~n通过堆栈形成的数字序列，倒序后，一定能通过该堆栈重新得到n~1的序列*/

#define MAXN 1000

typedef struct StackNode *Stack;
struct StackNode
{
    int Data[MAXN];
    int Top;
};

void Push(int A, Stack S)
{
    S->Data[++(S->Top)] = A;
}

int Pop(Stack S)
{
    if (S->Top == -1)
    {
        return 0;
    }
    else
    {
        return S->Data[(S->Top)--];
    }
}

int Check(int A[], int M, int N)
{
    Stack S;
    int j = 0, i = N;
    S = (Stack)malloc(sizeof(struct StackNode));
    S->Top = -1;
    for (; i >= 1; i--)
    {
        while (1)
        {
            if (S->Top != -1 && S->Data[S->Top] == i)
            {
                int x = Pop(S);
                printf("pop:%d ", x);
                break;
            }
            if (j == N)
            {
                free(S);
                return 0;
            }
            if (A[j] != i && S->Top != M - 1)
            {
                Push(A[j], S);
                j++;
                continue;
            }
            if (A[j] == i && S->Top != M - 1)
            {
                printf("list:%d ", A[j]);
                j++;
                break;
            }
            else
            {
                free(S);
                return 0;
            }
        }
    }
    free(S);
    return 1;
}

void ReadSeq(int N, int *A)
{
    while (N--)
    {
        scanf("%d", A + N);
    }
}

void PrintA(int A[], int N)
{
    printf("A[%d] = ", N);
    for (int i = 0; i < N; i++)
    {
        printf(" %d", A[i]);
    }
    printf("\n");
}

int main()
{
    int M, N, K, A[MAXN];
    scanf("%d %d %d", &M, &N, &K);
    for (int i = 0; i < K; i++)
    {
        ReadSeq(N, A);
        // PrintA(A, N);
        if (Check(A, M, N))
        {
            printf("YES\n");
        }
        else
        {
            printf("NO\n");
        }
    }
        
}