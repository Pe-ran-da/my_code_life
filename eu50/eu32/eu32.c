/*************************************************************************
	> File Name: eu32.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月27日 星期五 14时22分06秒
 ************************************************************************/

#include<stdio.h>
#define MAX 10000
#define MAX_N 10

int add[MAX] = {0};

int is_pandigital(int *arr, int x) {
    while(x) {
        if (arr[0]) return 0;
        if (arr[x % 10]) return 0;
        arr[x % 10] = 1;
        x /= 10;
    }
    return 1;
}

int SUM(int *arr) {
    //return (arr[1] && arr[2] && arr[3] && arr[4] && arr[5] && arr[6] && arr[7] && arr[8] && arr[9]);
    for (int i = 1; i < MAX_N; i++) {
        if (!arr[i]) return 0;
    }
    return 1;
}

int main() {
    int ans = 0;
    for (int i = 1; i < MAX; i++) {
        for (int j = 1; j < MAX; j++) {
            int sum[MAX_N] = {0};
            if (i * j > MAX) continue; // 100 * 100 = 10000; 3 3 6
            if(is_pandigital(sum, i) && is_pandigital(sum, j) && is_pandigital(sum, i * j) && SUM(sum)) {
                ans += i * j * (1 - add[i * j]);  // 此步乃是经典的，秀的操作； 
                add [i * j] = 1;
                //printf("%d * %d = %d\n", i, j, i * j);
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
