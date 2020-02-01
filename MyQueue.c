#include <stdio.h>
#include <stdlib.h>

typedef struct node *nptr;
typedef struct queue *qptr;
struct node {
    int data;       //type: changeable
    nptr next;
};
struct queue        //f->next: front r->next&r: rear
{
    nptr f;
    nptr r;
    int size;
};

qptr create_queue(void);
int is_empty(qptr q);
void dispose_queue(qptr q);
void make_empty(qptr q);
void enqueue(int x, qptr q);
void dequeue(qptr q);
int front(qptr q);

int main(void) {
    qptr test = create_queue();
    printf("%d\n", is_empty(test));
    enqueue(1, test);
    printf("%d\n", is_empty(test));
    enqueue(2, test);
    printf("%d\n", front(test));
    dequeue(test);
    printf("%d\n", front(test));
    dequeue(test);
    printf("%d\n", is_empty(test));
    dispose_queue(test);
    return 0;
}

qptr create_queue(void) {
    qptr q = (qptr) malloc(sizeof(struct queue));
    q->f = q->r = (nptr) malloc(sizeof(struct node));
    q->f->next = NULL;        //imply: q->r->next=NULL
    q->size=0;
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
