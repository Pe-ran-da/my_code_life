/*************************************************************************
	> File Name: guji.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月22日 星期日 11时03分37秒
 ************************************************************************/

#include<stdio.h>
#include<cmath>
#define max_s pow(9, 5)
#define max_n pow(10, i)

/*int main() {
    for (int i = 1; i < 100; i++) {
        if (max_s * i > max_n) continue;
        printf("%d\n", i);
        break;
    }
    return 0;
}
*/

#define MAX_S 9*8*7*6*5*4*3*2*1

int main() {
    for (int i = 1; i < 20; i++) {
        if (MAX_S * i > max_n) continue;
        printf("%d\n", i);
        break;
    }
    printf("%d\n", MAX_S);
    return 0;
}
