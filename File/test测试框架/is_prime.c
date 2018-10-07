/*************************************************************************
> File Name: test.c
> Author: Peranda
> Mail: 
> Created Time: 2018年10月04日 星期四 17时52分30秒
************************************************************************/

#include <stdio.h>
int is_prime(int x) {
    if (x <= 1) return 0;
    for (int i = 2; i * i <= x; i++) {
        if (x % i == 0) return 0;
    }
    return 1;
}
