/*************************************************************************
	> File Name: eu5.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月22日 星期日 15时01分37秒
 ************************************************************************/

#include<stdio.h>

int gcd(int a, int b) {
    return (b ? gcd (b , a % b): a);
}


int main() {
    int ans = 1;
    for (int i = 2; i <= 20; i++){
        if(!ans % i) continue;
        ans = ans / gcd(ans, i) * i;
    }
    printf("%d\n", ans);
    return 0;
}
