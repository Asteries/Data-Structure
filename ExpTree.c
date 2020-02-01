#include <stdio.h>          //expression tree(no showing of empty tree)
#include <stdlib.h>
#include <string.h>

typedef struct treenode *tptr;
struct treenode {
    char info;
    tptr left;
    tptr right;
};

tptr create_tree(void);
void preorder(tptr t, int depth);//depth: just for recording
void inorder(tptr t, int depth);
void postorder(tptr t, int depth);//incomplete
int depth(tptr t);

typedef struct node *nptr;
struct node {
    tptr data;
    nptr next;
};

nptr create_stack(void);
int is_empty(nptr s);
void dispose_stack(nptr s);
void make_empty(nptr s);
void push(tptr x, nptr s);
tptr top(nptr s);
void pop(nptr s);

int main(void) {
    nptr st = create_stack();
    char exp[101];      //postfix exp
    scanf("%s", exp);
    int l = strlen(exp), i = 0;
    for (i = 0; i < l; i++) {
        if (exp[i] >= 'a' && exp[i] <= 'z') {
            tptr al = create_tree();
            al->info = exp[i];
            push(al, st);
        } else {
            tptr sy = create_tree();
            sy->info = exp[i];
            sy->right = top(st);
            pop(st);
            sy->left = top(st);
            pop(st);
            push(sy, st);
        }
    }
    postorder(top(st), 0);
    return 0;
}


tptr create_tree(void) {
    tptr t = (tptr) malloc(sizeof(struct treenode));
    t->info = 0;
    t->left = NULL;
    t->right = NULL;
    return t;
}

int depth(tptr t) {
    int ld, rd;
    if (t == NULL)             //never
        return 0;
    ld = depth(t->left);
    rd = depth(t->right);
    if (ld > rd)
        return ld + 1;
    else
        return rd + 1;
}

void preorder(tptr t, int depth) {
    printf("%c", t->info);
    if (t->left != NULL)
        preorder(t->left, depth + 1);
    if (t->right != NULL)
        preorder(t->right, depth + 1);
}


void inorder(tptr t, int depth) {
    if (t->left != NULL)
        inorder(t->left, depth + 1);
    printf("%c", t->info);
    if (t->right != NULL)
        inorder(t->right, depth + 1);
}


void postorder(tptr t, int depth) {
    if (t->left != NULL)
        postorder(t->left, depth + 1);
    if (t->right != NULL)
        postorder(t->right, depth + 1);
    printf("%c", t->info);
}


nptr create_stack(void) {
    nptr s = (nptr) malloc(sizeof(struct node));
    s->data = NULL;
    s->next = NULL;
    return s;
}


int is_empty(nptr s) {
    return s->next == NULL;
}


void dispose_stack(nptr s) {
    make_empty(s);
    free(s);
}


void make_empty(nptr s) {
    while (!is_empty(s))
        pop(s);
}


void push(tptr x, nptr s) {
    nptr p = (nptr) malloc(sizeof(struct node));
    p->next = s->next;
    p->data = x;
    s->next = p;
}


tptr top(nptr s) {
    if (!is_empty(s))
        return s->next->data;
    else {
        printf("Empty stack\n");
        return 0;
    }
}

void pop(nptr s) {
    nptr temp;
    if (is_empty(s))
        printf("Empty stack\n");
    else {
        temp = s->next;
        s->next = temp->next;
        free(temp);
    }
}
