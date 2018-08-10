/*************************************************************************
	> File Name: eu12.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月29日 星期日 11时16分53秒
 ************************************************************************/

#include<stdio.h>
#define MAX_N 100000

int dnum[MAX_N] = {0};
int prime[MAX_N] = {0};
int mnum[MAX_N] = {0};

void init() {
    for (int i = 2; i * 2 <= MAX_N; i++) {
        if (!prime[i]) {
            prime[++prime[0]] = i;
            dnum[i] = 2;
            mnum[i] = 1;
        }
        for (int j = 1; j <= prime[0]; j++) {
            if (i * prime[j] >= MAX_N) break;
            prime[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                mnum[i * prime[j]] = mnum[i]  + 1;
                dnum[i * prime[j]] = dnum[i] / (mnum[i] + 1) * (mnum[i] + 2);
                break;
            } else {
                mnum[i * prime[j]] = 1;
                dnum[i * prime[j]] = dnum[i] * dnum[prime[j]];
            }
        } 
    }
    return ;
}

int factor_nums(int n) {
    if (n & 1) return dnum[n] * dnum[(n + 1) / 2];
    return dnum[n + 1] * dnum[n / 2];
}

int main() {
    init();
    int key = 1; 
    while (factor_nums(key) < 500) key++;
    printf("%d\n", key * (key + 1) / 2);
    return 0;
}
