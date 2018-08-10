/*************************************************************************
	> File Name: string_compare_1.c
	> Author: 
	> Mail: 
	> Created Time: 2018年08月08日 星期三 22时20分04秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>

int main() {
    char string[] = "peranda";
    char index[]  = "perandb";

    int ans = strcmp(string, index);     // 比较了整个字符串
    printf("ans : %d\n", ans);

    int sum = strncmp(string, index, 6); // 比较了前六个字符串，
    
    //就是说strncmp可以由部分匹配的能力
    
    printf("sum : %d\n", sum);
    return 0;
}
