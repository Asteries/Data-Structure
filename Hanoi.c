#include<stdio.h>

void hanoi(int n,char A,char B,char C);

int main()
{
    int n;
    printf("请输入需要移动的盘子个数：\n");
    scanf("%d",&n);
    printf("移动顺序为：\n");
    hanoi(n,'X','Y','Z');
    return 0;
}

void hanoi(int n,char A,char B,char C)
{
    if(n==1)
        printf("%c to %c\n",A,C);       //递归结束条件：处理一个盘子的移动
    else
    {
        hanoi(n-1,A,C,B);               //将整个移动过程拆分为三步：降1阶的两次移动，和那一个盘子的移动
        printf("%c to %c\n",A,C);
        hanoi(n-1,B,A,C);
    }
}
