/*************************************************************************
	> File Name: eu7_prim.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月24日 星期二 10时23分12秒
 ************************************************************************/

#include<stdio.h>
#define MAX 200000

int prime[MAX + 10] = {};//存放素数
int is_prime[MAX + 10] = {};//判断此下标的数是否是素数

int main() {
    for (int m = 2; m <= MAX; m++) {
        if (!is_prime[m]) prime[++prime[0]] = m;
        for (int i = 1, p = prime[1]; i <= prime[0]; i++, p = prime[i]) {
            if (m * p > MAX) break;
            is_prime[m * p] = 1;
            if(m % p == 0) break;
        }
    }
    printf("%d\n", prime[10001]);
    return 0;
}
