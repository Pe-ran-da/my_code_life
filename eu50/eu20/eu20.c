/*************************************************************************
	> File Name: eu20.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月30日 星期一 10时21分09秒
 ************************************************************************/

#include<stdio.h>
#include<inttypes.h>
#define MAX_N 1000

int main() {
    int64_t a[MAX_N] = {0};
    a[0] = a[1] = 1;
    for(int i = 1; i <= 100; i++) {
        for (int l = 1; l <= a[0]; l++) {
            a[l] *= i;
        }
        for (int j = 1; j <= a[0]; j++) {
            if (a[j] < 10)continue;
            a[j + 1] += a[j] / 10;
            a[j] %= 10;
            a[0] += (j == a[0]);
        }
    }
    int64_t ans = 0;
    for (int i = 1; i <= a[0]; i++) {
        ans += a[i];
    }
    printf("%" PRId64 "\n", ans);
    return 0;
}
