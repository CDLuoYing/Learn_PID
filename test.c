#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{

    int a = 0;
    srand((unsigned int)time(NULL));

    for (int i = 0; i < 10; i++)
    {
        /* code */
        int ret1 = rand() % 10 + 1; // 生成1~10的随机数
        printf("%d ", ret1);
    }

    return 0;
}
