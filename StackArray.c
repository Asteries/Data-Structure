#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stack_array *nstk;
struct stack_array {
    int *st;
    int size;
    int top;
};

nstk create_stack(int n);

int is_empty(nstk s);

int is_full(nstk s);

void dispose_stack(nstk s);

void make_empty(nstk s);

void push(int x, nstk s);

int pop(nstk s);

int top(nstk s);

int main(void) {
    nstk s = create_stack(100);
    return 0;
}

nstk create_stack(int n) {
    nstk s = (nstk) malloc(sizeof(struct stack_array));
    s->st = (int *) malloc(sizeof(int) * (n + 1));
    memset(s->st, 0, sizeof(s->st));
    s->size = n;
    s->top = 0;
}

int is_full(nstk s) {
    return s->top == s->size;
}

int is_empty(nstk s) {
    return s->top == 0;
}


void dispose_stack(nstk s) {
    make_empty(s);
    free(s->st);
    free(s);
}


void make_empty(nstk s) {
    while (!is_empty(s))
        pop(s);
}


void push(int x, nstk s) {
    if (is_full(s))
        printf("Full Stack!");
    else
        s->st[++s->top] = x;
}


int top(nstk s) {
    if (!is_empty(s))
        return s->st[s->top];
    else {
        printf("Empty stack!\n");
        return 0;
    }
}

int pop(nstk s) {
    int item;
    if (is_empty(s))
        printf("Empty stack!\n");
    else
        item = s->st[s->top--];
    return item;
}

