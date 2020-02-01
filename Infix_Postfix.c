#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stack_array *nstk;
struct stack_array                  //������һ���ṹ�����洢ջ������ջ���顢��С��ջ��
{
    char *st;
    int size;
    int top;
};

//ջ��غ���
nstk create_stack(int n);
int is_empty(nstk s);
int is_full(nstk s);
void dispose_stack(nstk s);
void make_empty(nstk s);
void push(char x, nstk s);
char pop(nstk s);
char top(nstk s);

int main(void) {
    char a[1001];                                           //�洢����ı��ʽ
    nstk s = create_stack(100);                               //������ջ
    int len, i;
    int in[65], out[65];                                            //in out����洢��Ӧ������ŵ����ȼ�
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
    printf("��������׺���ʽ��\n");
    scanf("%s", a);
    len = strlen(a);
    i = 0;
    printf("��Ӧ�ĺ�׺���ʽ��\n");
    while (i < len && a[i] != '#') {
        if (a[i] >= 48 && a[i] <= 57)                              //�����־�������Ƿ��ż�������
            printf("%c", a[i]);
        else if (a[i] == ')')                                  //�������žͳ�ջ������������Ϊֹ
        {
            while (1) {
                if (top(s) == '(') {
                    pop(s);
                    break;
                }
                printf("%c", top(s));
                pop(s);
            }
        } else if (is_empty(s) || out[a[i]] > in[top(s)])       //���������ջ�ջ��ߵ�ǰ��������ȼ�����ջ���ģ�����ջ
            push(a[i], s);
        else                                                //�����ջ�������������ȼ���������˺�����ջ
        {
            while (!is_empty(s) && out[a[i]] <= in[top(s)]) {
                printf("%c", top(s));
                pop(s);
            }
            push(a[i], s);
        }
        i++;
    }
    while (!is_empty(s))                                     //�������ջ��Ԫ�ؼ���
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