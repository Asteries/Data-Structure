#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stack_array *nstk;           //栈指针
struct stack_array {
    char *st;                               //栈的存储数组
    int size;                               //栈的大小
    int top;                                //栈顶标号
};

nstk create_stack(int n);                   //栈相关函数
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
void func(int n, nstk s1, nstk s2);                                 //5，这里栈内st数组需要改成int数组


int main(void) {
    char out[101]="\0";
    char a[5]="abcd\0";
    nstk stk=create_stack(100);
    out_order(0,stk,out,a);
    return 0;
}


//结果是dcba cdba cbda cbad bdca bcda bcad badc bacd adcb acdb acbd abdc abcd 共14种
void out_order(int cnt, nstk stk, char *out, char *a) {
    if (cnt == strlen(a) && is_empty(stk))
        printf("%s ", out);
    else {
        if (cnt < strlen(a)) {                          //当前元素进栈
            push(a[cnt], stk);
            out_order(cnt + 1, stk, out, a);            //递归处理相同过程
            pop(stk);                                   //回溯
        }
        if (!is_empty(stk)) {
            out[strlen(out) + 1] = '\0';                //选择栈顶元素出栈
            out[strlen(out)] = top(stk);
            char tp = pop(stk);
            out_order(cnt, stk, out, a);                //递归处理相同过程
            out[strlen(out) - 1] = '\0';                //回溯
            push(tp, stk);
        }
    }
}


void im_order(char *s) {                                //当前出栈的元素后面的比他字典序小的元素必须倒序
    int l = strlen(s), i, j;
    for (i = 0; i < l; i++) {
        int cmp[l], cnt = 0;
        for (j = i + 1; j < l; j++)                     //存储字典序更小的元素
            if (s[i] > s[j])
                cmp[cnt++] = s[j];
        for (j = 0; j < cnt - 1; j++)                   //检查是否倒序
            if (cmp[j] < cmp[j + 1]) {
                printf("Wrong order\n");
                return;
            }
    }
    printf("Right order\n");
}


void fake_enqueue(char x, nstk s1, nstk s2) {           //两个栈，第一个栈用来存储输入的元素
    if (is_full(s1))
        printf("Full stack");
    else
        push(x, s1);
}

void fake_dequeue(nstk s1, nstk s2) {                   //出队时，直接输出第二个栈的栈顶元
    if (is_empty(s2))                                   //若为空将第一个栈的所有元素压进第二个栈，再输出栈顶
        while (!is_empty(s1))                           //这样倒序两次相当于先进先出
            push(pop(s1), s2);
    pop(s2);
}


void to_hex(int n, nstk s) {                            //简单的除以16不断取余数
    char a;                                             //char是为了处理十六进制的10-15（A-F）
    while (n >= 16) {
        if (n % 16 < 10)
            a = n % 16 + 48;                            //ASCII码变换
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


//这里需要把栈结构的st数组改成int数组
void func(int n, nstk s1, nstk s2) {                    //第一个栈储存依次需要操作的n
    while (n) {                                         //第二个栈储存每一次本来需要递归返回的结果
        push(n, s1);
        n /= 2;
    }
    push(0, s1);

    while (!is_empty(s1))
        if (top(s1) == 0) {
            push(1, s2);
            pop(s1);
        } else
            push(pop(s2) * pop(s1), s2);                //将老结果出栈，最新一个需要返回的结果入栈

    printf("%d", top(s2));
}






//栈函数部分
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

