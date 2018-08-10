/*************************************************************************
	> File Name: eu8_2.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月24日 星期二 11时57分29秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<inttypes.h>
//#include "eu8.h"
char arr_str[1005] = {0};

int main() {


    int offset = 0;
    FILE *fin = fopen("./input8", "r");
    while (fscanf( fin, "%s", arr_str + offset) != EOF) {
 // printf("%s", arr_str);
 // printf("\n---------------\n");
    offset = strlen(arr_str);
}

    int64_t max_p = 0, p = 1, zero_num = 0;
    for (int i = 0; arr_str[i]; i++) {
        if (i >= 13) {
            if (arr_str[i - 13] == '0' ) {
                zero_num--;
            } else {
                p /= (arr_str[i - 13] - '0');
            }
        }
        if (arr_str[i] == '0' ) {
            zero_num++;
        } else {
            p *= (arr_str[i] - '0');
        }
        if (zero_num == 0 && i >= 13 && p > max_p) { 
            max_p = p;
        }
    }

    printf("%" PRId64 "\n", max_p);
    return 0;
}
