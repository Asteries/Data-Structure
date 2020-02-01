#include <stdio.h>
#include <stdlib.h>

void shell_sort(int a[], int l, int r);

int main(void) {
    int arr[10], i, n;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    shell_sort(arr, 0, n - 1);
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    return 0;
}

void shell_sort(int a[], int l, int r) {
    int inc = r - l + 1, i, j, k, temp;             //��������inc�ĳ�ʼֵ
    while (inc > 1) {
        inc = inc / 3 + 1;                          //ÿ�θı�����
        for (i = l; i < l + inc; i++)
            for (j = i + inc; j <= r; j += inc) {   //��incΪ����ȡ����ȡinc-1�Σ�Ȼ�����inc-1�����в�������
                temp = a[j];
                k = j;
                while (j > i && a[j - inc] < temp) {    //�ƶ�Ԫ�ز�Ѱ��λ�ã�һ���ƶ�inc
                    a[j] = a[j - inc];
                    j -= inc;
                }
                a[j] = temp;  //����Ԫ��
                j = k;
            }
    }
}
