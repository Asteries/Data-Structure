#include <stdio.h>
#include <stdlib.h>

void read(int a[][3]);
void print_triple(int a[][3]);
void plus(int a[][3], int b[][3], int c[][3]);
void push(int x, int y, int f, int c[][3]);

int main(void) {
    int a[11][3], b[11][3], c[21][3];
    printf("请输入两个加数矩阵对应三元组的元素个数：\n");
    scanf("%d %d", &a[0][2], &b[0][2]);       //读入a储存的元素个数，必须保证行为主要顺序，列为次要顺序
    a[0][0] = -1;                 //最大行号
    b[0][0] = -1;
    a[0][1] = -1;                 //最大列号
    b[0][1] = -1;
    printf("请以输入三元组a：\n");
    read(a);
    printf("请以输入三元组b：\n");
    read(b);
    printf("三元组a与矩阵（有效形式）输出如下：\n");
    print_triple(a);
    printf("三元组b与矩阵（有效形式）输出如下：\n");
    print_triple(b);
    plus(a, b, c);
    printf("结果三元组c与矩阵（有效形式）输出如下：\n");
    print_triple(c);
}


void read(int a[][3]) {
    int i;
    for (i = 1; i <= a[0][2]; i++) {
        scanf("%d%d%d", &a[i][0], &a[i][1], &a[i][2]);  //依次将三元组输入a中
        if (a[i][0] > a[0][0])                             //更新最大行号和列号
            a[0][0] = a[i][0];
        if (a[i][1] > a[0][1])
            a[0][1] = a[i][1];
    }
}


void print_triple(int a[][3])//仅仅输出矩阵的有效形式，即忽略外围的全是0的行和列
{
    int i, j, k, flag = 0;
    for (i = 1; i <= a[0][2]; i++)                                 //直接遍历a输出三元组形式
        printf("%d %d %d\n", a[i][0], a[i][1], a[i][2]);
    printf("\n");
    for (i = 1; i <= a[0][0]; i++) {
        for (j = 1; j <= a[0][1]; j++)                             //遍历矩阵位置
        {
            flag = 0;                                         //标记矩阵元素是否是0
            for (k = 1; k <= a[0][2]; k++)                         //遍历a来寻找当前位置的元素
                if (a[k][0] == i && a[k][1] == j) {
                    flag = 1;
                    break;
                }
            if (flag == 1)                                     //根据标记判断输出
                printf("%d ", a[k][2]);
            else
                printf("%d ", 0);
        }
        printf("\n");
    }
    printf("\n");
}

void plus(int a[][3], int b[][3], int c[][3])//仍采用类似归并排序的处理方式
{
    int i = 1, j = 1;
    c[0][0] = -1;
    c[0][1] = -1;                                             //c的最大行列号不直接取a,b中大的一个，因为有相加等于0的情况
    c[0][2] = 0;
    while (i <= a[0][2] && j <= b[0][2]) {
        if (a[i][0] == b[j][0] && a[i][1] == b[j][1])            //行列均相等
        {
            if ((a[i][2] + b[i][2]) != 0)                        //和等于0就不处理
            {
                push(a[i][0], a[i][1], a[i][2] + b[j][2], c);    //元素求和并加入c
                i++;                                        //处理下一次比较
                j++;
            }
        } else if (a[i][0] < b[j][0])                            //将行数较小的加入c
        {
            push(a[i][0], a[i][1], a[i][2], c);
            i++;                                            //处理下一次比较
        } else if (a[i][0] > b[j][0]) {
            push(b[j][0], b[j][1], b[j][2], c);
            j++;                                            //处理下一次比较
        } else {
            if (a[i][1] < b[j][1])                             //行相等要保证列有序，否则有加法运算会被跳过
            {
                push(a[i][0], a[i][1], a[i][2], c);
                i++;                                        //处理下一次比较
            } else {
                push(b[j][0], b[j][1], b[j][2], c);
                j++;                                        //处理下一次比较
            }
        }
    }
    if ((i - 1) == a[0][2])                                      //将剩余的三元组直接顺次加入c
        for (; j <= b[0][2]; j++)
            push(b[j][0], b[j][1], b[j][2], c);
    else
        for (; i <= a[0][2]; i++)
            push(a[i][0], a[i][1], a[i][2], c);
}


void push(int x, int y, int f, int c[][3]) {
    c[c[0][2] + 1][0] = x;                  //将所给的三元组插入c
    c[c[0][2] + 1][1] = y;
    c[c[0][2] + 1][2] = f;
    if (c[0][0] < x)                       //变更最大行列号
        c[0][0] = x;
    if (c[0][1] < y)
        c[0][1] = y;
    c[0][2]++;                          //变更计数
}