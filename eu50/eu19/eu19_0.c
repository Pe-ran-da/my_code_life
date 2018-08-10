/*************************************************************************
	> File Name: eu19_0.c
	> Author: 
	> Mail: 
	> Created Time: 2018年08月05日 星期日 11时49分56秒
 ************************************************************************/

#include<stdio.h>

int year_sum(int y) {
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

int main() {
    int m[15], d = 1; {
        for (int i = 3; i < 15; i++) {
            m[i] = i;
        }

    }
    int ans = 0;
    for (int i = 1901; i <= 2000; i++) {
        for (int k = 3; k < 15; k++) {
        int w = (d + 2 * m[k] + 3 * (m[k] + 1) / 5 + i + i / 4 - i / 100 + i / 400) % 7;  // 可能由逻辑上的问题
        if (w + 1 == 7) ans++;
        }
    }
    printf("%d\n", ans);
    return 0;
}
