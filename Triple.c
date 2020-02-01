#include <stdio.h>
#include <stdlib.h>

void read(int a[][3]);
void print_triple(int a[][3]);
void transpose(int a[][3], int b[][3]);
void fast_transpose(int a[][3], int b[][3]);

int main(void) {
    int a[11][3], b[11][3];
    printf("请输入元素个数：\n");
    scanf("%d", &a[0][2]);       //读入a储存的元素个数
    a[0][0] = -1;                 //最大行号
    a[0][1] = -1;                 //最大列号
    read(a);
    printf("三元组与原矩阵（有效形式）输出如下：\n");
    print_triple(a);
    transpose(a, b);
    printf("转置后三元组与原矩阵（有效形式）输出如下：\n");
    print_triple(b);
    fast_transpose(a, b);
    printf("快速转置后三元组与原矩阵（有效形式）输出如下：\n");
    print_triple(b);
}


void read(int a[][3]) {
    int i;
    printf("请以输入对应个数的三元组：\n");
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


void transpose(int a[][3], int b[][3]) {
    int i, j, cnt = 1;                      //cnt标记转置时应该加入三元组的位置
    b[0][0] = a[0][1];                    //交换最大行列号
    b[0][1] = a[0][0];
    b[0][2] = a[0][2];
    for (i = 1; i <= a[0][1]; i++)             //遍历列号以保证转置后三元组的行号仍是有序的
        for (j = 1; j <= a[0][2]; j++)
            if (a[j][1] == i)              //需要转置的元素
            {
                b[cnt][1] = a[j][0];
                b[cnt][0] = a[j][1];
                b[cnt][2] = a[j][2];
                cnt++;
            }
}


void fast_transpose(int a[][3], int b[][3]) {
    int i, j, num[a[0][1] + 1], first[a[0][1] + 1];    //num统计各列非零元素个数 first统计各列（转置后为行）首个非零元是第几个三元组
    b[0][0] = a[0][1];                            //交换最大行列号
    b[0][1] = a[0][0];
    b[0][2] = a[0][2];
    for (i = 1; i <= a[0][1]; i++)                     //初始化
        num[i] = 0;
    for (i = 1; i <= a[0][2]; i++)                     //对应列号的统计数+1
        num[a[i][1]]++;
    first[1] = 1;                                 //转置后第一行首个非零元当然是第一个
    for (i = 2; i <= a[0][1]; i++)                     //递推得出其余行的数据
        first[i] = first[i - 1] + num[i - 1];
    for (i = 1; i <= a[0][2]; i++)                     //遍历每一个三元组
    {
        j = a[i][1];                              //j记录当前三元组的列号
        b[first[j]][0] = a[i][1];                 //b[first[j]]就是当前元对应的新的三元组的序号
        b[first[j]][1] = a[i][0];
        b[first[j]][2] = a[i][2];
        first[j]++;
    }
}