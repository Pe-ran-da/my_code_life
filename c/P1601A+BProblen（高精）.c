/*************************************************************************
	> File Name: P1601A+BProblen（高精）.c
	> Author: Peranda
	> Mail: 
	> Created Time: 2018年08月18日 星期六 16时56分23秒
 ************************************************************************/

#include <stdio.h>
#include <cstring>
#define MAX_N 500

char a[MAX_N + 10] = {0};
char b[MAX_N + 10] = {0};
int ans[MAX_N + 10] = {0};

int main(){
    ans[0] = 0;
    for (int k = 0; k < 2; k++) {
        scanf("%s", a);
        if (ans[0] < strlen(a)) ans[0] = strlen(a);
        for (int i = 0; i < strlen(a); i++) {
            ans[strlen(a) - i] += (a[i] - '0');
        }
        for (int i = 1; i <= ans[0]; i++) {
            if (ans[i] < 10) continue;
            ans[i + 1] += ans[i] / 10;
            ans[i] %= 10;
            ans[0] += (ans[0] == i);
        }
    }
    for (int i = ans[0]; i > 0; i--) {
        printf("%d", ans[i]);
    }
    return 0;

    
}


