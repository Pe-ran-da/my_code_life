/*************************************************************************
	> File Name: eu35.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月27日 星期五 17时12分12秒
 ************************************************************************/

#include<stdio.h>
#include<math.h>
#include<inttypes.h>
#define MAX_SUM 20000000

int prime[MAX_SUM + 10] = {0};
int peranda[MAX_SUM + 10] = {0};
void is_prime() {
    for (int i = 2; i <= MAX_SUM; i++) {
        if(!peranda[i]) prime[++prime[0]] = i;
        for (int j = 1; j <= prime[0]; j++) {
            if (i * prime[j] >= MAX_SUM) break;
            peranda[i * prime[j]] = 1;
            if (i % prime[j] == 0) break;
        }
    }
}

int is_ok(int x) {
   /* int64_t n = floor(log10(x));
    int64_t key = x;
    int64_t y = n + 1; 
    while (y--) {
        if (key % 10 == 0) return 0;
        if (prime[key] <= 1) return 0;
        key = (key % 10) * n + (key / 10);
    }
    if (key != x) return 0;
    return key; // 防止中间有数是０的时候
    */
    if (peranda[x] != 0) return 0;
    int num = x, key, value;
    key = (int)pow(10, floor(log10(x))); //权位
    value = (int)floor(log10(x)) + 1; // 位数
    for (int i = 0; i < value; i++) {
        num = (num % 10) * key + num / 10;
        if (peranda[num] != 0) return 0;
    }
    printf("num : %d\n", x);
    return 1;
}
int main() {
    is_prime();
    int ans = 0; 
    for (int i = 1; i <= prime[0]; i++) {
        //((prime[i] > 1) && (is_ok(i))) && (ans += i);
        if (prime[i] >= 1000000) break;
        if (is_ok(prime[i])) {
            ans++;
        }
    }
    printf("%d\n", ans);
    /*for (int i = 1; i <= 100; i++) {
        printf("%d\n", prime[i]);
    }*/
    return 0;
}
