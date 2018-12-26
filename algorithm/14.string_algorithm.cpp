/*************************************************************************
	> File Name: 14.string_algorithm.cpp
	> Author: peranda
	> Mail:1365227825@qq.com  
	> Created Time: 2018年12月25日 星期二 11时15分56秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int BF(const char *text, const char *pattern, int *p_cnt) {
    #define cnt (*p_cnt)
    int len1 = strlen(text);
    int len2 = strlen(pattern);
    for (int i = 0; i < len1 - len2 + 1; i++, cnt++) {
        int flag = 1;
        for (int j = 0; pattern[j] && flag; j++, cnt++) {
            if (text[i + j] == pattern[j]) continue;
            flag = 0;
        }
        if (flag) return 1;
    }
    #undef cnt
    return 0;
}

int KMP(const char *text, const char *pattern, int *p_cnt) {
    #define cnt (*p_cnt)
    int len1 = strlen(text);
    int len2 = strlen(pattern);
    int *next = (int *)malloc(sizeof(int) * len2);
    int j = -1;
    next[0] = -1;
    for (int i = 1; i < len2; i++, cnt++) {
        // 从第一位和第二位开始比较
        int j = next[i - 1]; // 每次择取相应的开始位置
        while (j != -1 && pattern[j + 1] != pattern[i]) j = next[j], cnt++;//每次的递推计算
        if (pattern[j + 1] == pattern[i]) { // 当前计算位置的判断
            j += 1;
        }
        // 满足条件则next会存在相应的值，不存在赋值为-1
        next[i] = j;
    }
    j = -1;
    for (int i = 0; text[i]; i++, cnt++) {
        while (j != -1 && pattern[j + 1] != text[i]) j = next[j], cnt++;
        if (pattern[j + 1] == text[i]) j += 1;
        if (pattern[j + 1] == 0) return 1;
    }
    #undef cnt
    return 0;
}

int main() {
    char str1[] = "hello world";
    int cnt = 0;
    printf("BF(%s, %s) = %d\n", str1, "wor", BF(str1, "wor", &cnt));
    printf("BF cnt : %d\n", cnt);
    cnt = 0;
    printf("KMP(%s, %s) = %d\n", str1, "wor", KMP(str1, "wor", &cnt));
    printf("KMP cnt : %d\n", cnt);
}
