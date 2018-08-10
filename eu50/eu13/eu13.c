/*************************************************************************
	> File Name: eu13.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月19日 星期四 20时28分47秒
 ************************************************************************/

#include<stdio.h>
#include <string.h>


int main() {
    char read_arr[55];
    int add[55] = {0};
    while (scanf("%s",read_arr) != EOF) {
        printf("printf: %s \n", read_arr);
        int len = strlen(read_arr);
        if (len > add[0]) add[0] = len;
        for (int i = 0; read_arr[i]; i++) {
            add[len - i] += (read_arr[i] - '0'); // 减去'0'别忘加括号
        } 
        for (int i = 1; i <= add[0]; i++) {
            if (add[i] >= 10){
                add[i + 1] += add[i] / 10;
                add[i] %= 10;
                if (i == add[0]) add[0]++;
            }
        } 
        for (int i = add[0]; i > add[0] - 10; i--) {　
            printf ("%d", add[i]);
        }
        printf("\n");
    }
    return 0;
}
