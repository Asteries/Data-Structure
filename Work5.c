#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node *nptr;
typedef struct queue *qptr;
struct node {
    int data;
    nptr next;
};
struct queue        //��ͷ���Ķ��нṹ��f->next�Ƕ�ͷ��r�Ƕ�β
{
    nptr f;
    nptr r;
    int size;
};

qptr create_queue(void);
int is_empty(qptr q);
void enqueue(int x, qptr q);
void dequeue(qptr q);
int front(qptr q);

void prim(int g[][101], int n);                  //1
void bfs(int g[][5], int n, qptr q, int st);     //2
void degree(int n, nptr v[]);                    //3

int main(void) {
    return 0;
}

void prim(int g[][101], int n) {                //n��ʾ����ŵ����ֵ���ٶ���1�ŵ����
    int i, j, temp, minn;
    int vis[n + 1], best[n + 1], close[n + 1];
    //vis��ʾ�����û�з��ʹ�,best��ʾ������������̵�һ���߳���close��ʾ��������Ľ��
    for (i = 1; i <= n; i++) {                  //��ʼ��
        vis[i] = 0;                             //ȫ��û�з���
        best[i] = g[1][i];                      //��̱߳�������1�ľ���
        close[i] = 1;                           //����Ķ���1
    }
    vis[1] = 1;                                 //��1��ʼ��1������
    for (i = 2; i <= n; i++) {
        minn = 999999999;
        for (j = 2; j <= n; j++) {
            if (!vis[j] && best[j] < minn) {    //Ѱ����̱߳����Ǹ����
                minn = best[j];
                temp = j;
            }
        }
        vis[temp] = 1;                          //����ѷ���
        printf("(%d,%d) ", temp, close[temp]);
        for (j = 1; j <= n; j++) {
            if (!vis[j] && g[temp][j] < best[j]) {  //����temp�Ѿ������ˣ�best��close���б仯
                best[j] = g[temp][j];
                close[j] = temp;
            }
        }
    }
}

void bfs(int g[][5], int n, qptr q, int st) {
    int vis[n + 1], i, j;           //vis��¼�����û�з��ʹ�
    for (i = 1; i <= n; i++)
        vis[i] = 0;
    printf("%d ", st);              //��ʼ��
    vis[st] = 1;
    enqueue(st, q);
    while (!is_empty(q)) {          //˼·���Ʋ�α������ٶ�g��1��ʾ��ͨ��0��ʾ����ͨ
        st = front(q);              //������˳�����η���
        dequeue(q);
        for (j = 1; j <= n; j++) {
            if (g[st][j] == 1 && vis[j] == 0) { //�������������е㲢���
                printf("%d ", j);
                vis[j] = 1;
                enqueue(j, q);
            }
        }
    }
}

void degree(int n, nptr v[]) {      //v���ڽӱ�ͷ����
    int in[n + 1], out[n + 1], i;   //���������鴢�����������Ⱥͳ���
    nptr pos;
    for (i = 1; i <= n; i++) {      //��ʼ��
        in[i] = 0;
        out[i] = 0;
    }
    for (i = 1; i <= n; i++) {      //�����ڽӱ�ͷ����
        pos = v[i]->next;           //����ÿ���ڽӱ���ͷ���
        while (pos != NULL) {       //����ÿ���ڽӱ�
            out[i]++;               //�Լ�����+1
            in[pos->data]++;        //������������+1
            pos = pos->next;
        }
    }
    for (i = 1; i <= n; i++)
        printf("%d ", in[i]);
    printf("\n");
    for (i = 1; i <= n; i++)
        printf("%d ", out[i]);
}


//������غ���
qptr create_queue(void) {
    qptr q = (qptr) malloc(sizeof(struct queue));
    q->f = q->r = (nptr) malloc(sizeof(struct node));
    q->f->next = NULL;
    q->size = 0;
    return q;
}


int is_empty(qptr q) {
    return q->f == q->r;
}


void enqueue(int x, qptr q) {
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
        free(p);
        q->size--;
    } else
        printf("Empty queue\n");
}

int front(qptr q) {
    return q->f->next->data;
}


