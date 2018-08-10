/*************************************************************************
	> File Name: eu10.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月24日 星期二 19时47分15秒
 ************************************************************************/

#include<stdio.h>
#include<inttypes.h>
#define MAX_S 2000000

int prime[MAX_S + 10] = {0};

int main() {
    int64_t ans = 0;
    for (int64_t i = 2; i <= MAX_S; i++) {
        if (prime[i]) continue;
        for (int64_t j = i; j <= MAX_S; j += i) {
            if (prime[j]) continue;
            prime[j] = i;
        }
    }
    for (int i = 2; i <= MAX_S; i++) {
        (prime[i] == i) && (ans += i);
    }
    printf("%"PRId64"\n", ans);
    return 0;
}
