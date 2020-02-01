#include <stdio.h>
#include <stdlib.h>

void stairs(int n, int c[][101]);
void trans(int n, int c[][101]);
void print_matrix(int n, int c[][101]);

int main(void) {
    int n, i, j;
    printf("请输入需要的魔方阶数（奇数）:\n");
    scanf("%d", &n);                 //n是魔方阶数
    int cube[101][101];
    for (i = 0; i < 101; i++)
        for (j = 0; j < 101; j++)          //初始化数组
            cube[i][j] = 0;
    stairs(n, cube);
}


void stairs(int n, int c[][101])//采用阶梯法构造
{
    int i = n, j = 1, tot = 1, item = 1;   //从n行1列开始填，tot记录已经填了的个数，item记录应该填的数
    while (tot <= n * n) {
        c[i][j] = item;
        if (tot % n == 0)            //一斜行填完后的处理
        {
            i += n;
            j -= (n - 2);
        } else                    //正在填一斜行时的处理
        {
            i -= 1;
            j += 1;
        }
        tot++;                  //改变记录量
        item++;
    }
    trans(n, c);                 //平移函数
    print_matrix(n, c);          //输出魔方
}


void trans(int n, int c[][101])//平移
{
    int i, j, cnt = n + n / 2 * 2;                //cnt：最大的行列号
    for (i = 1; i <= n / 2; i++)                 //以下为对位平移，上下左右各处理一次
        for (j = n - i + 1; j <= n + i; j += 2)
            c[i + n][j] = c[i][j];
    for (i = cnt; i >= cnt - n / 2 + 1; i--)
        for (j = n - cnt + i; j <= n + cnt - i; j += 2)
            c[i - n][j] = c[i][j];
    for (j = 1; j <= n / 2; j++)
        for (i = n - j + 1; i <= n + j; i += 2)
            c[i][j + n] = c[i][j];
    for (j = cnt; j >= cnt - n / 2 + 1; j--)
        for (i = n - cnt + j; i <= n + cnt - j; i += 2)
            c[i][j - n] = c[i][j];
}


void print_matrix(int n, int c[][101]) {
    int i, j;
    printf("生成的魔方为：\n");
    for (i = n / 2 + 1; i <= n / 2 + n; i++)           //从有效位置开始输出
    {
        for (j = n / 2 + 1; j <= n / 2 + n; j++)
            printf("%*d", 4, c[i][j]);    //控制输出宽度为4
        printf("\n");
    }
}