/*************************************************************************
	> File Name: 1.vector.cpp
	> Author: Peranda
	> Mail: 
	> Created Time: 2018年10月11日 星期四 18时57分05秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DEFAULT_ARG(a, b) ((#a)[0] ? a + 0 : b)
// 判断a的第一个字符
// a + 0 防止展开时为空报错
#define init(a) __init(DEFAULT_ARG(a, 10)) 
//默认设置为0

typedef struct Vector {
    int *data;
    int size, length;
} Vector;

Vector *__init(int n) {
    Vector *p = (Vector *)malloc (sizeof (Vector));
    p->data = (int *) malloc(sizeof (int) * n);
    p->size = n;
    p->length = 0;
    return p;
}

int expand(Vector *v) {
    printf("[%p] expanding\n", v->data);
    int *p = (int *)realloc(v->data, sizeof(int) * 2 * v->size); // p的存在是防止，两种情况申请失败
    // realloc 申请两倍空间不需要
    if (p == NULL) return 0; 
    v->data = p;
    v->size *= 2;
    printf("[%p] expand Vector success, the size %d\n", v->data, v->size);
    return 1;
}


int insert(Vector *v, int value, int ind) {
    if (v->length == v->size) {
        if (expand(v) == 0) return 0;
    }
    if (ind < 0 || ind > v->length) return 0;
    for (int i = v->length - 1; i >= ind; i--) {
        v->data[i + 1] = v->data[i];
    }
    v->data[ind] = value;
    v->length += 1;
    return 1;
} 

int erase(Vector *v, int ind) {
    if (v->length == 0) return 0;
    if (ind < 0 || ind >= v->length) return 0;
    for (int i = ind + 1; i < v->length; i++) {
        v->data[i - 1] = v->data[i];
    }
    v->length -= 1;
    return 1;
}

void output(Vector *v) {
    printf("Vector = [");
    for (int i = 0; i < v->length; i++) {
        printf(" %d", v->data[i]);
    }
    printf("]\n");
}

void clear(Vector *v) {
    if (v == NULL) return ;
    free(v->data);
    free(v);
    return ;
}

int main() {
    Vector *v = init(100);
    #define MAX_OP 50 
    for (int t = 0; t < MAX_OP; t++) {
        int op = rand() % 5, ind, value;
        switch(op) {
            case 4 :
            case 3 :
            case 2 :
            case 0 : {
                ind = rand() % (v->length + 3) - 1;
                value = rand() % 100;
                printf("insert(%d, %d) = %d to Vector\n",value, ind, insert(v, value, ind));
                output(v);
            } break;
            case 1 : {
                ind = rand() % (v->length + 3) - 1;
                printf("erase(%d) = %d from Vector\n", ind, erase(v, ind));
                output(v);
            } break;
        }
    }
    clear(v);
    return 0;
}
