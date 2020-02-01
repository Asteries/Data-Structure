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
    if (l > r)      //l>r说明排完了最小段
        return;
    base = a[l];    //基准数设为当前段最左边的元素
    i = l;
    j = r;
    while (i != j) {
        while (a[j] >= base && i < j)   //从右开始找比基准数小的数（基准数在左边，先从右边找）
            j--;
        while (a[i] <= base && i < j)   //从左开始找比基准数大的数
            i++;
        if (i < j) {                    //交换找到的数
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }
    a[l] = a[i];                //交换停止位置的数和基准数
    a[i] = base;
    quick_sort(a, l, i - 1);    //递归处理左边一段
    quick_sort(a, i + 1, r);    //递归处理右边一段
}
