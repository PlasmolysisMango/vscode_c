#include <stdio.h>
#include <stdlib.h>

typedef struct ChainList *List;
typedef int Address;
struct ChainList
{
    Address Addr;
    int Data;
    Address Next;
};

//思路：利用堆栈加二分查找的方法，避免对链表的重复修改。

