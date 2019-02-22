/*************************************************************************
	> File Name: 22.UnionSet.cpp
	> Author:  Peranda 
	> Mail:    1365227825@qq.com
	> Created Time: 2019年01月20日 星期日 16时48分31秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct UnionSet {
    int *color;
    int size;
} UnionSet;

UnionSet *init(int n) {
    UnionSet *u = (UnionSet *)calloc(sizeof(UnionSet), 1);
    u->color = (int *)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        u->color[i] = i;
    }
    u->size = n;
    return u;
}

int find(UnionSet *u, int x) {
    return u->color[x];
}
 

int merge(UnionSet *u, int a, int b) {
    int color_a = find(u, a), color_b = find(u, b);
    if (color_a == color_b) return 0;
    for (int i = 0; i < u->size; i++) {
        if (u->color[i] == color_a) u->color[i] = color_b;
    }
    return 1;
} 


void clear(UnionSet *u) {
    if (u == NULL) return ;
    free(u->color);
    free(u);
    return ;
}

void output(UnionSet *u) {
    for (int i = 0; i < u->size; i++) {
        printf("(%d, %d)\t");
        if (i + 1 < u->size && i + 1 % 5 == 0) printf("\n");
    }
    printf("\n\n");
    return ;
}

int main() {
    int op, a, b;
    srand(time(0));
    #define MAX_OP 10
    #define MAX_N 10
    UnionSet *u = init(MAX_N);
    for (int i = 0; i < MAX_OP; i++) {
        op = rand() % 4;
        a = rand() % MAX_N;
        b = rand() % MAX_N;
        switch (op) {
            case 0: {
                printf("find %d <-> %d = %d\n", a, b, find(u, a) == find());
            } break;
            default: {

            } break;
        }
    }
    
    return 0;
}

