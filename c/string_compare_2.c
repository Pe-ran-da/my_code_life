/*************************************************************************
	> File Name: string_compare_2.c
	> Author: 
	> Mail: 
	> Created Time: 2018年08月08日 星期三 22时28分27秒
 ************************************************************************/

#include<stdio.h>
#include<assert.h> // 提供assert函数
#include<string.h>

int string_strcmp(const char *s1, const char *s2) {
    assert((s1 != NULL) && (s2 != NULL));
    
    while(*s1 != '\0' && *s2 != '\0') {
        
        if (*s1 - *s2 > 0) return 1; //只要差不相同的，谁大那么相应的串就大
        if (*s1 - *s2 < 0) return -1;

        s1 += 1;
        s2 += 1;
    }
    if (*s1 == '\0' && *s2 != '\0') return -1; //此时，谁先'\0'谁就小
    if (*s2 == '\0' && *s1 != '\0') return 1;  

    return 0; // 同时为'\0'，并且前面部分一样　返回0
}

int string_strncmp(const char *s1, const char *s2, int key) {
    assert((s1 != NULL) && (s2 != NULL));

    while(*s1 != '\0' && *s2 != '\0' && key) {
        
        if (*s1 - *s2 > 0) return 1;    // 谁大那么相应的串就大
        if (*s1 - *s2 < 0) return -1;
        
        s1 += 1;
        s2 += 1;
        key -= 1;       // 引入了key是为了对比相应的长度的串
    }
    if (*s1 == '\0' && *s2 != '\0') return -1; //谁先'\0'谁就小
    if (*s2 == '\0' && *s1 != '\0') return 1;

    return 0;        // 前面所有情况都不符合,那么肯定对比的部分相等
}

int main() {
    char string[] = "peranda";
    char index[]  = "perandb";

    int ans = string_strcmp(string, index);     // 比较了整个字符串
    printf("ans : %d\n", ans);

    int sum = string_strncmp(string, index, 6); // 比较了前六个字符串，
        
    //就是说strncmp可以由部分匹配的能力
       
    printf("sum : %d\n", sum);
    return 0;
}
