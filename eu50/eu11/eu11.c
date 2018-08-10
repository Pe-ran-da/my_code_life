/*************************************************************************
	> File Name: eu11.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月14日 星期六 11时16分53秒
 ************************************************************************/

#include<stdio.h>

int arr[4][2] = {
    0, 1, 1, 0, 1, 1, 1, -1
};

int main() {
    int num[20][20];
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            scanf("%d", num[i] + j);
        }
    }
    int ans = 0;
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            for (int k = 0; k < 4; k++) {
                int p = 1; 
                for (int l = 0; l < 4; l++) {
                    int x = i + arr[k][0] * l;
                    int y = j + arr[k][1] * l;
                    if (x < 0 || x >= 20) {p = 0; break;}
                    if (y < 0 || y >= 20) {p = 0; break;}
                    p *= num[x][y];
                }
                if (p > ans) ans = p;
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
