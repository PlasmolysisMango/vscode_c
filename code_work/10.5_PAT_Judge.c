// 有三个关键字的排序，本质上是表排序的应用
// 1. 总分（非升序；2. 完美答题数量（非升序；3. 用户ID（非降序

#include <stdlib.h>
#include <stdio.h>

#define MaxN 10000 

typedef struct UNode // 结构体里存储的是可以在读取阶段得到的数据
{
    int t_score; // 总分
    int score[5]; // 各项分数
    int perfect_num; // 完美答题数量
} * UserType;

UserType User[MaxN]; // 用户数组
int Sort[MaxN]; // 排序数组

void Read(int N, int K, int M) // 用户数、题目数、提交数
{
    for (int i = 0; i < N; i++) // 初始化, User[]数组从零开始计
    {
        User[i] = malloc(sizeof(struct UNode));
        User[i]->t_score = 0; // 未提交任何答案或者所有提交均未通过，则总分为-1
        User[i]->perfect_num = 0;
        for (int j = 0; j < K; j++)
        {
            User[i]->score[j] = -2; // 未提交的题目成绩记为-2，提交但未通过记为-1
        }
    }

    int FullMark[5];
    for (int i = 0; i < K; i++) // 读取所有问题的分值
    {
        scanf("%d", &FullMark[i]); 
    }

    int id, problem_id, single_score;
    UserType p;
    for (int i = 0; i < M; i++) // 开始读取提交
    {
        scanf("%d %d %d", &id, &problem_id, &single_score); // single_score = [-1, fullmark]
        id--;
        problem_id--;
        p = User[id];
        if (single_score <= p->score[problem_id]) // 若提交的分数低于上次提交，则无需继续
        {
            continue;
        }
        p->score[problem_id] = single_score;
        // 由于总分可能变化，最后再统计
    }

    int ErrorNum;
    for (int i = 0; i < N; i++) // 统计总分及其他参数
    {
        p = User[i];
        ErrorNum = 0; // 记录未通过或者未提交的题目总数
        for (int j = 0; j < K; j++)
        {
            if (p->score[j] < 0)
            {
                ErrorNum++;
            }
            else
            {
                p->t_score += p->score[j];
                if (p->score[j] == FullMark[j]) // 即完美作答
                {
                    p->perfect_num++;
                }
            }
        }
        if (ErrorNum == K) // 即所有题目均未通过或者未提交
        {
            p->t_score = -1;
        }
    }
}

int _compar(const void *a, const void *b)
{
    int id1 = *(int *)a, id2 = *(int *)b;
    UserType p1 = User[id1], p2 = User[id2];
    if (p1->t_score != p2->t_score) // 总分不同
    {
        return p2->t_score - p1->t_score; // 总分非升序
    }
    else if (p1->perfect_num != p2->perfect_num) // 总分相同，完美答题数不同
    {
        return p2->perfect_num - p1->perfect_num; // 完美答题数非升序
    }
    else // 总分、完美答题数均相同，ID一定不相同
    {
        return id1 - id2;
    }
}

void TableSort(int N, int K) // 用户数、问题数
{
    for (int i = 0; i < N; i++)
    {
        Sort[i] = i; // 初始化排序数组
    }
    // 调用快速排序
    qsort(Sort, N, sizeof(int), _compar);

    // // 若要物理排序
    // UserType tmp_u;
    // for (int i = 0; i < N; i++)
    // {
    //     if (i != Sort[i]) // 即一个独立的环起点
    //     {
    //         int j = i;
    //         tmp_u = User[i];
    //         while (Sort[j] != i) // 当不是环的最后一个位置时
    //         {
    //             User[j] = User[Sort[j]];
    //             int next = Sort[j];
    //             Sort[j] = j;
    //             j = next;
    //         }
    //         User[j] = tmp_u;
    //         Sort[j] = j; // 防止死循环
    //     }
    // }

    UserType p;
    int old_rank = 0, old_t_score = 0, rank;
    for (int i = 0; i < N; i++)
    {
        p = User[Sort[i]]; 
        if (p->t_score < 0) // 即未通过或者未提交，直接进行下一次循环
        {
            continue;
        }
        if (p->t_score != old_t_score)
        {
            rank = i + 1;
        }
        else
        {
            rank = old_rank;
        }
        old_rank = rank;
        old_t_score = p->t_score;

        printf("%d %05d %d", rank, Sort[i] + 1, p->t_score);
        for (int j = 0; j < K; j++)
        {
            if (p->score[j] == -2) // 即未提交
            {
                printf(" -");
            }
            else if (p->score[j] == -1) // 即提交但未通过
            {
                printf(" 0");
            }
            else
            {
                printf(" %d", p->score[j]);
            }
        }
        printf("\n");
    }
}

int main()
{
    int N, K, M;
    scanf("%d %d %d", &N, &K, &M);
    Read(N, K, M);
    TableSort(N, K);
    return 0;
}