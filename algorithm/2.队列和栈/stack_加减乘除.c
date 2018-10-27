/*************************************************************************
> File Name: stack.cpp
> Author: Peranda
> Mail: 1365227825@qq.com 
> Created Time: 2018年10月22日 星期一 19时23分00秒
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define ERROR 0
#define OK 1

typedef struct Stack {
    int *data;
    int top_size, length;

} Stack;

void init(Stack *s, int length) {
    s->data = (int *)malloc(sizeof(int) * length);
    s->length = length;
    s->top_size = -1;

}

int push(Stack *s, int value) {
    if (s->top_size >= s->length - 1) return ERROR;
    s->top_size += 1;
    s->data[s->top_size] = value;
    return OK;

}

int pop(Stack *s) {
    if (s->top_size < 0) return ERROR;
    s->top_size -= 1;
    return 1;

}

int top(Stack *s) {
    return s->data[s->top_size];

}

int empty(Stack *s) {
    if (s->top_size < 0) return OK;
    else return ERROR;

}

int precede(char a, char b) {// 难点
    int key_a = 0, key_b = 0;
    if (a == '+' || a == '-') {
        key_a += 1;
    } else {
        key_a += 2;
    }
    if (b == '+' || b == '-') {
        key_b += 1;
    } else {
        key_b += 2;
    }
    return key_a > key_b;
}
int operate(char oper, int a, int b) {
    if (oper == '*') return a * b;
    if (oper == '/') return b / a; // 难点
    if (oper == '+') return a + b;
    if (oper == '-') return b - a; //　难点

}
void calc(Stack *numbers, Stack *operators) {
    int a = top(numbers);
    pop(numbers);
    int b = top(numbers);
    pop(numbers);
    push(numbers, operate(top(operators), a, b));
    pop(operators);

}

void clear(Stack *s) {
    free(s->data);
    free(s);
    return ;

}

int main() {
    int n; 
    scanf("%d", &n);
    Stack *numbers = (Stack *)malloc(sizeof(Stack));
    init (numbers, n);
    Stack *operators = (Stack *)malloc(sizeof(Stack));
    init(operators, n);
    char *buffer = (char *)malloc(sizeof(char) * (n + 1));
    scanf("%s", buffer);
    int i = 0; 
    while (i < n) {
        if (isdigit(buffer[i])) {
            push(numbers, buffer[i] - '0');
            i++;

        } else {
            if (empty(operators) || precede(buffer[i], top(operators))) {
                push(operators, buffer[i]);
                i++;

            } else {
                calc(numbers, operators);

            }

        }

    }
    while (!empty(operators)) {
        calc(numbers, operators);

    }
    printf("%d", top(numbers));
    clear(numbers);
    clear(operators);
    free(buffer);
    return 0;

}
