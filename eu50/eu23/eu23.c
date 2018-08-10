/*************************************************************************
	> File Name: eu23.c
	> Author: 
	> Mail: 
	> Created Time: 2018年08月04日 星期六 10时53分31秒
 ************************************************************************/

#include<stdio.h>
#define MAX_S 28123

int sum[MAX_S] = {0};

void init() {
    for (int i = 1; i < MAX_S; i++) {
        for (int j = 1; j * j < i; j++) {
            int add = i / j;
            if (add * j == i) sum[i] += (add  + j);
        }
    } 
}


int main() {
    

    return 0;
}
