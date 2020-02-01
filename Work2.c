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
    printf("����������С�������\n");
    scanf("%d%d", &m, &n);
    printf("���������Ԫ�أ�\n");
    for (i = 1; i <= m; i++)
        for (j = 1; j <= n; j++)
            scanf("%d", &a[i][j]);

    printf("ԭ����\n");
    print(a, m, n);

    printf("��Ԫ�飺\n");
    to_triple(a, t, m, m);
    for (i = 1; i <= t[0][2]; i++)
        printf("%d %d %d\n", t[i][0], t[i][1], t[i][2]);

    printf("�Խ��ߺͣ�\n");
    sum_diag(a, n);

    printf("������СԪ�أ�\n");
    find_min(a, b, m, n);
    for (i = 1; i <= m; i++)
        printf("%d %d %d\n", b[i][0], b[i][1], b[i][2]);

    printf("ת�þ���\n");
    transpose(a, p, m, n);
    print(p, n, m);

    printf("���㣺\n");
    saddle(a, m, n);
    return 0;
}

void to_triple(int a[][101], int t[][3], int m, int n) {
    int i, j;
    t[0][0] = -1;                             //��ʼ����Ԫ��ͳ����
    t[0][1] = -1;
    t[0][2] = 0;
    for (i = 1; i <= m; i++)                       //��������
        for (j = 1; j <= n; j++)
            if (a[i][j] != 0)                  //��������0��Ԫ�ؾʹ�����Ԫ��
            {
                t[t[0][2] + 1][0] = i;
                t[t[0][2] + 1][1] = j;
                t[t[0][2] + 1][2] = a[i][j];
                if (t[0][0] < i)               //�ı���Ԫ��ͳ����
                    t[0][0] = i;
                if (t[0][1] < j)
                    t[0][1] = j;
                t[0][2]++;
            }
}


void sum_diag(int a[][101], int n) {
    int sum = 0, i = 1, j = 1, k;
    for (k = 1; k <= n; k++)           //�����һ���Խ���
    {
        sum += a[i][j];
        i++;
        j++;
    }
    i = 1;
    j = n;
    for (k = 1; k <= n; k++)           //����ڶ����Խ���
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
        minn = 99999999;              //��ʼ����Сֵ
        for (int j = 1; j <= n; j++)
            if (a[i][j] < minn)        //��������Ԫ�ظ�����Сֵ������¼��λ��
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
        for (j = 1; j <= n; j++)           //�򵥵ص���˳��
            p[j][i] = a[i][j];
}


void saddle(int a[][101], int m, int n)//��������ж����СԪ��Ҫȫ������
{
    int i, j, k, minn, found = 0, flag;
    for (i = 1; i <= m; i++) {
        minn = 99999999;                          //��ʼ����Сֵ
        for (j = 1; j <= n; j++)
            if (a[i][j] < minn)
                minn = a[i][j];
        for (j = 1; j <= n; j++)
            if (a[i][j] == minn)                   //����ÿһ����СԪ��
            {
                flag = 1;                         //flag��¼����Сֵ�ǲ��������ֵ
                for (k = 1; k <= m; k++)
                    if (a[k][j] > minn)            //���ָ���ľͽ���
                    {
                        flag = 0;
                        break;
                    }
                if (flag == 1)                     //û�з��־����
                {
                    printf("%d %d %d\n", i, j, minn);
                    found = 1;
                }
            }
    }
    if (!found)                                  //û���ҵ�����Ҫ��ĵ㣬���0
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
