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
    int K, A[MAXN], sum = 0, maxsum = 0;
    scanf("%d", &K);
    get_input_array(K, A);
    for (int i = 0; i < K; i++)
    {
        sum = sum + A[i];
        if (sum < 0)
        {
            sum = 0;
            continue;
        }
        if (sum > maxsum)
        {
            maxsum = sum;
        }
    }
    printf("%d", maxsum);
}


