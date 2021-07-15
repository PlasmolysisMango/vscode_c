#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define JUMP 10
#define MaxSize 50
#define MaxN (MaxSize * 2)^2

typedef struct PositionPoint *Position;
struct PositionPoint
{
    int x, y;
    int visited;
};

Position NewPosistion()
{
    Position P = (Position)malloc(sizeof(struct PositionPoint));
    P->x = P->y = 0;
    P->visited = 0;
    return P;
}

int isSafe(Position P) //判断是否可以直接上岸
{
    if (abs(P->x) + JUMP >= MaxSize || abs(P->y) + JUMP >= MaxSize)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int inRange(Position P1, Position P2) //判断P1 P2是否可以跳跃通过
{
    if (pow(P1->x - P2->x, 2) + pow(P1->y - P2->y, 2) <= pow(JUMP, 2))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int DFS(Position Start, Position Plist[], int N) //DFS的思路来找到出口
{
    int ans;
    Start->visited = 1;
    if (isSafe(Start))
    {
        ans = 1;
    }
    else
    {
        for (int i = 0; i < N; i++)
        {
            if (!Plist[i]->visited && inRange(Start, Plist[i]))
            {
                ans = DFS(Plist[i], Plist, N);
                if (ans)
                {
                    break;
                }
            }
        }
    }
    return ans;
}

void ReadList(Position *Plist, int N) //读入范围内的所有点
{
    for (int i = 0; i < N; i++)
    {
        Plist[i] = NewPosistion();
        scanf("%d %d", &Plist[i]->x, &Plist[i]->y);
    }
}

int main()
{
    int N;
    scanf("%d", &N);
    Position *Plist = malloc(MaxN * sizeof(Position)), Start = NewPosistion(); //起点为0 0
    ReadList(Plist, N);
    if (DFS(Start, Plist, N))
    {
        printf("YES\n");
    }
    else
    {
        printf("NO\n");
    }
    return 0;
}


