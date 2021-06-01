// 未验证
// 思路： I操作即为建立集合；C操作即为判断两个元素是否属于同一集合；如果所有元素都在一个集合，输出全部连接，否则输出已有的集合数量。
#include <stdio.h>
#include <stdlib.h>

#define MaxSize 10000

typedef int ComputerType;
typedef struct 
{
    ComputerType Data;
    int Parent;
} ElementType;

typedef struct SetType *Set;
struct SetType
{
    ElementType *Elements;
    int Size;
};

