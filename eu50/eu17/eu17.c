/*************************************************************************
> File Name: eu17.c
> Author: 
> Mail: 
> Created Time: 2018年07月14日 星期六 20时18分05秒
************************************************************************/

#include<stdio.h>

int arr1[20] = {0, 3, 3, 5, 4, 4, 3, 5, 5, 4, 3,

                6, 6, 8, 8, 7, 7, 9, 8, 8 };

int arr2[10] = { 0, 0, 6, 6, 5, 5, 5, 7, 6, 6 };

int get_value(int x) {
    if (x < 20) return arr1[x];
    if (x >= 20 && x < 100) {
        return arr2[x / 10] + arr1[x % 10];
    } else if (x < 1000) {
        if (x % 100 == 0) {
            return arr1[x / 100] + 7; 
        } else {
            return arr1[x / 100] + get_value(x % 100) + 10;
        }
    } else if (x == 1000) {
        return 11;
    }
}


int main() {
    int ans = 0;
    for (int i = 1; i <= 1000; i++) {
        ans += get_value(i);
    }
    printf("%d\n", ans);
    return 0;
}
