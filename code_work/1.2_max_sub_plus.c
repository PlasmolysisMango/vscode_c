#include <stdio.h>

#define MAXN 20000

void get_input_array(int K, int *A)
{
    for (int i = 0; i < K; i++)
    {
        scanf("%d", &A[i]);
    }
}

int main()
{
    int K, A[MAXN], sum = 0, maxsum = -1;
    scanf("%d", &K);
    get_input_array(K, A);
    int start = A[0], stop = 0, maxstart = A[0];
    A[K] = 0;
    for (int i = 0; i < K; i++)
    {
        sum = sum + A[i];
        if (sum < 0)
        {
            sum = 0;
            start = A[i + 1];
            continue;
        }
        if (sum > maxsum)
        {
            maxsum = sum;
            maxstart = start;
            stop = A[i];
        }
    }
    if (maxsum >= 0)
    {
        printf("%d %d %d", maxsum, maxstart, stop);
    }
    else
    {
        printf("%d %d %d", 0, A[0], A[K - 1]);
    }
    
}


