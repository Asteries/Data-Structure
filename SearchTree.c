#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct treenode *tptr;
struct treenode {
    int info;
    tptr left;
    tptr right;
    int times;              //times记录相同的数出现了多少次
};

tptr create_shtree(tptr t, int n);
tptr insertsh(tptr t, int x);
void inorder(tptr t);


int main(void) {
    tptr t = NULL;
    int n;
    scanf("%d", &n);            //n是数据个数
    t = create_shtree(t, n);
    inorder(t);
    return 0;
}

tptr create_shtree(tptr t, int n) {
    int x;
    while (n--) {
        scanf("%d", &x);
        t = insertsh(t, x);         //不断输入数据并insert
    }
    return t;
}


tptr insertsh(tptr t, int x) {
    if (t == NULL) {                                        //找到了应该插入的位置，就申请空间并插入
        t = (tptr) malloc(sizeof(struct treenode));
        t->info = x;
        t->left = NULL;
        t->right = NULL;
        t->times = 1;
    } else if (x == t->info)                                //找到相同数据，times+1
        t->times++;
    else if (x < t->info)                                   //更小就递归插到左子树
        t->left = insertsh(t->left, x);
    else                                                    //更大就递归插到右子树
        t->right = insertsh(t->right, x);
    return t;                                               //返回t以传递修改
}


void inorder(tptr t) {                  //左中右顺序遍历即可
    int i;
    if (t->left != NULL)
        inorder(t->left);
    for (i = 1; i <= t->times; i++)
        printf("%d ", t->info);
    if (t->right != NULL)
        inorder(t->right);
}
