/*************************************************************************
	> File Name: eu30.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月22日 星期日 10时39分22秒
 ************************************************************************/

#include<stdio.h>
#include<cmath>
int add = 0;

void powers(int x) {
    int key = x;
    int ans = 0;
    while (x) {
        ans += pow(x % 10, 5);
        x /= 10;
    }
    if (ans == key) {
        printf("%d\n", key);
        add += key;
        printf("add : %d \n", add);
    } 
    
}

int main() {
    for (int i = 2; i < 354294; i++) {
        powers(i);
    }
    return 0;
}
