#include <stdio.h>
#include <stdlib.h>

void stairs(int n, int c[][101]);
void trans(int n, int c[][101]);
void print_matrix(int n, int c[][101]);

int main(void) {
    int n, i, j;
    printf("��������Ҫ��ħ��������������:\n");
    scanf("%d", &n);                 //n��ħ������
    int cube[101][101];
    for (i = 0; i < 101; i++)
        for (j = 0; j < 101; j++)          //��ʼ������
            cube[i][j] = 0;
    stairs(n, cube);
}


void stairs(int n, int c[][101])//���ý��ݷ�����
{
    int i = n, j = 1, tot = 1, item = 1;   //��n��1�п�ʼ�tot��¼�Ѿ����˵ĸ�����item��¼Ӧ�������
    while (tot <= n * n) {
        c[i][j] = item;
        if (tot % n == 0)            //һб�������Ĵ���
        {
            i += n;
            j -= (n - 2);
        } else                    //������һб��ʱ�Ĵ���
        {
            i -= 1;
            j += 1;
        }
        tot++;                  //�ı��¼��
        item++;
    }
    trans(n, c);                 //ƽ�ƺ���
    print_matrix(n, c);          //���ħ��
}


void trans(int n, int c[][101])//ƽ��
{
    int i, j, cnt = n + n / 2 * 2;                //cnt���������к�
    for (i = 1; i <= n / 2; i++)                 //����Ϊ��λƽ�ƣ��������Ҹ�����һ��
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
    printf("���ɵ�ħ��Ϊ��\n");
    for (i = n / 2 + 1; i <= n / 2 + n; i++)           //����Чλ�ÿ�ʼ���
    {
        for (j = n / 2 + 1; j <= n / 2 + n; j++)
            printf("%*d", 4, c[i][j]);    //����������Ϊ4
        printf("\n");
    }
}