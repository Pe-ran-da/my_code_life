/*************************************************************************
	> File Name: 15.string_algorithm.cpp
	> Author: peranda
	> Mail:1365227825@qq.com  
	> Created Time: 2018年12月26日 星期三 15时50分12秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*int BF(const char *text, const char *pattern) {
    int len1 = strlen(text);
    int len2 = strlen(pattern);
    for (int i = 0; i < len1 - len2 + 1; i++) {
        int flag = 1;
        for (int j = 0; pattern[j] && flag; j++) {
            if (text[i + j] == pattern[j]) continue;
            flag = 0;
        }
        if (flag) return 1;
    }
    return 0;
}

int KMP(const char *text, const char *pattern) {
    int len1 = strlen(text);
    int len2 = strlen(pattern);
    int *next = (int *)malloc(sizeof(int) * len2);
    int j = -1;
    next[0] = -1;
    for (int i = 1; i < len2; i++) {
        int j = next[i - 1]; // 每次查找位置的前一位情况
        while (j != -1 && pattern[j + 1] != pattern[i]) j = next[j];//每次查找的位置迭代的核心代码
        //查找当前位置是否与前驱位置匹配
        if (pattern[j + 1] == pattern[i]) {
            j = j + 1;
        }
        next[i] = j;
    }
    j = -1; 
    for (int i = 0; i < text[i]; i++) {
        while (j != -1 && pattern[j] != text[i]) j = next[j];//同理操作
        if (pattern[j + 1] == text[i]) j += 1;//计算可匹配长度
        if (pattern[j + 1] == 0) return 1;//长度达标退出
    }
    return 0;
}



int main() {
    
    
    return 0;
}*/
#define TEST(func, a, b) { \
    printf("%s (\"%s\", \"%s\") = %d\n", #func, a, b, func(a, b)); \
}

int BruteForce(char *str, char *pattern) {

    for (int i = 0; str[i]; i++) {
        int flag = 1;
        for (int j = 0; pattern[j]; j++) {
            if (str[i + j] == pattern[j]) continue;
            flag = 0;
            break;
        }
        if (flag) return i;
    }
    return -1;
}


int KMP(char *str, char *pattern) {
    int *next = (int *)malloc(sizeof(int) * strlen(pattern));
    next[0] = -1; 
    for (int i = 1; pattern[i]; i++) {
        int j = next[i - 1];
        while (j != -1 && pattern[j + 1] != pattern[i]) j = next[j];
        if (pattern[j + 1] == pattern[i]) next[i] = j + 1;
        else next[i] = j;
    }
    int i = 0, j = -1;
    while (str[i]) {
        while (j != -1 && str[i] != pattern[j + 1]) j = next[j];
        if (str[i] == pattern[j + 1]) {
            j += 1;
        }
        i += 1;
        if (pattern[j + 1] == 0) return i - strlen(pattern);
    }
    return -1;
}

int Sunday(char *str, char *pattern) {
    #define BASE 128
    int ind[BASE] = {0};
    int len = strlen(pattern), max_len = strlen(str);
    for (int i = 0; i < BASE; i++) {
        ind[i] = len + 1;
    }
    for (int i = 0; i < len; i++) {
        ind[pattern[i]] = len - i;
    }
    for (int i = 0; i < max_len; ) {
        int flag = 1;
        for (int j = 0; j < len; j++) {
            if (str[i + j] == pattern[j]) continue;
            i += ind[str[i + len]];
            flag = 0;
            break;
        }
        if (flag) return i;
    }
    return -1;
    #undef BASE
}

int Shift_And(char *str, char *pattern) {
    #define BASE 128 
    int code[BASE] = {0}, len = 0;
    for (len = 0; pattern[len]; len++) {
        code[pattern[len]] |= (1 << len);
    }
    int p = 0;
    for (int i = 0; str[i]; i++) {
        p = (p << 1 | 1) & code[str[i]];
        if (p & (1 << (len - 1))) return i - len + 1;
    }
    return -1;
    #undef BASE
}


int main() {
    char str[100], pattern[30];
    while (scanf("%s%s", str, pattern) != EOF) {
        TEST(BruteForce, str, pattern);
        TEST(KMP, str, pattern);
        TEST(Sunday, str, pattern);
        TEST(Shift_And, str, pattern);

    }

    return 0;
}
