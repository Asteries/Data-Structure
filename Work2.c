#include <stdio.h>
#include <stdlib.h>

void to_triple(int a[][101], int t[][3], int m, int n);            //1
void sum_diag(int a[][101], int n);                                //2
void find_min(int a[][101], int b[][3], int m, int n);             //3
void transpose(int a[][101], int p[][101], int m, int n);          //4
void saddle(int a[][101], int m, int n);                           //5

void print(int a[][101], int m, int n);

int main(void) {
    int a[101][101], t[21][3], b[21][3], p[101][101], m, n, i, j;
    printf("请输入矩阵行、列数：\n");
    scanf("%d%d", &m, &n);
    printf("请输入矩阵元素：\n");
    for (i = 1; i <= m; i++)
        for (j = 1; j <= n; j++)
            scanf("%d", &a[i][j]);

    printf("原矩阵：\n");
    print(a, m, n);

    printf("三元组：\n");
    to_triple(a, t, m, m);
    for (i = 1; i <= t[0][2]; i++)
        printf("%d %d %d\n", t[i][0], t[i][1], t[i][2]);

    printf("对角线和：\n");
    sum_diag(a, n);

    printf("各行最小元素：\n");
    find_min(a, b, m, n);
    for (i = 1; i <= m; i++)
        printf("%d %d %d\n", b[i][0], b[i][1], b[i][2]);

    printf("转置矩阵：\n");
    transpose(a, p, m, n);
    print(p, n, m);

    printf("鞍点：\n");
    saddle(a, m, n);
    return 0;
}

void to_triple(int a[][101], int t[][3], int m, int n) {
    int i, j;
    t[0][0] = -1;                             //初始化三元组统计量
    t[0][1] = -1;
    t[0][2] = 0;
    for (i = 1; i <= m; i++)                       //遍历矩阵
        for (j = 1; j <= n; j++)
            if (a[i][j] != 0)                  //遇到不是0的元素就存入三元组
            {
                t[t[0][2] + 1][0] = i;
                t[t[0][2] + 1][1] = j;
                t[t[0][2] + 1][2] = a[i][j];
                if (t[0][0] < i)               //改变三元组统计量
                    t[0][0] = i;
                if (t[0][1] < j)
                    t[0][1] = j;
                t[0][2]++;
            }
}


void sum_diag(int a[][101], int n) {
    int sum = 0, i = 1, j = 1, k;
    for (k = 1; k <= n; k++)           //计算第一条对角线
    {
        sum += a[i][j];
        i++;
        j++;
    }
    i = 1;
    j = n;
    for (k = 1; k <= n; k++)           //计算第二条对角线
    {
        sum += a[i][j];
        i++;
        j--;
    }
    printf("%d\n", sum);
}


void find_min(int a[][101], int b[][3], int m, int n) {
    int i, j, minn;
    for (i = 1; i <= m; i++) {
        minn = 99999999;              //初始化最小值
        for (int j = 1; j <= n; j++)
            if (a[i][j] < minn)        //遍历行内元素更新最小值，并记录其位置
            {
                minn = a[i][j];
                b[i][0] = i;
                b[i][1] = j;
                b[i][2] = a[i][j];
            }
    }
}


void transpose(int a[][101], int p[][101], int m, int n) {
    int i, j;
    for (i = 1; i <= m; i++)
        for (j = 1; j <= n; j++)           //简单地调整顺序
            p[j][i] = a[i][j];
}


void saddle(int a[][101], int m, int n)//这里如果有多个最小元素要全部处理
{
    int i, j, k, minn, found = 0, flag;
    for (i = 1; i <= m; i++) {
        minn = 99999999;                          //初始化最小值
        for (j = 1; j <= n; j++)
            if (a[i][j] < minn)
                minn = a[i][j];
        for (j = 1; j <= n; j++)
            if (a[i][j] == minn)                   //处理每一个最小元素
            {
                flag = 1;                         //flag记录行最小值是不是列最大值
                for (k = 1; k <= m; k++)
                    if (a[k][j] > minn)            //发现更大的就结束
                    {
                        flag = 0;
                        break;
                    }
                if (flag == 1)                     //没有发现就输出
                {
                    printf("%d %d %d\n", i, j, minn);
                    found = 1;
                }
            }
    }
    if (!found)                                  //没有找到符合要求的点，输出0
        printf("0");
}


void print(int a[][101], int m, int n) {
    int i, j;
    for (i = 1; i <= m; i++) {
        for (j = 1; j <= n; j++)
            printf("%d ", a[i][j]);
        printf("\n");
    }
}
