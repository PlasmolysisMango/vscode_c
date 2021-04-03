#include <stdio.h>

void swap(int *a, int *b);

int main()
{
    int a = 1, b = 2;
    int c[] = {1, 2, 3};
    const char *names[] = {
                   "Zara Ali",
                   "Hina Ali",
                   "Nuha Ali",
                   "Sara Ali",
    };
    printf("%s\n", names[2]); //%s 接受一个char *变量，其指向需要输出的字符数组
    // swap(&a, &b);
    return 0;
}

void swap(int *a, int *b) // *a为变量的值，a为变量的地址。
{
    printf("%d, %d", *a, *b);
    return;
}