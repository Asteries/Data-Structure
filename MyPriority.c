#include <stdio.h>      //priority queue(min) and heapsort
#include <stdlib.h>
#define minn -1000000
typedef struct heap *hptr;
struct heap
{
    int cap;
    int size;
    int *data;
};
hptr init(int maxsize);
void destroy(hptr h);
void make_empty(hptr h);    //incomplete
void insert(int x, hptr h);
int delete_min(hptr h);     //and return min
int find_min(hptr h);
int is_empty(hptr h);
int is_full(hptr h);

int main(void)
{
    int s[5],i=0;
    hptr hs=init(10);
    for(i=0;i<5;i++)
    {
        scanf("%d", &s[i]);
        insert(s[i],hs);
    }
    for(i=0;i<5;i++)
        printf("%d ",delete_min(hs));
    return 0;
}

hptr init(int maxsize)
{
    hptr h=(hptr)malloc(sizeof(struct heap));
    h->data=(int *)malloc((maxsize+1)*sizeof(int));
    h->cap=maxsize;
    h->size=0;
    h->data[0]=minn;
    return h;
}


int is_empty(hptr h)
{
    return h->size==0;
}


int is_full(hptr h)
{
    return h->size==h->cap;
}


void insert(int x, hptr h)
{
    int i=0;
    if(is_full(h))
        printf("Full");
    else
    {
        for(i=++h->size;h->data[i/2]>x;i/=2)
            h->data[i]=h->data[i/2];
        h->data[i]=x;
    }
}


int find_min(hptr h)
{
    return h->data[1];
}


int delete_min(hptr h)
{
    int i,child,minitem,lastitem;
    if(is_empty(h))
    {
        printf("Empty");
        return h->data[0];
    }
    minitem=find_min(h);
    lastitem=h->data[h->size--];
    for(i=1;i*2<=h->size;i=child)   //i: hole
    {
        child=i*2;
        if(child!=h->size && h->data[child+1]<h->data[child])   //smaller child
            child++;
        if(lastitem>h->data[child])
            h->data[i]=h->data[child];
        else
            break;
    }
    h->data[i]=lastitem;
    return minitem;
}