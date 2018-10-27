/*************************************************************************
	> File Name: test.cpp
	> Author: Peranda
	> Mail: 1365227825@qq.com 
	> Created Time: 2018年10月23日 星期二 19时38分56秒
 ************************************************************************/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#define MAX_N 1000
#define MAX_K 20


struct Edge {
    int v, n;
} g[MAX_N << 1];

int head[MAX_N + 5] = {0}, cnt = 0;
inline void add(int a, int b) {
    g[++cnt].v = b; // .to 存指向边
    g[cnt].n = head[a]; // 
    head[a] = cnt;
    printf("cnt %d   g[%d].v = %d   g[%d].n %d   head[%d] = %d\n", cnt, cnt, g[cnt].v, cnt, g[cnt].n, a, head[a]);
    return ;
}

// gas[i][j] i往上走２^ｊ步，所能到达的祖先节点的编号
int gas[MAX_N][MAX_K] = {0}, dep[MAX_N] = {0};
//dep 点深度

void dfs(int u, int father) {
    gas[u][0] = father;
    dep[u] = dep[father] + 1;
    for (int i = 1; i < MAX_K; i++) {
        gas[u][i] = gas[gas[u][i - 1]][i - 1];
    }
    for (int i = head[u]; i; i = g[i].n) {
        if (g[i].v == father) continue;
        dfs(g[i].v, u);
    }
    return ;
}

int lca(int a, int b) {
    if (dep[b] < dep[a]) {
        a ^= b;
        b ^= a;
        a ^= b;
    }
    int l = dep[b] - dep[a];
    for (int i = 0; i < MAX_K; i++) {//对齐
        if ((l & (1 << i))) b = gas[b][i];
        //  l & (1 << i)  处理的步数
        //判断二进制位，处理次数减少　（倍增）
    }
    if (a == b) return a;// a b 对齐了就是
    for (int i = MAX_K - 1; i >= 0; i--) {//一起往上走
        if (gas[a][i] != gas[b][i]) a = gas[a][i], b = gas[b][i];
        // 跳到公共祖先下一位
    }
    return gas[a][0];
}


int main() {
    int n;
    int a, b;
    scanf("%d", &n);
    for (int i = 1; i < n; i++) {
        scanf("%d%d", &a, &b);
        printf("%d : %d -> %d \n", i, a, b);
        add(a, b);
        add(b, a);
    }
    dfs(1, 0);
    // 任一节点不影响两点的距离
    while (scanf("%d%d", &a, &b) != EOF) {
        printf("lca (%d, %d) = %d, %d -> %d = %d\n",a, b, lca(a, b), a, b, dep[a] + dep[b] - 2 * dep[lca(a, b)]);
    }
    return 0;
}
