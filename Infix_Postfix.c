#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stack_array *nstk;
struct stack_array                  //这里用一个结构体来存储栈，包含栈数组、大小、栈顶
{
    char *st;
    int size;
    int top;
};

//栈相关函数
nstk create_stack(int n);
int is_empty(nstk s);
int is_full(nstk s);
void dispose_stack(nstk s);
void make_empty(nstk s);
void push(char x, nstk s);
char pop(nstk s);
char top(nstk s);

int main(void) {
    char a[1001];                                           //存储输入的表达式
    nstk s = create_stack(100);                               //创建空栈
    int len, i;
    int in[65], out[65];                                            //in out数组存储对应运算符号的优先级
    in['+'] = 1;
    in['-'] = 1;
    in['*'] = 2;
    in['/'] = 2;
    in['%'] = 2;
    in['^'] = 3;
    in['('] = 0;
    out['+'] = 1;
    out['-'] = 1;
    out['*'] = 2;
    out['/'] = 2;
    out['%'] = 2;
    out['^'] = 4;
    out['('] = 5;
    printf("请输入中缀表达式：\n");
    scanf("%s", a);
    len = strlen(a);
    i = 0;
    printf("对应的后缀表达式：\n");
    while (i < len && a[i] != '#') {
        if (a[i] >= 48 && a[i] <= 57)                              //是数字就输出，是符号继续处理
            printf("%c", a[i]);
        else if (a[i] == ')')                                  //是右括号就出栈到遇到左括号为止
        {
            while (1) {
                if (top(s) == '(') {
                    pop(s);
                    break;
                }
                printf("%c", top(s));
                pop(s);
            }
        } else if (is_empty(s) || out[a[i]] > in[top(s)])       //是运算符，栈空或者当前运算符优先级高于栈顶的，就入栈
            push(a[i], s);
        else                                                //否则出栈到遇到更低优先级运算符，此后再入栈
        {
            while (!is_empty(s) && out[a[i]] <= in[top(s)]) {
                printf("%c", top(s));
                pop(s);
            }
            push(a[i], s);
        }
        i++;
    }
    while (!is_empty(s))                                     //依次输出栈内元素即可
    {
        printf("%c", top(s));
        pop(s);
    }
    return 0;
}


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
    int item;
    if (is_empty(s))
        printf("Empty stack!\n");
    else
        item = s->st[s->top--];
    return item;
}