#include <stdio.h>
#include <stdlib.h>

typedef struct node *nptr;
struct node
{
    int data;
    nptr link;
};

//函数根据循环链表有修改
nptr create_list();//设置一个头节点
int is_empty(nptr l);
int is_last(nptr p,nptr l);
nptr find(int x,nptr l);
void delete(int x,nptr l);
nptr find_previous(int x,nptr l);
void insert(int x,nptr l,nptr p);
void delete_list(nptr l);
void print_list(nptr l);

void josephu(int n,int m,int k);


int main(void)
{
    int n,m;
    scanf("%d%d",&n,&m);
    josephu(n,m,1);
    return 0;
}

nptr create_list()
{
    nptr l=(nptr)malloc(sizeof(struct node));
    l->data=0;
    l->link=l;
    return l;
}


int is_empty(nptr l)
{
    return l->link==NULL;
}


int is_last(nptr p,nptr l)
{
    return p->link==l;
}


nptr find(int x,nptr l)
{
    nptr p=l->link;
    while(p!=l && p->data!=x)
        p=p->link;
    return p;
}


nptr find_previous(int x,nptr l)
{
    nptr p=l;
    while(p->link!=l && p->link->data!=x)
        p=p->link;
    return p;
}


void delete_list(nptr l)
{
    nptr p,temp;
    p=l->link;
    l->link=NULL;
    while(p!=NULL)
    {
        temp=p->link;
        free(p);
        p=temp;
    }
}

void delete(int x,nptr l)
{
    nptr p,temp;
    p=find_previous(x,l);
    if(!is_last(p,l))
    {
        temp=p->link;
        p->link=temp->link;
        free(temp);
    }
}

void print_list(nptr l)
{
    nptr p=l->link;
    while(p!=l)
    {
        printf("%d ",p->data);
        p=p->link;
    }
    printf("\n");
}


void insert(int x,nptr l,nptr p)
{
    nptr temp=malloc(sizeof(struct node));
    temp->data=x;
    temp->link=p->link;
    p->link=temp;
}


void josephu(int n,int m,int k)
{
    if(m==0 || n==0)
        return;
    nptr l=create_list();//已定义函数
    nptr p=l,temp;
    int i,j,cnt=n;
    for(i=1;i<=n;i++)
    {
        insert(i,l,p);//已定义函数
        p=p->link;
    }
    p=find(k,l);//已定义函数
    while(cnt!=1)
    {
        for(j=1;j<=m-1;j++)
        {
            p=p->link;
            if(p==l)
                p=p->link;
        }
        printf("%d ",p->data);
        temp=p->link;
        if(temp==l)
            temp=temp->link;
        delete(p->data,l);
        p=temp;
        cnt--;
    }
    printf("%d",l->link->data);
}

