/*************************************************************************
	> File Name: eu7_2.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月24日 星期二 18时44分36秒
 ************************************************************************/

#include<stdio.h>
#define MAX_S 100

int arr[MAX_S + 10] = {};

int main() {
    for (int i = 2; i <= MAX_S; i++) {
        if(arr[i]) continue;
        for (int j = i; j <= MAX_S; j += i) {
            if (arr[j]) continue;
            arr[j] = i;  // 计算数ｉ最大素因子
        }
    }    
    for (int i = 2; i <= MAX_S; i++) {
        if (!arr[i]) arr[i] = i;
    }
    for (int i = 2; i <= MAX_S; i++) {
        printf("%d %d \n", i, arr[i]);
    }
    printf("\n");
    return 0;
}
