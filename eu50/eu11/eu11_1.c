/*************************************************************************
	> File Name: eu11_1.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月24日 星期二 14时56分34秒
 ************************************************************************/

#include<stdio.h>


int main() {

    int arr[4][2] = {
        1, 1, 1, 0, 0, 1, 1, -1 
    };

    int num[30][30] = {0};
    for (int i = 5; i < 25; i++) {
        for (int j = 5; j < 25; j++) {
            scanf("%d", num[i] + j);
        }
    }
    int ans = 0;
    for (int i = 5; i < 25; i++) {
        for (int j = 5; j < 25; j++) {
            for (int k = 0; k < 4; k++) {
                int p = 1;
                for (int temp = 0; temp < 4; temp++) {
                    int x = i + temp * arr[k][0];
                    int y = j + temp * arr[k][1];
                    p *= num[x][y];
                }
                if (p > ans) ans = p;
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
