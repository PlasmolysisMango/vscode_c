#include <stdio.h>
#include <stdlib.h>

#define MaxN 30

int Pre[30], In[30];

int Tree[30];

int N;

void Build(int in_left, int pre_left, int length, int index) // 0 0 N 0
{
    if (index > N - 1 || length <= 0)
    {
        return;
    }
    Tree[index] = Pre[pre_left];
    int i;
    for (i = 0; i < length; i++)
    {
        if (Tree[index] == In[i + in_left])
        {
            break;
        }
    }
    // i 即为左序列长度， Length - i - 1即为右序列长度
    Build(in_left, pre_left + 1, i, 2 * index + 1);
    Build(in_left + i + 1, pre_left + i + 1, length - i - 1, 2 * index + 2);
}

void Read()
{
    scanf("%d", &N);
    for (int i = 0; i < N * 2; i++)
    {
        if (i < N)
        {
            scanf("%d", &In[i]);
        }
        else
        {
            scanf("%d", &Pre[i - N]);
        }
    }
    Build(0, 0, N, 0);
}

int main()
{
    Read();
    return 0;
}
