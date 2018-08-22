/*************************************************************************
	> File Name: P3367【模板】并查集.c
	> Author: Peranda
	> Mail: 
	> Created Time: 2018年08月21日 星期二 19时29分51秒
 ************************************************************************/

#include <stdio.h>
#define MAX_N 10000

int ans[MAX_N + 10] = {0};
int rank[MAX_N + 10] = {0};

__attribute__((constructor)) //gcc提供的构造函数　在main之前就会被运行
void init() {
    for (int i = 1; i <= MAX_N; i++) {
        ans[i] = i;
        rank[i] = 0;
    }
}

int find(int x) {//查询和路径压缩需要的查询函数
    if (ans[x] == x) {
        return x;
    } else {
        return ans[x] = find(ans[x]);
    }
}

void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    if (rank[x] < rank[y]) {
        ans[x] = y;
    } else {
        ans[y] = x;
        if (rank[x] == rank[y]) rank[x]++;
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    for (int i = 0; i < m; i++) {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        if (a == 1) {
            unite(b, c);
        } else if (a == 2) {
            if (find(b) == find(c)) {
                printf("Y\n");
            } else {
                printf("N\n");
            }
        }
    }
    return 0;
}
