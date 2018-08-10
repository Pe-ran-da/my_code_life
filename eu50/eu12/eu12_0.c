/*************************************************************************
	> File Name: eu12_0.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月29日 星期日 19时26分38秒
 ************************************************************************/

#include<stdio.h>
#include<math.h>

int num(int n) {
    return (n + 1) * n / 2;
}

int factor_nums(int n) {
    int cnt = 0;
    int i;
    for (i = 1; i * i <= n; i++) {
        if (n % i == 0) cnt += 2;
    }
    if (sqrt(n) == i) cnt--;
    return cnt;
}

int main() {
    int n = 1; 
    while(factor_nums(num(n)) < 500) ++n;
    printf("%d\n", num(n));
    return 0;
}
