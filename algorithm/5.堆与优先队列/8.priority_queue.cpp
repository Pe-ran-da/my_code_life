/*************************************************************************
	> File Name: 8.priority_queue.cpp
	> Author: Peranda
	> Mail: 1365227825@qq.com 
	> Created Time: 2018年10月30日 星期二 19时22分47秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define swap(a, b) { \
    __typeof(a) __temp = a; \
    a = b, b = __temp;\
}
// 如果宏的里面变量和函数内冲突，　容易导致逻辑错误，　应该避免，　比如　这个程序
// 中的temp（如果只是使用temp这个变量名） 在函数里也有，　运行后替换导致越界
typedef struct priority_queue {
    int *data;
    int cnt, size;

} priority_queue;

priority_queue *init(int n) {
    priority_queue *q = (priority_queue *)malloc(sizeof(priority_queue));
    q->data = (int *)malloc(sizeof(int ) *(n + 1) );
    q->cnt = 0;
    q->size = n;
    return q;
}

int empty(priority_queue *q) {
    return q->cnt == 0;
}

int push(priority_queue *q, int value) {
    if (q->cnt  == q->size) return 0;
    q->data[++(q->cnt)] = value;
    int ind = q->cnt;
    while (ind > 1) {
        if (q->data[ind] <= q->data[ind >> 1]) break;
        swap(q->data[ind], q->data[ind >> 1]);
        ind >>= 1;
    }
    return 1;
} 

int pop(priority_queue *q) {
    if (empty(q)) return 0;
    q->data[1] = q->data[(q->cnt)--];
    int ind = 1;
    while ((ind << 1) <= q->cnt) {
        int temp = ind;
        if (q->data[temp] < q->data[ind << 1]) temp = ind << 1;
        if ((ind << 1 | 1) < q->cnt && q->data[temp] < q->data[ind << 1 | 1]) 
        temp = ind << 1 | 1;
        if (temp == ind) break;
        swap(q->data[ind], q->data[temp]);
        ind = temp;
    }
    return 1;
    
}



int top(priority_queue *q) {
    if (empty (q)) return 0;
    return q->data[1];
}



void clear(priority_queue *q) {
    if (q == NULL) return ;
    free(q->data);
    free(q);
    return ;
}

void output(priority_queue *q) {
    printf("queue = [");
    for (int i = 1; i <= q->cnt; i++) {
        printf(" %d", q->data[i]);
        i == q->cnt || printf(",");
    }
    printf("]\n");
    return ;
}


int main() {
    #define MAX_OP 20
    srand(time(0));
    priority_queue *q = init(MAX_OP);
    for (int i = 0; i < MAX_OP; i++) {
        int op = rand() % 4, value = rand() % 100;
        switch (op) {
            case 0:
            case 1:
            case 2: {
                printf("push %d : \n", value);
                push(q, value);
                output(q);
            } break;
            case 3: {
                printf("pop %d : \n", top(q));
                pop(q);
                output(q);
            } break;
        }
    }
}

