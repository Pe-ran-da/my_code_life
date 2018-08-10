/*************************************************************************
	> File Name: eu18.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月29日 星期日 14时20分26秒
 ************************************************************************/

#include<stdio.h>
#define MAX_S 30

int keep[MAX_S + 5][MAX_S + 5];
int map[MAX_S + 5][MAX_S + 5] = {0};

int solve(int i, int j) {
    if (i == MAX_S) return 0;
    if (keep[i][j]) return keep[i][j];
    int lnum = solve(i + 1, j), rnum = solve(i + 1, j + 1);
    keep[i][j] = (lnum > rnum ? lnum : rnum) + map[i][j];
    return keep[i][j];
}

int main() {
    for (int i = 0; i < 15; i++) {
        for (int j = 0; j <= i; j++) {
            scanf("%d", map[i] + j);
        }
    }
    printf("%d\n", solve(0, 0));
    return 0;
}
