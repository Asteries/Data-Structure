#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct treenode *tptr;//指向树结点的指针
struct treenode {
    int info;
    tptr left;
    tptr right;
};

typedef struct node *nptr;  //指向结点的指针
typedef struct queue *qptr; //指向队列的指针
struct node {
    tptr data;
    nptr next;
};

struct queue        //这个队列有头结点，即队头结点的下一个节点才是真正的队头，但队尾结点就是队尾
{
    nptr f;
    nptr r;
    int size;
};

//队列相关函数
qptr create_queue(void);
int is_empty(qptr q);
void dispose_queue(qptr q);
void make_empty(qptr q);
void enqueue(tptr x, qptr q);
void dequeue(qptr q);
tptr front(qptr q);

//习题解答
int depth(tptr t, qptr q);                  //3
void ex_lr(tptr t, qptr q);                 //4
tptr find(int x,tptr t);                    //5

//树相关函数
tptr create_tree(int x);
tptr insert(tptr t, int x);
void inorder(tptr t);

//查找树相关函数
tptr create_shtree(tptr t, int n);
tptr insertsh(tptr t, int x);

int main(void) {
    tptr t = NULL;
    qptr q = create_queue();
    int n;
    scanf("%d", &n);
    t = create_shtree(t, n);
    inorder(t);
    ex_lr(t,q);
    printf("\n");
    inorder(t);
    return 0;
}


int depth(tptr t, qptr q) {             //进行层次遍历，每遍历一层，depth+1
    int d = 0, l;
    tptr temp;
    if (t == NULL)
        return 0;
    enqueue(t, q);                      //树根入队
    while (!is_empty(q)) {
        l = q->size;                    //处理当前层的所有结点
        d++;                            //depth+1
        while (l--) {
            temp = front(q);
            dequeue(q);
            if (temp->left != NULL)     //依次入队下一层的所有结点
                enqueue(temp->left, q);
            if (temp->right != NULL)
                enqueue(temp->right, q);
        }
    }
    return d;
}


void ex_lr(tptr t, qptr q) {            //进行层次遍历，交换每一次遍历到的结点的左右子结点
    tptr temp, ex;
    if (t == NULL)
        return;
    enqueue(t, q);
    while (!is_empty(q)) {
        temp = front(q);
        dequeue(q);

        ex = temp->left;                //交换
        temp->left = temp->right;
        temp->right = ex;

        if (temp->left != NULL)         //处理下一层
            enqueue(temp->left, q);
        if (temp->right != NULL)
            enqueue(temp->right, q);
    }
}


tptr find(int x,tptr t)
{
    tptr pos=t;
    while(pos!=NULL)
        if(x==pos->info)                //查找到了
            return pos;
        else if(x>pos->info)            //查找右子树
            pos=pos->right;
        else                            //查找左子树
            pos=pos->left;
    return NULL;                        //没有找到返回NULL
}



//树函数部分
tptr create_tree(int x) {
    tptr t = (tptr) malloc(sizeof(struct treenode));
    t->info = x;
    t->left = NULL;
    t->right = NULL;
    return t;
}
void inorder(tptr t) {
    if (t->left != NULL)
        inorder(t->left);
    printf("%d ", t->info);
    if (t->right != NULL)
        inorder(t->right);
}

//队列函数部分
qptr create_queue(void) {
    qptr q = (qptr) malloc(sizeof(struct queue));
    q->f = q->r = (nptr) malloc(sizeof(struct node));
    q->f->next = NULL;        //imply: q->r->next=NULL
    q->size = 0;
    return q;
}


int is_empty(qptr q) {
    return q->f == q->r;
}


void dispose_queue(qptr q) {
    make_empty(q);
    free(q);
}


void make_empty(qptr q) {
    while (!is_empty(q))
        dequeue(q);
}

void enqueue(tptr x, qptr q) {
    nptr p = (nptr) malloc(sizeof(struct node));
    p->data = x;
    p->next = NULL;
    q->r->next = p;
    q->r = p;
    q->size++;
}

void dequeue(qptr q) {
    if (!is_empty(q)) {
        nptr p;
        p = q->f->next;
        q->f->next = p->next;
        if (q->r == p)
            q->f = q->r;
        //free(p);
        q->size--;
    } else
        printf("Empty queue\n");
}

tptr front(qptr q) {
    return q->f->next->data;
}

//查找树函数部分
tptr create_shtree(tptr t, int n) {
    int x;
    while (n--) {
        scanf("%d", &x);
        t = insertsh(t, x);
    }
    return t;
}


tptr insertsh(tptr t, int x) {
    if (t == NULL) {
        t = (tptr) malloc(sizeof(struct treenode));
        t->info = x;
        t->left = NULL;
        t->right = NULL;
    } else if (x < t->info)
        t->left = insertsh(t->left, x);
    else
        t->right = insertsh(t->right, x);
    return t;
}