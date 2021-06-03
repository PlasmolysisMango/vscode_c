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

typedef char Code[MaxLenth + 1]; //用于读入Huffman编码

typedef int Frequence; //用于存储字符出现的频率

void BubbleSort(Frequence *F, int N) //用于排序频率序列
{
    for (int i = 0; i < N - 1; i++)
    {
        for (int j = 0; j < N - i - 1; j++)
        {
            if (F[j] < F[j + 1])
            {
                int temp = F[j];
                F[j] = F[j + 1];
                F[j + 1] = temp;
            }
        }
    }
}

HuffmanTree NewNode()
{
    HuffmanTree newnode = malloc(sizeof(struct TreeNode));
    newnode->Left = newnode->Right = NULL;
    return newnode;
}

