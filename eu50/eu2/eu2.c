/*************************************************************************
	> File Name: eu2.c
	> Author: 
	> Mail: 
	> Created Time: 2018年07月20日 星期五 14时40分51秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#define MAX 4000000



/*int main() {
    int add = 0;
    int a = 0,b = 1, temp;
    while (a + b <= MAX) {
        temp = b;
        b = a + b;
        a = temp;
        if (b & 1) continue;
        add += b;
        printf("%d\n", add);
    }
    printf("%d\n", add);
    return 0;
}*/


/*int arr[10000];

int main() {
    arr[0] = arr[1] = 1;    
    int i = 2;
    int add = 0;
    while(arr[i - 2] + arr[i - 1] <= MAX) {
        arr[i] = arr[i - 2] + arr[i - 1];
        if (arr[i] & 1) continue;
        add += arr[i];
    }
    printf("%d", add);



    return 0;
}*/

int main() {
    int f[3] = {1, 0, 0};
    int add = 0, n = 1;

    while(f[(n + 2) % 3] + f[(n + 1) % 3] <= MAX) {
        f[n % 3] = f[(n + 1) % 3] + f[(n + 2) % 3];
        if ((f[n % 3] & 1) == 0) add += f[n % 3];
        n++;
    }
    printf("%d\n", add);
    return 0;
}
