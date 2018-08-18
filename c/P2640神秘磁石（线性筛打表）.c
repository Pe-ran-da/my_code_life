/*************************************************************************
	> File Name: P2640神秘磁石（线性筛打表）.c
	> Author: Peranda
	> Mail: 
	> Created Time: 2018年08月18日 星期六 09时53分18秒
 ************************************************************************/

#include <stdio.h>
#define MAX_N 10000

int ans[MAX_N + 10] = {0};
int prime[MAX_N + 10] = {0};

void is_prime() {
    for (int i = 2; i <= MAX_N; i++) {
        if (!ans[i]) ans[++ans[0]] = i, prime[i] = 1;
        for (int j = 1; j <= ans[0]; j++) {
            if(i * ans[j] > MAX_N) break;
            ans[i * ans[j]] = 1;
            if (i % ans[j] == 0) break;
        }
    }
}

int main() {
    is_prime();
    int n, k;
    scanf("%d %d", &n, &k);
    int key = 0;
    for (int i = 1; i <= MAX_N; i++) {
        if (i < n && (i + k) <= n) {
            if (prime[i] && prime[i + k]) {
                printf("%d %d\n",i, i + k);
                key = 1;

            }
        }
    }
    if (key == 0) printf("empty\n");
    return 0;
}


