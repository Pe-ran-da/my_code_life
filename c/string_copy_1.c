/*************************************************************************
	> File Name: string_copy_1.c
	> Author: 
	> Mail: 
	> Created Time: 2018年08月09日 星期四 10时02分56秒
 ************************************************************************/

#include<stdio.h>
#include<assert.h>
#include<string.h>

char *string_strcpy(char *s1, const char *s2) {
    assert((s1 != NULL) && (s2 != NULL));

    while((*s1++ = *s2++) != '\0');

    return s1;
}

char *string_strncpy(char *s1, const char *s2, int key) {
    assert((s1 != NULL) && (s2 != NULL));

    while(key && (*s1++ = *s2++) != '\0') {
        key -= 1;
    }
    if (key) {
        while(key--) {
            *s1++ = '\0';
        }
    }
    
    return s1;
}

int main() {
    char string[100] = "peranda";
    char index[10] = "";
    char value[10] = "";
    int len1 = strlen(string);
    string_strcpy(index, string);
    int len = strlen(string);
    printf("%d %s\n",len1, index);
    printf("%s\n", string);
    //问题１　为什么strcpy在copy时 copy串的长度没 原串长的时候　并不会导致
    //复制失败，反而能原样copy?
    //答案：原串的长度是声明的很长的　若按照原串内容copy 那么会copy到'\0'
    //从而copy串里有原串的"\0"
    //
    //总结：空间要多开　不要访问越界　写入越界
    string_strncpy(value, string, 3);
    printf("%s\n", value);
    return 0;
}


