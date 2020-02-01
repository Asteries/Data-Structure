//17377082 唐霆岳 170814班
#include <stdio.h>
#include <stdlib.h>

typedef struct node *nptr;
struct node {
    int data;
    nptr link;
};

//函数根据循环链表有修改
nptr create_list();

nptr find(int x, nptr l);

void delete(int x, nptr l);

nptr find_previous(int x, nptr l);

void insert(int x, nptr l, nptr p);

void josephu(int n, int m, int k);


int main(void) {
    int n, m, k;
    printf("请依次输入n、m、k：\n");
    scanf("%d%d%d", &n, &m, &k);
    printf("出表顺序为：\n");
    josephu(n, m, k);
    return 0;
}

nptr create_list() {
    nptr l = (nptr) malloc(sizeof(struct node));
    l->data = 0;
    l->link = l;      //循环链表设置
    return l;       //l作为头节点
}


nptr find(int x, nptr l)//找到表中第一个x（此问题表中没有重复的x）
{
    nptr p = l->link;
    while (p != l && p->data != x)
        p = p->link;
    return p;
}


nptr find_previous(int x, nptr l)//找到数据为x的节点的前驱结点
{
    nptr p = l;
    while (p->link != l && p->link->data != x)
        p = p->link;
    return p;
}


void delete(int x, nptr l)//删除第一个数据为x的节点
{
    nptr p, temp;
    p = find_previous(x, l);
    if (p->link != NULL) {
        temp = p->link;
        p->link = temp->link;
        free(temp);
    }
}


void insert(int x, nptr l, nptr p)//将x插入到l表的p位置
{
    nptr temp = malloc(sizeof(struct node));
    temp->data = x;
    temp->link = p->link;
    p->link = temp;
}


void josephu(int n, int m, int k) {
    if (m == 0 || n == 0 || k == 0)
        return;
    nptr l = create_list();       //创建循环链表
    nptr p = l, temp;
    int i, j, cnt = n;              //cnt：余下的人数
    for (i = 1; i <= n; i++)           //建立约瑟夫环（连续尾部插入）
    {
        insert(i, l, p);
        p = p->link;
    }
    p = find(k, l);                //找到开始报数的人
    while (cnt) {
        for (j = 1; j <= m - 1; j++)     //找出出表的人
        {
            p = p->link;
            if (p == l)            //特殊情况：跳到了头节点
                p = p->link;
        }
        temp = p->link;
        if (temp == l)             //特殊情况：跳到了头节点
            temp = temp->link;
        printf("%d ", p->data);  //为检查方便，输出完整的出表顺序
        delete(p->data, l);      //出表
        p = temp;
        cnt--;
    }
}
