#include <stdio.h>

#define MAXN 200000

void get_input_array(int K, int *A)
{
    for (int i = 0; i < K; i++)
    {
        scanf("%d", &A[i]);
    }
}

int main()
{
    int K = 3, A[MAXN];
    get_input_array(K, A);
    for (int i = 0; i < K; i++)
    {
        printf("%d\n", A[i]);
    }
    return 0;
}


