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
    int inc = r - l + 1, i, j, k, temp;             //计算增量inc的初始值
    while (inc > 1) {
        inc = inc / 3 + 1;                          //每次改变增量
        for (i = l; i < l + inc; i++)
            for (j = i + inc; j <= r; j += inc) {   //以inc为增量取数，取inc-1次，然后对这inc-1个子列插入排序
                temp = a[j];
                k = j;
                while (j > i && a[j - inc] < temp) {    //移动元素并寻找位置，一次移动inc
                    a[j] = a[j - inc];
                    j -= inc;
                }
                a[j] = temp;  //插入元素
                j = k;
            }
    }
}
