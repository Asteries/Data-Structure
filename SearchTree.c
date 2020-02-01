#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct treenode *tptr;
struct treenode {
    int info;
    tptr left;
    tptr right;
    int times;              //times��¼��ͬ���������˶��ٴ�
};

tptr create_shtree(tptr t, int n);
tptr insertsh(tptr t, int x);
void inorder(tptr t);


int main(void) {
    tptr t = NULL;
    int n;
    scanf("%d", &n);            //n�����ݸ���
    t = create_shtree(t, n);
    inorder(t);
    return 0;
}

tptr create_shtree(tptr t, int n) {
    int x;
    while (n--) {
        scanf("%d", &x);
        t = insertsh(t, x);         //�����������ݲ�insert
    }
    return t;
}


tptr insertsh(tptr t, int x) {
    if (t == NULL) {                                        //�ҵ���Ӧ�ò����λ�ã�������ռ䲢����
        t = (tptr) malloc(sizeof(struct treenode));
        t->info = x;
        t->left = NULL;
        t->right = NULL;
        t->times = 1;
    } else if (x == t->info)                                //�ҵ���ͬ���ݣ�times+1
        t->times++;
    else if (x < t->info)                                   //��С�͵ݹ�嵽������
        t->left = insertsh(t->left, x);
    else                                                    //����͵ݹ�嵽������
        t->right = insertsh(t->right, x);
    return t;                                               //����t�Դ����޸�
}


void inorder(tptr t) {                  //������˳���������
    int i;
    if (t->left != NULL)
        inorder(t->left);
    for (i = 1; i <= t->times; i++)
        printf("%d ", t->info);
    if (t->right != NULL)
        inorder(t->right);
}
