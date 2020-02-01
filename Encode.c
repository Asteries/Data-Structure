#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node *nptr;
struct node {
    char data;
    nptr link;
};

//函数根据循环链表有修改
nptr create_list();
nptr find(char x, nptr l);
void delete(nptr p, nptr l);
nptr find_previous(char x, nptr l);
void insert(char x, nptr l, nptr p);
void print_list(nptr l);

void no_rep(char *str, char *strn, int *is);
void setup(char *strn, int *is, nptr l);
void encode(nptr l, char *code);


int main(void) {
    char str[1001], strn[1001] = "\0", code[128];
    int is[128] = {0}, i;
    nptr l = create_list();
    gets(str);
    no_rep(str, strn, is);
    setup(strn, is, l);
    encode(l, code);
    for (i = 32; i <= 126; i++)
        printf("%c", code[i]);
    return 0;
}


void setup(char *strn, int *is, nptr l) {
    int len = strlen(strn), i;
    nptr p = l;
    for (i = 0; i < len; i++) {
        insert(strn[i], l, p);
        p = p->link;
    }
    for (i = 32; i <= 126; i++)
        if (is[i] == 0) {
            insert(i, l, p);
            p = p->link;
        }
}

void encode(nptr l, char *code) {
    nptr p = l->link, temp, q = l;
    int i, lim, cnt = 0;
    char fst = p->data;
    while (p->link->link != p) {
        lim = p->data;
        temp = p->link;
        if (temp == l)
            temp = temp->link;
        delete(q, l);
        p = temp;
        q->link = p;
        for (i = 1; i <= lim - 1; i++) {
            p = p->link;
            q = q->link;
            if (p == l) {
                p = p->link;
                q = q->link;
            }
        }
        code[lim] = p->data;
    }
    code[p->data] = fst;
}


void no_rep(char *str, char *strn, int *is) {
    int i, l, j = 0;
    l = strlen(str);
    for (i = 0; i < l; i++)
        if (is[str[i]] == 0) {
            strn[j++] = str[i];
            strn[j] = '\0';
            is[str[i]] = 1;
        }
}


void print_list(nptr l) {
    nptr p = l->link;
    while (p != l) {
        printf("%c", p->data);
        p = p->link;
    }
    printf("\n");
}


nptr create_list() {
    nptr l = (nptr) malloc(sizeof(struct node));
    l->data = 0;
    l->link = l;      //循环链表设置
    return l;       //l作为头节点
}


void delete(nptr p, nptr l) {
    nptr temp;
    temp = p->link;
    p->link = temp->link;
    free(temp);
}


void insert(char x, nptr l, nptr p)//将x插入到l表的p位置后
{
    nptr temp = malloc(sizeof(struct node));
    temp->data = x;
    temp->link = p->link;
    p->link = temp;
}