/*************************************************************************
	> File Name: P3383【模板】线性筛素数.c
	> Author: Peranda
	> Mail: 
	> Created Time: 2018年08月22日 星期三 09时52分22秒
 ************************************************************************/

#include <stdio.h>
#define MAX_N 10000000

int is_prime[MAX_N + 5] = {0};
int prime[MAX_N + 5] = {0};

__attribute__((constructor))
void PRIME() {
    for (int i = 2; i <= MAX_N; i++) {
        if (!prime[i]) {
            prime[++prime[0]] = i;
            is_prime[i] = 1;
        }
        for (int j = 1; j <= prime[0]; j++) {
            if (i * prime[j] > MAX_N) break;
            prime[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++) {
        int key;
        scanf("%d", &key);
        if (is_prime[key]) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }
    return 0;
}
