/*************************************************************************
	> File Name: main.c
	> Author: 
	> Mail: 
	> Created Time: 2018年08月09日 星期四 19时56分53秒
 ************************************************************************/

#include<stdio.h>
#include "array.h"
#include "main.h"
int main() {
    int a[10];
    int i;
    for(i = 0; i < 10; i++) {
        scanf("%d", &a[i]);
    }
    printf("数组元素和为: %d\n", array_sum(a, 10)); 
    printf("数组元素平均值为: %g\n", array_avg(a, 10)); 
    return 0;
}                               
