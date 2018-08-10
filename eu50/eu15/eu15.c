/*************************************************************************
	> File Name: eu15.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月29日 星期日 11时49分54秒
 ************************************************************************/

#include<stdio.h>
#include<inttypes.h>

int64_t gcd(int64_t m, int64_t n) {
    if (n == 0) return m;
    return gcd(n, m % n);
}

int main() {
    int64_t m = 1, n = 1;
    for (int64_t i = 40; i > 20; i--) {
        m *= i;
        n *= (i - 20);
        int64_t key = gcd(m , n);
        m /= key;
        n /= key;
    }
    printf("%" PRId64 "\n", m / n);
    return 0;
}
