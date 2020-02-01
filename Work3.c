#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stack_array *nstk;           //ջָ��
struct stack_array {
    char *st;                               //ջ�Ĵ洢����
    int size;                               //ջ�Ĵ�С
    int top;                                //ջ�����
};

nstk create_stack(int n);                   //ջ��غ���
int is_empty(nstk s);
int is_full(nstk s);
void dispose_stack(nstk s);
void make_empty(nstk s);
void push(char x, nstk s);
char pop(nstk s);
char top(nstk s);

void out_order(int cnt, nstk stk, char *out, char *a);              //1
void im_order(char *s);                                             //2
void fake_enqueue(char x, nstk s1, nstk s2);                        //3-1
void fake_dequeue(nstk s1, nstk s2);                                //3-2
void to_hex(int n, nstk s);                                         //4
void func(int n, nstk s1, nstk s2);                                 //5������ջ��st������Ҫ�ĳ�int����


int main(void) {
    char out[101]="\0";
    char a[5]="abcd\0";
    nstk stk=create_stack(100);
    out_order(0,stk,out,a);
    return 0;
}


//�����dcba cdba cbda cbad bdca bcda bcad badc bacd adcb acdb acbd abdc abcd ��14��
void out_order(int cnt, nstk stk, char *out, char *a) {
    if (cnt == strlen(a) && is_empty(stk))
        printf("%s ", out);
    else {
        if (cnt < strlen(a)) {                          //��ǰԪ�ؽ�ջ
            push(a[cnt], stk);
            out_order(cnt + 1, stk, out, a);            //�ݹ鴦����ͬ����
            pop(stk);                                   //����
        }
        if (!is_empty(stk)) {
            out[strlen(out) + 1] = '\0';                //ѡ��ջ��Ԫ�س�ջ
            out[strlen(out)] = top(stk);
            char tp = pop(stk);
            out_order(cnt, stk, out, a);                //�ݹ鴦����ͬ����
            out[strlen(out) - 1] = '\0';                //����
            push(tp, stk);
        }
    }
}


void im_order(char *s) {                                //��ǰ��ջ��Ԫ�غ���ı����ֵ���С��Ԫ�ر��뵹��
    int l = strlen(s), i, j;
    for (i = 0; i < l; i++) {
        int cmp[l], cnt = 0;
        for (j = i + 1; j < l; j++)                     //�洢�ֵ����С��Ԫ��
            if (s[i] > s[j])
                cmp[cnt++] = s[j];
        for (j = 0; j < cnt - 1; j++)                   //����Ƿ���
            if (cmp[j] < cmp[j + 1]) {
                printf("Wrong order\n");
                return;
            }
    }
    printf("Right order\n");
}


void fake_enqueue(char x, nstk s1, nstk s2) {           //����ջ����һ��ջ�����洢�����Ԫ��
    if (is_full(s1))
        printf("Full stack");
    else
        push(x, s1);
}

void fake_dequeue(nstk s1, nstk s2) {                   //����ʱ��ֱ������ڶ���ջ��ջ��Ԫ
    if (is_empty(s2))                                   //��Ϊ�ս���һ��ջ������Ԫ��ѹ���ڶ���ջ�������ջ��
        while (!is_empty(s1))                           //�������������൱���Ƚ��ȳ�
            push(pop(s1), s2);
    pop(s2);
}


void to_hex(int n, nstk s) {                            //�򵥵ĳ���16����ȡ����
    char a;                                             //char��Ϊ�˴���ʮ�����Ƶ�10-15��A-F��
    while (n >= 16) {
        if (n % 16 < 10)
            a = n % 16 + 48;                            //ASCII��任
        else
            a = n % 16 + 55;
        push(a, s);
        n /= 16;
    }
    if (n < 10)
        a = n + 48;
    else
        a = n + 55;
    push(a, s);
    while (!is_empty(s))
        printf("%c", pop(s));
}


//������Ҫ��ջ�ṹ��st����ĳ�int����
void func(int n, nstk s1, nstk s2) {                    //��һ��ջ����������Ҫ������n
    while (n) {                                         //�ڶ���ջ����ÿһ�α�����Ҫ�ݹ鷵�صĽ��
        push(n, s1);
        n /= 2;
    }
    push(0, s1);

    while (!is_empty(s1))
        if (top(s1) == 0) {
            push(1, s2);
            pop(s1);
        } else
            push(pop(s2) * pop(s1), s2);                //���Ͻ����ջ������һ����Ҫ���صĽ����ջ

    printf("%d", top(s2));
}






//ջ��������
nstk create_stack(int n) {
    nstk s = (nstk) malloc(sizeof(struct stack_array));
    s->st = (char *) malloc(sizeof(char) * (n + 1));
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


void push(char x, nstk s) {
    if (is_full(s))
        printf("Full Stack!");
    else
        s->st[++s->top] = x;
}


char top(nstk s) {
    if (!is_empty(s))
        return s->st[s->top];
    else {
        printf("Empty stack!\n");
        return 0;
    }
}


char pop(nstk s) {
    char item;
    if (is_empty(s))
        printf("Empty stack!\n");
    else
        item = s->st[s->top--];
    return item;
}

