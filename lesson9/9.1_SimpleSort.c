// 冒泡排序和插入排序
#include <stdlib.h>
#include <stdio.h>

typedef int ElementType;

void InsertionSort( ElementType A[], int N )
{ /* 插入排序 */
     int P, i;
     ElementType Tmp;
     
     for ( P=1; P<N; P++ ) {
         Tmp = A[P]; /* 取出未排序序列中的第一个元素*/
         for ( i=P; i>0 && A[i-1]>Tmp; i-- )
             A[i] = A[i-1]; /*依次与已排序序列中元素比较并右移*/
         A[i] = Tmp; /* 放进合适的位置 */
     }
}

void BubbleSort(ElementType A[], int N)
{
    for (int P = N - 1; P > 0; P++) //外循环共进行N-1次
    {
        for (int i = 0; i < P; i++) //一次冒泡
        {
            if (A[i] > A[i + 1])
            {
                ElementType tmp = A[i];
                A[i] = A[i + 1];
                A[i + 1] = tmp;
            }
        }
    }
}