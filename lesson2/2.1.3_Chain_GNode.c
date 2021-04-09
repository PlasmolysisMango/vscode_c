// 广义表的多重链表实现

#include <stdio.h>
#include <stdlib.h>

#define MAXN 10

typedef struct GNode *GList;
struct GNode
{
    int Tag; // 标志域，0为单元素，1则为广义表
    union //子表指针域和单元素数据域共用存储空间
    {
        double Data;
        GList SubList;
    } URegion;
    GList Next; //指向后续结点
};

