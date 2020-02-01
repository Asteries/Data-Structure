#include <stdio.h>
#include <stdlib.h>

typedef struct node *nptr;
struct node {
    int data;       //type: changeable
    nptr next;
};

nptr create_stack(void);

int is_empty(nptr s);

void dispose_stack(nptr s);

void make_empty(nptr s);

void push(int x, nptr s);

int top(nptr s);

void pop(nptr s);

int main(void) {
    nptr test, temp;
    test = create_stack();
    printf("%d\n", is_empty(test));
    push(1, test);
    printf("%d\n", is_empty(test));
    printf("%d\n", top(test));
    pop(test);
    printf("%d\n", is_empty(test));
    dispose_stack(test);
}


nptr create_stack(void) {
    nptr s = (nptr) malloc(sizeof(struct node));
    s->data = 0;
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


void push(int x, nptr s) {
    nptr p = (nptr) malloc(sizeof(struct node));
    p->next = s->next;
    p->data = x;
    s->next = p;
}


int top(nptr s) {
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