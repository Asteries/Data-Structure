#include <stdio.h>
#include <stdlib.h>

void read(int a[][3]);
void print_triple(int a[][3]);
void transpose(int a[][3], int b[][3]);
void fast_transpose(int a[][3], int b[][3]);

int main(void) {
    int a[11][3], b[11][3];
    printf("������Ԫ�ظ�����\n");
    scanf("%d", &a[0][2]);       //����a�����Ԫ�ظ���
    a[0][0] = -1;                 //����к�
    a[0][1] = -1;                 //����к�
    read(a);
    printf("��Ԫ����ԭ������Ч��ʽ��������£�\n");
    print_triple(a);
    transpose(a, b);
    printf("ת�ú���Ԫ����ԭ������Ч��ʽ��������£�\n");
    print_triple(b);
    fast_transpose(a, b);
    printf("����ת�ú���Ԫ����ԭ������Ч��ʽ��������£�\n");
    print_triple(b);
}


void read(int a[][3]) {
    int i;
    printf("���������Ӧ��������Ԫ�飺\n");
    for (i = 1; i <= a[0][2]; i++) {
        scanf("%d%d%d", &a[i][0], &a[i][1], &a[i][2]);  //���ν���Ԫ������a��
        if (a[i][0] > a[0][0])                             //��������кź��к�
            a[0][0] = a[i][0];
        if (a[i][1] > a[0][1])
            a[0][1] = a[i][1];
    }
}


void print_triple(int a[][3])//��������������Ч��ʽ����������Χ��ȫ��0���к���
{
    int i, j, k, flag = 0;
    for (i = 1; i <= a[0][2]; i++)                                 //ֱ�ӱ���a�����Ԫ����ʽ
        printf("%d %d %d\n", a[i][0], a[i][1], a[i][2]);
    printf("\n");
    for (i = 1; i <= a[0][0]; i++) {
        for (j = 1; j <= a[0][1]; j++)                             //��������λ��
        {
            flag = 0;                                         //��Ǿ���Ԫ���Ƿ���0
            for (k = 1; k <= a[0][2]; k++)                         //����a��Ѱ�ҵ�ǰλ�õ�Ԫ��
                if (a[k][0] == i && a[k][1] == j) {
                    flag = 1;
                    break;
                }
            if (flag == 1)                                     //���ݱ���ж����
                printf("%d ", a[k][2]);
            else
                printf("%d ", 0);
        }
        printf("\n");
    }
    printf("\n");
}


void transpose(int a[][3], int b[][3]) {
    int i, j, cnt = 1;                      //cnt���ת��ʱӦ�ü�����Ԫ���λ��
    b[0][0] = a[0][1];                    //����������к�
    b[0][1] = a[0][0];
    b[0][2] = a[0][2];
    for (i = 1; i <= a[0][1]; i++)             //�����к��Ա�֤ת�ú���Ԫ����к����������
        for (j = 1; j <= a[0][2]; j++)
            if (a[j][1] == i)              //��Ҫת�õ�Ԫ��
            {
                b[cnt][1] = a[j][0];
                b[cnt][0] = a[j][1];
                b[cnt][2] = a[j][2];
                cnt++;
            }
}


void fast_transpose(int a[][3], int b[][3]) {
    int i, j, num[a[0][1] + 1], first[a[0][1] + 1];    //numͳ�Ƹ��з���Ԫ�ظ��� firstͳ�Ƹ��У�ת�ú�Ϊ�У��׸�����Ԫ�ǵڼ�����Ԫ��
    b[0][0] = a[0][1];                            //����������к�
    b[0][1] = a[0][0];
    b[0][2] = a[0][2];
    for (i = 1; i <= a[0][1]; i++)                     //��ʼ��
        num[i] = 0;
    for (i = 1; i <= a[0][2]; i++)                     //��Ӧ�кŵ�ͳ����+1
        num[a[i][1]]++;
    first[1] = 1;                                 //ת�ú��һ���׸�����Ԫ��Ȼ�ǵ�һ��
    for (i = 2; i <= a[0][1]; i++)                     //���Ƶó������е�����
        first[i] = first[i - 1] + num[i - 1];
    for (i = 1; i <= a[0][2]; i++)                     //����ÿһ����Ԫ��
    {
        j = a[i][1];                              //j��¼��ǰ��Ԫ����к�
        b[first[j]][0] = a[i][1];                 //b[first[j]]���ǵ�ǰԪ��Ӧ���µ���Ԫ������
        b[first[j]][1] = a[i][0];
        b[first[j]][2] = a[i][2];
        first[j]++;
    }
}