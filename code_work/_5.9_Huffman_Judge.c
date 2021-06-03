#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MaxLenth 63

typedef struct TreeNode
{
    struct TreeNode *Left;
    struct TreeNode *Right;
} *HuffmanTree;

HuffmanTree NewNode()
{
    HuffmanTree newnode = malloc(sizeof(struct TreeNode));
    newnode->Left = newnode->Right = NULL;
    return newnode;
}

