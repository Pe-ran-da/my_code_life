/*************************************************************************
	> File Name: eu7.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月22日 星期日 16时58分05秒
 ************************************************************************/

#include<stdio.h>
#define MAX_S 200000

int arr[MAX_S + 5];

void prime() {
    for (int i = 2; i * i <= MAX_S; i++) {
        if (arr[i]) continue;
        for (int j = i * i; j <= MAX_S; j += i) {
            arr[j] = 1;
        }
    }
    for (int i = 2; i <= MAX_S; i++) {
        if (!arr[i]) arr[++arr[0]] = i;
    }
    return ;
} 

int main() {
    prime();
    printf("%d\n", arr[10001]);
    return 0;
}
