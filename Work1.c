//17377082 唐霆岳 170814班
//UTF-8
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node *nptr;      //为使用方便，给予指向node的指针nptr的别名
struct node {
    int data;
    nptr link;
};


int is_empty(nptr l);
int is_last(nptr p, nptr l);
nptr find(int x, nptr l);
void delete(int x, nptr *pl);
nptr find_previous(int x, nptr l);
void insert(int x, nptr *pl, nptr p);
void delete_list(nptr l);
void print_list(nptr l);


//以下各函数可以独立使用，不需要链表相关函数            由于没有头节点，使用二重指针
void delete_item(int *A, int b, int *n);                          //1
void exchange(int *A, int n);                                    //2
void insert_list(int *A, int *B, int *m, int n, int i);           //3
void delete_odd(int *A, int *n);                                 //4
void delete_node(int b, nptr *H);                                //5
void merge_list(nptr A, nptr B, int *m, int n);                    //6
void merge_order(nptr HA, nptr HB, nptr *HC);                     //7



int main(void)//主函数中可以进行测试
{
    return 0;
}


//算法函数部分
void delete_item(int *A, int b, int *n) {
    int i, j = 1;

    for (i = 1; i <= *n; i++)   //将不是b的元素复制到新表（仍用A）
        if (A[i] != b)
            A[j++] = A[i];
    *n = j - 1;
}


void exchange(int *A, int n) {
    int l = 1, r = n, temp;

    while (l < r)          //从两端同时开始扫描，左端遇到偶数，右边遇到奇数就交换（类似快速排序）
    {
        while (l <= n && A[l] % 2 == 1)
            l++;
        while (r > 0 && A[r] % 2 == 0)
            r--;
        if (l < r) {
            temp = A[l];
            A[l] = A[r];
            A[r] = temp;
        }
    }
}


void insert_list(int *A, int *B, int *m, int n, int i)//需要A对应数组足够大
{
    int j;

    for (j = i + 1; j <= *m; j++)//空出B所需的空间
        A[j + n] = A[j];
    for (j = i + 1; j <= i + n; j++)//覆盖
        A[j] = B[j - i];
    *m = *m + n;
}


void delete_odd(int *A, int *n) {
    int i;

    *n /= 2;
    for (i = 1; i <= *n; i++)//直接将按位置关系复制储存的数据
        A[i] = A[2 * i];
}


void delete_node(int b, nptr *H) {
    nptr p = *H, temp;

    while (p != NULL && p->data == b)//表头删除，直到表头储存的不是b为止
    {
        *H = p->link;
        free(p);
        p = *H;
    }
    if (p == NULL)
        return;
    while (p->link != NULL)//P后删除
    {
        while (p->link != NULL && p->link->data != b)
            p = p->link;
        if (p->link != NULL) {
            temp = p->link;
            p->link = temp->link;
            free(temp);
        }
    }
}


void merge_list(nptr A, nptr B, int *m, int n)//A,B两个表直接合并为A表
{
    nptr tempa, tempb;

    while (A != NULL && B != NULL) {
        tempa = B->link;
        tempb = B->link;
        A->link = B;
        B->link = tempa;
        if ((tempa == NULL || tempb == NULL) && *m < n)//A表比B表短时需要处理尾节点的link
            B->link = tempb;
        A = tempa;
        B = tempb;
    }
    *m = *m + n;
}


void merge_order(nptr HA, nptr HB, nptr *HC)//假设A和B中元素从小到大排列
{
    nptr cnt = *HC;        //cnt记录C的尾节点

    while (HA != NULL && HB != NULL)//比较两表的当前最小位置，谁更小就加入新表，类似归并排序
    {
        if (HA->data < HB->data) {
            if (cnt == NULL) {
                *HC = HA;
                cnt = HA;
                HA = HA->link;
            } else {
                cnt->link = HA;
                cnt = HA;
                HA = HA->link;
            }
        } else {
            if (cnt == NULL) {
                *HC = HB;
                cnt = HB;
                HB = HB->link;
            } else {
                cnt->link = HB;
                cnt = HB;
                HB = HB->link;
            }
        }
    }

    if (HA == NULL)     //连上剩余有序部分
        cnt->link = HB;
    else
        cnt->link = HA;
}


//链表相关函数部分
int is_empty(nptr l) {
    return l == NULL;
}


int is_last(nptr p, nptr l) {
    return p->link == NULL;
}


nptr find(int x, nptr l)         //find first x
{
    nptr p = l;
    while (p != NULL && p->data != x)
        p = p->link;
    return p;
}


nptr find_previous(int x, nptr l) {
    nptr p = l;
    while (p->link != NULL && p->link->data != x)
        p = p->link;
    return p;
}


void delete_list(nptr l) {
    nptr temp;
    while (l != NULL) {
        temp = l->link;
        free(l);
        l = temp;
    }
}


void delete(int x, nptr *pl)//pl是表头节点的指针的指针
{
    if ((*pl)->data == x)  //表头删除
    {
        *pl = (*pl)->link;
        return;
    }
    nptr p, temp;
    p = find_previous(x, *pl);
    if (p->link != NULL) {
        temp = p->link;
        p->link = temp->link;
        free(temp);
    }
}


void print_list(nptr l) {
    while (l != NULL) {
        printf("%d ", l->data);
        l = l->link;
    }
    printf("\n");
}


void insert(int x, nptr *pl, nptr p) {

    nptr temp = (nptr) malloc(sizeof(struct node));
    temp->data = x;
    if (p == NULL)     //表头插入
    {
        temp->link = *pl;
        *pl = temp;
    } else {
        temp->link = p->link;
        p->link = temp;
    }
}
