//17377082 唐霆岳 170814班
#include <stdio.h>
#include <stdlib.h>

typedef struct node *nptr;
struct node {
    int coe, high;
    nptr link;
};

void create_poly(nptr *l1, nptr *l2, int m, int n);            //m是l1的长度，n是l2的长度
void poly_plus(nptr l1, nptr l2, nptr *l3);                   //l3是结果多项式
nptr insert_rear_data(int coe, int high, nptr *pl, nptr p);
nptr insert_rear_node(nptr n, nptr *pl, nptr p);
void print_list(nptr l);

int main(void) {
    nptr p1 = NULL, p2 = NULL, p3 = NULL;
    int m, n;
    printf("请输入两个多项式的长度（项数）：\n");
    scanf("%d%d", &m, &n);
    create_poly(&p1, &p2, m, n);
    printf("结果多项式的各项系数与次数为（降幂排列）：\n");
    poly_plus(p1, p2, &p3);
    return 0;
}


nptr insert_rear_data(int coe, int high, nptr *pl, nptr p)//在尾部插入数据
{

    nptr temp = (nptr) malloc(sizeof(struct node));//建立一个节点储存这个数据
    temp->coe = coe;
    temp->high = high;
    if (p == NULL)             //常规的插入
    {
        temp->link = *pl;
        *pl = temp;
    } else {
        temp->link = p->link;
        p->link = temp;
    }
    return temp;//返回尾部节点的指针
}


nptr insert_rear_node(nptr n, nptr *pl, nptr p)//在尾部插入节点
{
    if (p == NULL)//常规插入
        *pl = n;
    else
        p->link = n;
    return n;//返回尾部节点的指针
}


void create_poly(nptr *l1, nptr *l2, int m, int n)//从最高次开始读入
{
    int i, coe, high;//使用此前定义的函数完成两个多项式链表的建立
    nptr pos = *l1;
    printf("请从最高次项开始输入第一个多项式各项的系数和次数，例如x^3为1 3，各项之间用空格隔开即可：\n");
    for (i = 1; i <= m; i++) {
        scanf("%d%d", &coe, &high);
        pos = insert_rear_data(coe, high, l1, pos);
    }
    pos = *l2;
    printf("请从最高次项开始输入第二个多项式各项的系数和次数，例如x^3为1 3，各项之间用空格隔开即可：\n");
    for (i = 1; i <= n; i++) {
        scanf("%d%d", &coe, &high);
        pos = insert_rear_data(coe, high, l2, pos);
    }
}


void poly_plus(nptr l1, nptr l2, nptr *l3)//仍然采用类似归并排序的思路
{
    nptr cnt = *l3;//l3尾节点
    while (l1 != NULL && l2 != NULL) {
        if (l1->high > l2->high)   //对比两个多项式的当前最高次数节点，将更高的一个链接到结果链表里
        {
            cnt = insert_rear_node(l1, l3, cnt);
            l1 = l1->link;        //处理下一次比较
        } else if (l1->high < l2->high) {
            cnt = insert_rear_node(l2, l3, cnt);
            l2 = l2->link;        //处理下一次比较
        } else                    //相等时，建立一个新节点储存相加后的结果，并链接到结果链表里
        {
            nptr temp = (nptr) malloc(sizeof(struct node));
            temp->coe = l1->coe + l2->coe;
            temp->high = l1->high;
            cnt = insert_rear_node(temp, l3, cnt);
            l1 = l1->link;        //处理下一次比较
            l2 = l2->link;
        }
    }
    if (l1 == NULL)                //连上还有余项的多项式的剩余有序部分
        cnt->link = l2;
    else
        cnt->link = l1;
    print_list(*l3);            //打印结果
}


void print_list(nptr l) {
    while (l != NULL) {
        printf("%d %d   ", l->coe, l->high);
        l = l->link;
    }
    printf("\n");
}