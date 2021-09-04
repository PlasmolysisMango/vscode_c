// QQ号码为一个不超过10位、但大于1000（据说QQ老总的号码是1001）的整数。密码为不小于6位、不超过16位、且不包含空格的字符串。

/* 针对每条指令，给出相应的信息：
1）若新申请帐户成功，则输出“New: OK”；
2）若新申请的号码已经存在，则输出“ERROR: Exist”；
3）若老帐户登陆成功，则输出“Login: OK”；
4）若老帐户QQ号码不存在，则输出“ERROR: Not Exist”；
5）若老帐户密码错误，则输出“ERROR: Wrong PW”。 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MaxN 30000

// 哈希表相关定义
typedef struct Node
{
    char Account[11]; // 存储QQ号，使用字符串避免超出数字范围
    char Password[17]; // 存储密码
    struct Node *Next;
} * PtrToNode;

typedef struct HNode
{
    int TSize;
    PtrToNode Head[MaxN];
} *HashTable;

int NextPrime(int N)
{
    if (N == 1)
    {
        return 2;
    }
    int p = (N % 2) ? N + 2 : N + 1, i; // 即为大于N的第一个奇数
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
    newnode->Account[0] = newnode->Password[0] = '\0';
    newnode->Next = NULL;
    return newnode;
}

HashTable CreateHashTable(int N)
{
    HashTable H = malloc(sizeof(struct HNode));
    H->TSize = NextPrime(N);
    for (int i = 0; i < MaxN; i++)
    {
        H->Head[i] = NewNode();
    }
    return H;
}

int Hash(char key[], int TSize) // 哈希函数定义为折叠累加法，从结尾每4位叠加一次
{
    int length = strlen(key), index = 0;
    char tmp[5];
    while (length > 4)
    {
        strncpy(tmp, key + length - 4, 4);
        tmp[4] = '\0';
        // printf("%s\n", tmp);
        index += atoi(tmp);
        length -= 4;
    }
    strncpy(tmp, key, length);
    tmp[length] = '\0';
    // printf("%s\n", tmp);
    index += atoi(tmp);
    return index;
}

PtrToNode Find(HashTable H, int index, char key[]) // 返回对应账户的结构指针，没找到则返回NULL
{
    PtrToNode ptr = H->Head[index]->Next;
    while (ptr)
    {
        if (strcmp(ptr->Account, key) == 0)
        {
            break;
        }
        ptr = ptr->Next;
    }
    return ptr;
}

void Insert(HashTable H, int index, char account[], char password[])
{
    PtrToNode newnode = NewNode();
    strcpy(newnode->Account, account);
    strcpy(newnode->Password, password);
    newnode->Next = H->Head[index]->Next;
    H->Head[index]->Next = newnode;
}

void Handle(HashTable H, int N) // 处理N条指令
{
    char cmd, account[11], password[17];
    PtrToNode ptr;
    int index;
    while (N--)
    {
        scanf("\n%c %s %s", &cmd, account, password);
        index = Hash(account, H->TSize);
        ptr = Find(H, index, account);
        if (cmd == 'N') // 新建账户的情况
        {
            if (!ptr) // 即没找到账户，可以顺利新建
            {
                Insert(H, index, account, password);
                printf("New: OK\n");
            }
            else
            {
                printf("ERROR: Exist\n");
            }
        }
        else // 登录账户的情况
        {
            if (!ptr) // 即账户不存在
            {
                printf("ERROR: Not Exist\n");
            }
            else if (strcmp(ptr->Password, password) != 0) // 即密码错误
            {
                printf("ERROR: Wrong PW\n");
            }
            else
            {
                printf("Login: OK\n");
            }
        }
    }
}

int main()
{
    int N;
    scanf("%d", &N);
    HashTable H = CreateHashTable(N);
    Handle(H, N);
    return 0;
}