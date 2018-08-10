/*************************************************************************
	> File Name: eu22.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月30日 星期一 11时00分54秒
 ************************************************************************/

#include<iostream>
#include<inttypes.h>
#include <cstring>
#include<algorithm>
#include"eu22.h"


int main() {

    /*std :: sort (str1, str1 + str1.length);
    std :: cout << str1.length << std:: endl;
    int len = str1[937].length();
    int ans = 0;
    for (int i = 0; i < len; i++) {
        ans += (str1[938][i] - 'A' + 1);
    }
    std:: cout << ans * 983 << std::endl;*/
    int i = 0;
    while(str1[i].length() != 0) {
        i++;
    }
    std::cout << i << std::endl;
    
    std::sort(str1, str1 + i);
    int64_t sum, ans = 0;
    for (int j = 0; j < i; j++) {
        if (j >= 930 && j < 940) {
            std::cout << j << "j : " <<  str1[j] << std::endl;
        }
        sum = 0;
        for (int k = 0; k < str1[j].length(); k++) {
            sum += (str1[j][k] - 'A' + 1); 
        }
        ans += sum * (j + 1);
    } 
    std::cout << ans << std::endl;
    return 0;
}
