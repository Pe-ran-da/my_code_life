/*************************************************************************
	> File Name: eu14.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月24日 星期二 15时12分08秒
 ************************************************************************/

#include<stdio.h>
#include<inttypes.h>
#define KEEP_RANGE 1000000
#define MAX_S 1000000

int sum[KEEP_RANGE + 10] = {};


int collatz(int64_t x) {
    if (x == 1) return 1;
    if (x <= KEEP_RANGE && sum[x]) return sum[x];
    int temp_sum;
    if (x & 1) {
        temp_sum = collatz(x * 3 + 1) + 1;
    } else {
        temp_sum = collatz(x >> 1) + 1;
    }
    if (x <= KEEP_RANGE) sum[x] = temp_sum;
    return temp_sum;
}

int main() {
    int ans = 0, ans_length = 0;
    for (int i = 1; i < MAX_S; i++) {
        int temp_length = collatz(i);
        if (temp_length > ans_length) {
            ans = i;
            ans_length = temp_length;
        }
    }
    printf("%d %d\n", ans, ans_length);
    return 0;
}
