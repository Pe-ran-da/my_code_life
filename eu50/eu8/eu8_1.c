/*************************************************************************
	> File Name: eu8_1.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月14日 星期六 09时58分20秒
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#define ll long long int
#include"eu8.h"

int main(){
    ll max_num = 0, num = 1, zero_num = 0;
    for (int i = 0; i < 1000; i++) { 
        if (i >= 13) {                      // no i > 13
            if (arr_str[i - 13] == '0' ) {
                zero_num--;
            } else {
             num /= (arr_str[i - 13] - '0');
            }
        }
        if (arr_str[i] != '0') {
            num *= (arr_str[i] - '0');
        } else {
            zero_num++;
        }
        if (zero_num == 0 && i >= 12 && num > max_num) { // no i >= 13
            max_num = num;
        }
    }
    printf("%lld\n", max_num);
    return 0;
}
