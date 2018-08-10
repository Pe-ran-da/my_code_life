/*************************************************************************
	> File Name: eu44.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月28日 星期六 17时45分25秒
 ************************************************************************/

#include<stdio.h>
#include<inttypes.h>
#define MAX_S 10
#define MAX_N 7
#define MAX_A 1000000000

int64_t key[MAX_N] = {2, 3, 5, 7, 11, 13, 17};

int divisibility(int64_t x) {
    int64_t  y = MAX_A, a = 1000000;
    for (int i = 1; i <= 8; i++) {
        int64_t value = x % y / a;
        a /= 10;
        y /= 10;
        if (value % key[i - 1]) return 0;
    }
    return 1;
}


int if_ok(int64_t x, int *arr) {
    while (x) {
        if(arr[x % 10]) return 0;
        arr[x % 10] = 1;
        x /= 10;
    }
    for (int i = 0; i <= 9; i++) {
        if (arr[i] != 1) return 0;
    }
    return 1;
}

int main() {
    for (int64_t i = 123456789; i <= 987654321; i++) {
        int sum[MAX_S] = {0};
        if (if_ok(i, sum)) {
           //if (divisibility(i)) printf("%" PRId64 "\n", i);
            printf("%"PRId64 "\n", i);
        }
    }
    return 0;
}
