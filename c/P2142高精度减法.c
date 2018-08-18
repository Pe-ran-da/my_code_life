/*************************************************************************
	> File Name: P2142高精度减法.c
	> Author: Peranda
	> Mail: 
	> Created Time: 2018年08月18日 星期六 20时19分30秒
 ************************************************************************/

#include <stdio.h>
#include <cstring>
#define MAX_N 10000

char a[MAX_N + 10] = {0};
char b[MAX_N + 10] = {0};
int ans[MAX_N + 10] = {0};


void get_sum(char a1[], char b1[]) {
    int len = strlen(a1);
    ans[0] = len;
    int len2 = strlen(b1);
    for (int i = 1; i <= len; i++) {
        if (i <= len2) {
            ans[ans[0]--] = (a1[len - i] - b1[len2 - i]);//不需要-'0'
        } else {
            ans[ans[0]--] = (a1[len - i] - '0');
        }
    }
    /*for (int i = 1; i <= len; i++) {
        printf("%d ", ans[i]);
    }
    printf("\n");*/
    for (int i = len; i > 1; i--) { //进制转换
        if (ans[i] < 0) {
            ans[i - 1] -= 1;
            ans[i] += 10;
        }
        //printf("%d", ans[i]);
    }
    /*printf("\n");*/
    int i = 1;
    while (ans[i] == 0) {
        i++;
    }
    for (int k = i; k <= len; k++) {
        printf("%d", ans[k]);
    }
    printf("\n");
}

int main() {
    scanf("%s %s", a, b);
    int lena = strlen(a);
    int lenb = strlen(b);
    int key = 0;
    if (lena == lenb) {//特判
        for (int i = 0; i < lena; i++) {
            if (a[i] > b[i]) {
                key = 1;
                break;
            } else if (a[i] < b[i]) {
                key = -1;
                break;
            }
        }
    }

    if (lena > lenb || (lena == lenb && key == 1)) {//根据情况计算
        get_sum(a, b);
    } else if (lena < lenb || (lena == lenb && key == -1)) {
        printf("-");
        get_sum(b, a);
    } else if (lena == lenb && key == 0) {
        printf("0");
    }
    return 0;
}
