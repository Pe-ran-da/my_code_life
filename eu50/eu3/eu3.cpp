/*************************************************************************
	> File Name: eu3.cpp
	> Author: 
	> Mail: 
	> Created Time: 2018年07月20日 星期五 16时32分13秒
 ************************************************************************/

#include<stdio.h>
#include<inttypes.h>
#define NUM 600851475143


int main() {
    int64_t ans = 0, num = NUM, n = 2;
    while (n * n <= num) {
        if (num % n == 0) ans = n;
        while(num % n == 0) num /= n;
        n++;
    }
    
    if (num != 1) ans = num;
    
    printf("%" PRId64 "\n", ans);
    return 0;
}


