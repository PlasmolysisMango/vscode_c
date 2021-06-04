/* 1. WPL最小，即与哈夫曼树的WPL相同；
   2. 满足前缀码；
   3. 无度为1的结点（满足1、2自动满足）；
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxLenth 63
#define MaxM 1000

typedef struct TreeNode //用于存储Huffman树
{
    struct TreeNode *Left;
    struct TreeNode *Right;
} *HuffmanTree;

typedef int Frequence; //用于存储字符出现的频率

typedef struct HeapNode
{
    Frequence *Freq;
    int Size;
} * MinHeap;

MinHeap CreateHeap()
{
    MinHeap H = malloc(sizeof(struct HeapNode));
    H->Freq = malloc((MaxLenth + 1) * sizeof(Frequence));
    H->Freq[0] = H->Size = -1;
    return H;
}

HuffmanTree NewNode()
{
    HuffmanTree newnode = malloc(sizeof(struct TreeNode));
    newnode->Left = newnode->Right = NULL;
    return newnode;
}

