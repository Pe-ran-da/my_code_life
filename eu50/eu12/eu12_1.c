/*************************************************************************
	> File Name: eu12_1.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月29日 星期日 20时08分08秒
 ************************************************************************/

#include<stdio.h>
#define MAX_N 100000
int dnum[MAX_N + 5] = {0};   // 记录下标这个数字的因子数量
int prime[MAX_N + 5] = {0};  

void init() {
    for (int i = 2; i * 2 <= MAX_N; i++) {
        if (!prime[i]) {
            prime[++prime[0]] = i;
            dnum[i] = 2;
            
        }
        for (int j = 1; j <= prime[0]; j++) {
            if (i * prime[j] > MAX_N) break;
            prime[i * prime[j]] = 1;
            if (i % prime[j] == 0) {
                int bj = 0, temp_i = i;
                while(temp_i % prime[j] == 0) bj += 1, temp_i /= prime[j]; // 删除掉相同的素因子
                dnum[i * prime[j]] = dnum[i] / (bj + 1) * (bj + 2);        // 除去原有的倍数 乘上相应的倍数
                break;
            } else {
                dnum[i * prime[j]] = dnum[i] * dnum[prime[j]];             // 互素的情况下直接乘
            }
        }
    }
    return ;
}

int factor_nums(int n) {
    if (n & 1) {
        return dnum[n] * dnum[(n + 1) / 2];
    }
    return dnum[n / 2] * dnum[n + 1];
}

int main() {
    init();
    int n = 1;
    while(factor_nums(n) < 500) n++;
    printf("%d\n", n * (n + 1) / 2);
    return 0;
}


