/*************************************************************************
	> File Name: eu37.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月28日 星期六 15时52分22秒
 ************************************************************************/

#include<stdio.h>
#include<math.h>

#define MAX_N 2000000

int prime[MAX_N + 10] = {0};
int peranda[MAX_N + 10] = {1, 1};

void is_prime() {
    for (int i = 2; i <= MAX_N; i++){
        if (!peranda[i]) prime[++prime[0]] = i;
        for (int j = 1; j <= prime[0]; j++) {
            if (prime[j] * i >= MAX_N) break;
            peranda[prime[j] * i] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}

int truncatable_prime(int x) {
    if (peranda[x] != 0) return 0; 
    int value = x;
    int value1 = x;
    int sum = (int)pow(10, floor(log10(x))); 
    while(value) {
        if (peranda[value] != 0) return 0;
        value /= 10;
    }
    while(value1) {
        if (peranda[value1] != 0) return 0;
        value1 -= (value1 / sum) * sum;
        sum /= 10;
    }
    return 1;
}

int main() {
    is_prime();
    int ans = 0, key = 0;
    for (int i = 1; i <= prime[0]; i++){
        if (10 > prime[i]) continue;
        if (truncatable_prime(prime[i])) {
            key += 1;
            ans += prime[i];
            printf(" key: %d  prime : %d \n", key, prime[i]);
            if (key > 11) break;
        } 
    }
    printf("%d\n", ans);
    /* int x = floor(log10(1111));
    int y = pow(10, floor(log10(1111)));
    printf("%d %d\n", x, y);*/ // 测试位数和权位计算。    

   // for (int i = 1; i <= 100; i++) {
     //   if (!peranda[i]) printf("%d\n", i);
    //}
    return 0;
}

