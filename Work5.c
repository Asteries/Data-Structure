#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node *nptr;
typedef struct queue *qptr;
struct node {
    int data;
    nptr next;
};
struct queue        //有头结点的队列结构，f->next是队头，r是队尾
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

void prim(int g[][101], int n) {                //n表示结点标号的最大值，假定从1号点出发
    int i, j, temp, minn;
    int vis[n + 1], best[n + 1], close[n + 1];
    //vis表示结点有没有访问过,best表示与结点相连的最短的一条边长，close表示与结点最近的结点
    for (i = 1; i <= n; i++) {                  //初始化
        vis[i] = 0;                             //全部没有访问
        best[i] = g[1][i];                      //最短边长都是与1的距离
        close[i] = 1;                           //最近的都是1
    }
    vis[1] = 1;                                 //从1开始，1被访问
    for (i = 2; i <= n; i++) {
        minn = 999999999;
        for (j = 2; j <= n; j++) {
            if (!vis[j] && best[j] < minn) {    //寻找最短边长与那个结点
                minn = best[j];
                temp = j;
            }
        }
        vis[temp] = 1;                          //标记已访问
        printf("(%d,%d) ", temp, close[temp]);
        for (j = 1; j <= n; j++) {
            if (!vis[j] && g[temp][j] < best[j]) {  //由于temp已经访问了，best和close会有变化
                best[j] = g[temp][j];
                close[j] = temp;
            }
        }
    }
}

void bfs(int g[][5], int n, qptr q, int st) {
    int vis[n + 1], i, j;           //vis记录结点有没有访问过
    for (i = 1; i <= n; i++)
        vis[i] = 0;
    printf("%d ", st);              //起始点
    vis[st] = 1;
    enqueue(st, q);
    while (!is_empty(q)) {          //思路类似层次遍历，假定g中1表示连通，0表示不连通
        st = front(q);              //按队列顺序依次访问
        dequeue(q);
        for (j = 1; j <= n; j++) {
            if (g[st][j] == 1 && vis[j] == 0) { //访问相连的所有点并入队
                printf("%d ", j);
                vis[j] = 1;
                enqueue(j, q);
            }
        }
    }
}

void degree(int n, nptr v[]) {      //v是邻接表头数组
    int in[n + 1], out[n + 1], i;   //用两个数组储存各个结点的入度和出度
    nptr pos;
    for (i = 1; i <= n; i++) {      //初始化
        in[i] = 0;
        out[i] = 0;
    }
    for (i = 1; i <= n; i++) {      //遍历邻接表头数组
        pos = v[i]->next;           //假设每个邻接表都有头结点
        while (pos != NULL) {       //遍历每个邻接表
            out[i]++;               //自己出度+1
            in[pos->data]++;        //遍历到点的入度+1
            pos = pos->next;
        }
    }
    for (i = 1; i <= n; i++)
        printf("%d ", in[i]);
    printf("\n");
    for (i = 1; i <= n; i++)
        printf("%d ", out[i]);
}


//队列相关函数
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


