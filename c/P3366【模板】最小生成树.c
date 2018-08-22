/*************************************************************************
	> File Name: P3366【模板】最小生成树.c
	> Author: Peranda
	> Mail: 
	> Created Time: 2018年08月22日 星期三 11时47分42秒
 ************************************************************************/

#include <stdio.h>
#include <algorithm>
#define MAX_N 200010

int father[MAX_N + 5] = {0};
int rank[MAX_N + 5] = {0};

struct edge {
    int u; //点
    int v; //点
    int cost; //权值
};

edge ans[MAX_N + 5];//
bool cmp(edge e1, edge e2) {
    return e1.cost < e2.cost;
}

void init(int v) {
    for (int i = 0; i < v; i++) {
        father[i] = i;
        rank[i] = 1;
    }
}

int find(int x) {
    if (x !=  father[x]) {
        father[x] = find(father[x]);
    }
    return father[x];
}

void unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return;
    if (rank[x] < rank[y]) {
        father[x] = y;
    } else {
        father[y] = x;
        if (rank[x] == rank[y]) rank[x]++;
    }
}

int kruskal(int v, int e) {
    std::sort(ans, ans + e, cmp);//对权值排序
    init(v);  //并查集初始化
    int sum = 0;
    for (int i = 0; i < e; i++) {
        edge key = ans[i];
        if (find(key.u) != find(key.v)) {
            unite(key.u, key.v);
            sum += key.cost;
        }
    }
    return sum;
}

int main() {
    int v, e;//点和边数
    scanf("%d %d", &v, &e);
    for (int i = 0; i < e; i++) {
        scanf("%d %d %d", &ans[i].u, &ans[i].v, &ans[i].cost);
    }
    int sum = kruskal(v, e);
    printf("%d\n", sum);
    return 0;
}

