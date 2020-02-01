//17377082 ������ 170814��
#include <stdio.h>
#include <stdlib.h>

typedef struct node *nptr;
struct node {
    int coe, high;
    nptr link;
};

void create_poly(nptr *l1, nptr *l2, int m, int n);            //m��l1�ĳ��ȣ�n��l2�ĳ���
void poly_plus(nptr l1, nptr l2, nptr *l3);                   //l3�ǽ������ʽ
nptr insert_rear_data(int coe, int high, nptr *pl, nptr p);
nptr insert_rear_node(nptr n, nptr *pl, nptr p);
void print_list(nptr l);

int main(void) {
    nptr p1 = NULL, p2 = NULL, p3 = NULL;
    int m, n;
    printf("��������������ʽ�ĳ��ȣ���������\n");
    scanf("%d%d", &m, &n);
    create_poly(&p1, &p2, m, n);
    printf("�������ʽ�ĸ���ϵ�������Ϊ���������У���\n");
    poly_plus(p1, p2, &p3);
    return 0;
}


nptr insert_rear_data(int coe, int high, nptr *pl, nptr p)//��β����������
{

    nptr temp = (nptr) malloc(sizeof(struct node));//����һ���ڵ㴢���������
    temp->coe = coe;
    temp->high = high;
    if (p == NULL)             //����Ĳ���
    {
        temp->link = *pl;
        *pl = temp;
    } else {
        temp->link = p->link;
        p->link = temp;
    }
    return temp;//����β���ڵ��ָ��
}


nptr insert_rear_node(nptr n, nptr *pl, nptr p)//��β������ڵ�
{
    if (p == NULL)//�������
        *pl = n;
    else
        p->link = n;
    return n;//����β���ڵ��ָ��
}


void create_poly(nptr *l1, nptr *l2, int m, int n)//����ߴο�ʼ����
{
    int i, coe, high;//ʹ�ô�ǰ����ĺ��������������ʽ����Ľ���
    nptr pos = *l1;
    printf("�����ߴ��ʼ�����һ������ʽ�����ϵ���ʹ���������x^3Ϊ1 3������֮���ÿո�������ɣ�\n");
    for (i = 1; i <= m; i++) {
        scanf("%d%d", &coe, &high);
        pos = insert_rear_data(coe, high, l1, pos);
    }
    pos = *l2;
    printf("�����ߴ��ʼ����ڶ�������ʽ�����ϵ���ʹ���������x^3Ϊ1 3������֮���ÿո�������ɣ�\n");
    for (i = 1; i <= n; i++) {
        scanf("%d%d", &coe, &high);
        pos = insert_rear_data(coe, high, l2, pos);
    }
}


void poly_plus(nptr l1, nptr l2, nptr *l3)//��Ȼ�������ƹ鲢�����˼·
{
    nptr cnt = *l3;//l3β�ڵ�
    while (l1 != NULL && l2 != NULL) {
        if (l1->high > l2->high)   //�Ա���������ʽ�ĵ�ǰ��ߴ����ڵ㣬�����ߵ�һ�����ӵ����������
        {
            cnt = insert_rear_node(l1, l3, cnt);
            l1 = l1->link;        //������һ�αȽ�
        } else if (l1->high < l2->high) {
            cnt = insert_rear_node(l2, l3, cnt);
            l2 = l2->link;        //������һ�αȽ�
        } else                    //���ʱ������һ���½ڵ㴢����Ӻ�Ľ���������ӵ����������
        {
            nptr temp = (nptr) malloc(sizeof(struct node));
            temp->coe = l1->coe + l2->coe;
            temp->high = l1->high;
            cnt = insert_rear_node(temp, l3, cnt);
            l1 = l1->link;        //������һ�αȽ�
            l2 = l2->link;
        }
    }
    if (l1 == NULL)                //���ϻ�������Ķ���ʽ��ʣ�����򲿷�
        cnt->link = l2;
    else
        cnt->link = l1;
    print_list(*l3);            //��ӡ���
}


void print_list(nptr l) {
    while (l != NULL) {
        printf("%d %d   ", l->coe, l->high);
        l = l->link;
    }
    printf("\n");
}