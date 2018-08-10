/*************************************************************************
	> File Name: eu21.c
	> Author: 
	> Mail: 
	> Created Time: 2018年08月04日 星期六 10时06分29秒
 ************************************************************************/

#include<stdio.h>
#define  MAX_S 100000

int sum[MAX_S] = {0};
int key[MAX_S] = {0};

void init() {
    for (int i = 1; i <= MAX_S; i++) {
        for (int j = 1; j * j < i; j++) {
            int add = i / j;
            if (add * j == i && add == i) {
                sum[i] -= i;
                continue;
            }
            if (add * j == i) sum[i] += j + add;
        }
        
    }
}

int main() {
    init();
    printf("%d %d\n", sum[220], sum[284]);
    int ans = 0;
    for (int i = 1; i < MAX_S; i++) {
        for (int j = 1; j < MAX_S; j++) {
            if (i == j || key[i] || key[j]) continue;
            if (sum[i] == j && sum[j] == i && !key[j] && !key[i]) {
                ans += i + j;
                key[i] = key[j] = 1;
            }
           // printf("error\n");
        }
    }
    printf("%d\n", ans);
    return 0;
}



