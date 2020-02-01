#include <stdio.h>
#include <stdlib.h>

void quick_sort(int a[], int l, int r);

int main(void) {
    int arr[10], i, n;
    scanf("%d", &n);
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    quick_sort(arr, 0, n - 1);
    for (i = 0; i < n; i++)
        printf("%d ", arr[i]);
    return 0;
}

void quick_sort(int a[], int l, int r) {
    int i, j, temp, base;
    if (l > r)      //l>r˵����������С��
        return;
    base = a[l];    //��׼����Ϊ��ǰ������ߵ�Ԫ��
    i = l;
    j = r;
    while (i != j) {
        while (a[j] >= base && i < j)   //���ҿ�ʼ�ұȻ�׼��С��������׼������ߣ��ȴ��ұ��ң�
            j--;
        while (a[i] <= base && i < j)   //����ʼ�ұȻ�׼�������
            i++;
        if (i < j) {                    //�����ҵ�����
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }
    a[l] = a[i];                //����ֹͣλ�õ����ͻ�׼��
    a[i] = base;
    quick_sort(a, l, i - 1);    //�ݹ鴦�����һ��
    quick_sort(a, i + 1, r);    //�ݹ鴦���ұ�һ��
}
