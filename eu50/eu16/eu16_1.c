/*************************************************************************
	> File Name: eu16_1.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月27日 星期五 09时39分37秒
 ************************************************************************/

#include<stdio.h>
int num[400] = {1, 1};

int main() {
    for (int i = 0; i < 100; i++) {
         for (int j = 1; j <= num[0]; j++) {
            num[j] *= 1024;
        }
        for (int j = 1; j <= num[0]; j++) {
            if (num[j] < 10) continue;
            num[j + 1] += num[j] / 10;
            num[j] %= 10;
            num[0] += (j == num[0]);
        }
    }
    int ans = 0;
    for (int i = 1; i <= num[0]; i++) {
        ans += num[i];
    }
    printf("%d\n", ans);
    return 0;
}


