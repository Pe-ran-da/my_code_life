/*************************************************************************
	> File Name: test.cpp
	> Author: Peranda
	> Mail: 1365227825@qq.com 
	> Created Time: 2018年11月01日 星期四 16时41分13秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define swap(a, b) { \
    __typeof(a) __temp = a; \
    a = b, b = __temp;\
}
// 如果宏的里面变量和函数内冲突，　容易导致逻辑错误，　应该避免，　比如　这个程序
// 中的temp（如果只是使用temp这个变量名） 在函数里也有，　运行后替换导致越界
typedef struct priority_queue {
    double *data;
    int cnt, size;
} priority_queue;

priority_queue *init(int n) {
    priority_queue *q = (priority_queue *)malloc(sizeof(priority_queue));
    q->data = (double *)malloc(sizeof(double) *(n + 1) );
    q->cnt = 0;
    q->size = n;
    return q;
}

int empty(priority_queue *q) {
    return q->cnt == 0;
}

int push(priority_queue *q, double value) {
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

double top(priority_queue *q) {
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
        printf(" %lf", q->data[i]);
        i == q->cnt || printf(",");
    }
    printf("]\n");
    return ;
}

int main() {
    //#define MAX_SUM 1010
    int n;
    double value;
    scanf("%d", &n);
    priority_queue *q = init(n);
    for (int i = 0; i < n; i++) {
        scanf("%lf", &value);
        push(q, value);
        output(q);
    }
    for (int i = 0; i < n; i++) {
       	printf("a : top : %lf\n", top(q));
        double a = top(q);
        pop(q);
        printf("b : top : %lf\n", top(q));
        double b = top(q);
        pop(q);
        double c = pow((a * b * b), 1/3);
        push(q, c);
        printf("c : %lf\n", c);
        output(q);
    }
    //q->cnt = n;
    
    output(q);
    
    
    return 0;
}



