//17377082 ������ 170814��
#include <stdio.h>
#include <stdlib.h>

typedef struct node *nptr;
struct node {
    int data;
    nptr link;
};

//��������ѭ���������޸�
nptr create_list();

nptr find(int x, nptr l);

void delete(int x, nptr l);

nptr find_previous(int x, nptr l);

void insert(int x, nptr l, nptr p);

void josephu(int n, int m, int k);


int main(void) {
    int n, m, k;
    printf("����������n��m��k��\n");
    scanf("%d%d%d", &n, &m, &k);
    printf("����˳��Ϊ��\n");
    josephu(n, m, k);
    return 0;
}

nptr create_list() {
    nptr l = (nptr) malloc(sizeof(struct node));
    l->data = 0;
    l->link = l;      //ѭ����������
    return l;       //l��Ϊͷ�ڵ�
}


nptr find(int x, nptr l)//�ҵ����е�һ��x�����������û���ظ���x��
{
    nptr p = l->link;
    while (p != l && p->data != x)
        p = p->link;
    return p;
}


nptr find_previous(int x, nptr l)//�ҵ�����Ϊx�Ľڵ��ǰ�����
{
    nptr p = l;
    while (p->link != l && p->link->data != x)
        p = p->link;
    return p;
}


void delete(int x, nptr l)//ɾ����һ������Ϊx�Ľڵ�
{
    nptr p, temp;
    p = find_previous(x, l);
    if (p->link != NULL) {
        temp = p->link;
        p->link = temp->link;
        free(temp);
    }
}


void insert(int x, nptr l, nptr p)//��x���뵽l���pλ��
{
    nptr temp = malloc(sizeof(struct node));
    temp->data = x;
    temp->link = p->link;
    p->link = temp;
}


void josephu(int n, int m, int k) {
    if (m == 0 || n == 0 || k == 0)
        return;
    nptr l = create_list();       //����ѭ������
    nptr p = l, temp;
    int i, j, cnt = n;              //cnt�����µ�����
    for (i = 1; i <= n; i++)           //����Լɪ�򻷣�����β�����룩
    {
        insert(i, l, p);
        p = p->link;
    }
    p = find(k, l);                //�ҵ���ʼ��������
    while (cnt) {
        for (j = 1; j <= m - 1; j++)     //�ҳ��������
        {
            p = p->link;
            if (p == l)            //���������������ͷ�ڵ�
                p = p->link;
        }
        temp = p->link;
        if (temp == l)             //���������������ͷ�ڵ�
            temp = temp->link;
        printf("%d ", p->data);  //Ϊ��鷽�㣬��������ĳ���˳��
        delete(p->data, l);      //����
        p = temp;
        cnt--;
    }
}
