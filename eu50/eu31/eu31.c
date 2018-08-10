/*************************************************************************
	> File Name: eu31.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月27日 星期五 10时24分36秒
 ************************************************************************/

#include<stdio.h>
#define MAX_N 8

int w[MAX_N] = {1, 2, 5, 10, 20, 50, 100, 200}; 
int sum[201] = {0};

int main() {
    sum[0] = 1;
    for (int i = 0; i < 8; i++) {
        for (int j = w[i]; j < 201; j++) {
            sum[j] += sum[j - w[i]];
        }
    }
    printf("%d\n", sum[200]);
    return 0;
}
