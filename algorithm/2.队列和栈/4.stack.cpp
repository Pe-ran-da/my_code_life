/*************************************************************************
	> File Name: 4.stack.cpp
	> Author: Peranda
	> Mail: 1365227825@qq.com 
	> Created Time: 2018年10月21日 星期日 19时15分28秒
 ************************************************************************/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef struct Stack {
    int *data;
    int top, size;
}Stack;

Stack *init(int n) {
    Stack *s = (Stack *)malloc(sizeof (Stack));
    s->data = (int *)malloc (sizeof(int) * n);
    s->top = -1;
    s->size = n;
    return s;
}

int empty(Stack *s) {
    return s->top == -1;
}

int top(Stack *s) {
    if(empty(s)) return 0;
    return s->data[s->top];
}

int push(Stack *s, int value) {
    if(s->top + 1 == s->size) return 0;
    s->top += 1;
    s->data[s->top] = value;
    return 1;
} 

void pop(Stack *s) {
    if (empty(s)) return ;
    s->top -= 1;
}

void clear(Stack *s) {
    if (s == NULL) return ;
    free(s->data);
    free(s);
    return ;
}

void output(Stack *s) {
    printf("stack = [");
    for (int i = s->top; i > -1; i--) {
        printf(" %d", s->data[i]);
        i && printf(",");
    }
    printf("]\n");
    return ;
}

int main() {
    srand(time(0));
    #define MAX_OP 20
    Stack *s = init(MAX_OP);
    for (int i = 0; i < MAX_OP; i++) {
        int op = rand() % 4, value = rand() % 4;
        switch (op) {
            case 0:
            case 1:
            case 2:
                    push (s, value);
                    printf("push %d to Stack\n", value);
                    output(s);
                    break;
            case 3:
                    printf("pop %d from Stack\n", top(s));
                    pop(s);
                    output(s);
                    break;
        }
    }
    return 0;
}
