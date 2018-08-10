/*************************************************************************
	> File Name: eu4.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月22日 星期日 09时14分37秒
 ************************************************************************/

#include<stdio.h>

int palindiomic_number(int x){
    int key = x; 
    int value = 0;;
    while(x > 0) {
        value = value * 10 + x % 10;
        x /= 10;
    }
    return value == key;
}


int main() {
    int ans = 0;
    for (int i = 100; i < 1000; i++) {
        for (int j = i; j < 1000; j++) {
            if (j * i < ans) continue; 
            if (palindiomic_number(i * j)) {    
                ans = i * j;
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
