/*************************************************************************
	> File Name: eu7_3.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月24日 星期二 19时02分46秒
 ************************************************************************/

#include<stdio.h>
#define MAX_S 10000

int prime[MAX_S + 10];

int main() {
    for (int i = 2; i <= MAX_S; i++) {
        if (prime[i]) continue;
        for (int j = i; j <= MAX_S; j += i) {
            if (prime[j]) continue;
            prime[j] = i;
        }
    }
    int n;
    while (scanf("%d", &n) != EOF) {
        printf("%d = 1", n);
        while(n != 1) {
            printf(" * %d", prime[n]);
            n /= prime[n];
        }
        printf("\n");
    }
    return 0;
}
