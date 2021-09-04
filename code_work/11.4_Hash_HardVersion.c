// 哈希表线性试探问题的逆推，若结果不唯一，优先取小的数字
/* 1. Hash(X) = index，说明恰好放在对应位置
   2. Hash(X) != index，说明是线性试探的结果
   3. 是拓扑排序的应用 */

#include <stdio.h>
#include <stdlib.h>

#define MaxN 1000

int G[MaxN][MaxN]; // 定义图
int A[MaxN], H[MaxN]; // 定义存储散列的数组
int N;

void InitGraph()
{
   for (int i = 0; i < N; i++)
   {
      for (int j = 0; j < N; j++)
      {
         G[i][j] = 0; // 用0表示没有链接
      }
   }
}

int HashFunc(int X)
{
   if (X >= 0)
   {
      return X % N;
   }
   else
   {
      return -1;
   }
}

void Read()
{
   for (int i = 0; i < N; i++)
   {
      scanf("%d", &A[i]);
      H[i] = HashFunc(A[i]);
   }
}

void BuildGraph()
{
   InitGraph();
   for (int i = 0; i < N; i++)
   {
      if (H[i] < 0)
      {
         G[i][i] = -1;
         continue;
      }
      if (H[i] != i) // 即哈希值不同于位置
      {
         int M = (i - H[i] + N) % N;
         for (int j = 1; j <= M; j++)
         {
            G[(i - j + N) % N][i] = 1;
         }
      }
      else
      {
         G[i][i] = 1;
      }
   }
}

int GetMinIndex(int Indegree[]) // 返回入度为零的点中最小的序号，不存在则返回-1
{
   int min = -1, min_index = -1;
   for (int i = 0; i < N; i++)
   {
      if (Indegree[i] == 0)
      {
         if (min == -1 || A[i] < min)
         {
            min = A[i];
            min_index = i;
         }
      }
   }
   return min_index;
}

void TopSort()
{
   int Indegree[MaxN] = {0};
   for (int j = 0; j < N; j++)
   {
      for (int i = 0; i < N; i++)
      {
         if (i == j && G[i][j] == -1) //指空的结点
         {
            Indegree[j] = -1;
         }
         if (i != j && G[i][j])
         {
            Indegree[j]++;
         }
      }
   }
   int flag = 0;
   while (1)
   {
      int V = GetMinIndex(Indegree);
      if (V == -1)
      {
         break;
      }
      Indegree[V] = -1;

      if (!flag)
      {
         flag = 1;
      }
      else
      {
         printf(" ");
      }
      printf("%d", A[V]);

      for (int W = 0; W < N; W++)
      {
         if (Indegree[W] > 0 && G[V][W])
         {
            Indegree[W]--;
         }
      }
   }

}

int main()
{
   scanf("%d", &N);
   Read();
   BuildGraph();
   TopSort();
   return 0;
}