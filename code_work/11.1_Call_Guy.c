// 散列查找的应用

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MaxN 200000

// 哈希表相关定义
typedef struct Node
{
    char Phone[12]; // 存储电话号码
    int Count; // 记录通话次数
    struct Node *Next;
} * PtrToNode;

typedef struct HNode
{
    int P;
    PtrToNode List[MaxN];
} *HashTable;

int NextPrime(int N)
{
    int p = (N + 1) / 2 * 2 + 1, i; // 即为大于N的第一个奇数
    while (1)
    {
        for (i = (int)sqrt(p); i > 2; i--)
        {
            if (!(p % i)) // 若p可以被i整除。即不是素数
            {
                break;
            }
        }
        if (i == 2) // 正常结束循环，即p为素数
        {
            break;
        }
        else
        {
            p += 2;
        }
    }
    return p;
}

PtrToNode NewNode()
{
    PtrToNode newnode = malloc(sizeof(struct Node));
    newnode->Count = 1;
    newnode->Phone[0] = '\0';
    newnode->Next = NULL;
    return newnode;
}

HashTable CreateHashTable(int N)
{
    HashTable H = malloc(sizeof(struct HNode));
    H->P = NextPrime(N);
    for (int i = 0; i < H->P; i++)
    {
        H->List[i] = NewNode();
    }
    return H;
}

int Hash(int key, int Size)
{
    return (key % Size);
}

void FindAndInsert(HashTable H, char s[])
{
    int key = atoi(s + 6);
    PtrToNode head = H->List[Hash(key, H->P)], ptr = head->Next;
    while (ptr) // 若head中有元素，则寻找相同号码
    {
        if (strcmp(ptr->Phone, s) == 0) // 即字符串相同
        {
            ptr->Count++;
            break;
        }
        ptr = ptr->Next;
    }
    if (!ptr) // 即没有找到相同的号码，或者一开始就没有元素
    {
        ptr = NewNode();
        ptr->Next = head->Next;
        strcpy(ptr->Phone, s);
        head->Next = ptr;
    }
}

// 输入输出相关函数
void Read(HashTable H, int N) // 读取N个数据
{
    char s[12];
    for (int i = 0; i < N; i++)
    {
        scanf("%s", s);
        FindAndInsert(H, s);
    }
}

void ScanAndOutput(HashTable H) // 找出电话狂人并输出
{
    char MaxPhone[12];
    int MaxCount = 0;
    int PersonNum = 0;
    PtrToNode ptr;
    for (int i = 0; i < H->P; i++)
    {
        ptr = H->List[i]->Next;
        while (ptr)
        {
            if (ptr->Count > MaxCount)
            {
                strcpy(MaxPhone, ptr->Phone);
                MaxCount = ptr->Count;
                PersonNum = 1;
            }
            else if (ptr->Count == MaxCount)
            {
                PersonNum++;
                if (strcmp(MaxPhone, ptr->Phone) > 0) // 说明str1 > str2
                {
                    strcpy(MaxPhone, ptr->Phone);
                }
            }
            ptr = ptr->Next;
        }
    }
    printf("%s %d", MaxPhone, MaxCount);
    if (PersonNum > 1)
    {
        printf(" %d", PersonNum);
    }
    printf("\n");
}

int main()
{
    int N;
    scanf("%d", &N);
    HashTable H = CreateHashTable(2 * N);
    Read(H, N * 2);
    ScanAndOutput(H);
    return 0;
}