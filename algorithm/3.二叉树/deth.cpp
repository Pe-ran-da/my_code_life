/*************************************************************************
	> File Name: deth.cpp
	> Author: Peranda
	> Mail: 1365227825@qq.com 
	> Created Time: 2018年10月24日 星期三 11时33分51秒
 ************************************************************************/

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#define MAX_S 1000
#define MAX_N 20 


struct Node {
    int to, next;
} g[MAX_S << 1];

int head[MAX_S] = {0}, cnt = 0;
inline void add(int a, int b) {
    g[++cnt].to = b;
    g[cnt].next = head[a];
    head[a] = cnt;
    printf("cnt %d   g[%d].to = %d   g[%d].next %d   head[%d] = %d\n", cnt, cnt, g[cnt].to, cnt, g[cnt].next, a, head[a]);
    return ;
}

void print(int a, int b) {
    for (int i = head[a]; i; i = g[i].next) {
        printf("%d ", g[i].to);
    }
    printf("\n");
}

int main () {
    int n;
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        add(a, b); 
        add(b, a);
    }
    print(1, 0);
    return 0; 
}
