#include<stdio.h>

void hanoi(int n,char A,char B,char C);

int main()
{
    int n;
    printf("��������Ҫ�ƶ������Ӹ�����\n");
    scanf("%d",&n);
    printf("�ƶ�˳��Ϊ��\n");
    hanoi(n,'X','Y','Z');
    return 0;
}

void hanoi(int n,char A,char B,char C)
{
    if(n==1)
        printf("%c to %c\n",A,C);       //�ݹ��������������һ�����ӵ��ƶ�
    else
    {
        hanoi(n-1,A,C,B);               //�������ƶ����̲��Ϊ��������1�׵������ƶ�������һ�����ӵ��ƶ�
        printf("%c to %c\n",A,C);
        hanoi(n-1,B,A,C);
    }
}
