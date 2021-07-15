#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MaxN 100

int JUMPD;
int N;

typedef struct VNode
{
    int x, y;
} Vertex;


Vertex Vlist[MaxN];
int visited[MaxN];

void Initvisit()
{
    for (int i = 0; i < N; i++)
    {
        visited[i] = 0;
    }
}

int isRound(Vertex V1, Vertex V2, double Distance)
{
    return (pow((V1.x - V2.x), 2) + pow((V1.y - V2.y), 2) <= pow(Distance, 2));
}

int isFirstJump(Vertex V)
{
    Vertex V0;
    V0.x = V0.y = 0;
    return isRound(V0, V, 7.5 + JUMPD);
}

int isSafe(Vertex V)
{
    return (abs(V.x) + JUMPD >= 50 || abs(V.y) + JUMPD >= 50);
}

int DFS(int index)
{
    visited[index] = 1;
    int ans = 0;
    if (isSafe(Vlist[index]))
    {
        return ans = 1;
    }
    for (int i = 0; i < N; i++)
    {
        if (!visited[i] && isRound(Vlist[index], Vlist[i], JUMPD))
        {
            ans = DFS(i);
            if (ans)
            {
                break;
            }
        }
    }
    return ans;
}

int main()
{
    scanf("%d %d", &N, &JUMPD);
    for (int i = 0; i < N; i++)
    {
        scanf("%d %d", &Vlist[i].x, &Vlist[i].y);
    }
    Initvisit();
    int ans;
    for (int i = 0; i < N; i++)
    {
        if (isFirstJump(Vlist[i]))
        {
            ans = DFS(i);
            if (ans)
            {
                break;
            }
        }
    }
    if (ans)
    {
        printf("Yes");
    }
    else
    {
        printf("No");
    }
}
